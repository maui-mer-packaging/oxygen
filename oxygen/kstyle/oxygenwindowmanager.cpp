//////////////////////////////////////////////////////////////////////////////
// oxygenwindowmanager.cpp
// pass some window mouse press/release/move event actions to window manager
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo@oxygen-icons.org>
//
// Largely inspired from BeSpin window decoration
// Copyright (C) 2007 Thomas Luebking <thomas.luebking@web.de>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include "oxygenwindowmanager.h"
#include "oxygenwindowmanager.moc"


#include <QtGui/QMouseEvent>
#include <QtGui/QApplication>
#include <QtGui/QDockWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QMenuBar>
#include <QtGui/QStyle>
#include <QtGui/QStyleOptionGroupBox>
#include <QtGui/QTabBar>
#include <QtGui/QTabWidget>

#ifdef Q_WS_X11
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#endif

namespace Oxygen
{

    //_____________________________________________________________
    WindowManager::WindowManager( QObject* parent ):
        QObject( parent ),
        enabled_( true ),
        dragDistance_(6),
        dragDelay_( QApplication::doubleClickInterval() ),
        dragInProgress_( false )
    {

        #ifdef Q_WS_X11

        Display* display( QX11Info::display() );
        netMoveResize_ = XInternAtom(display, "_NET_WM_MOVERESIZE", false );

        // one should make sure that the atom is supported
        // and permanently disable if not

        #endif

    }

    //_____________________________________________________________
    void WindowManager::registerWidget( QWidget* widget )
    {
        if( isDragableWidget( widget ) )
        {
            widget->removeEventFilter( this );
            widget->installEventFilter( this );
        }
    }

    //_____________________________________________________________
    void WindowManager::unregisterWidget( QWidget* widget )
    {
        if( widget )
        { widget->removeEventFilter( this ); }
    }

    //_____________________________________________________________
    bool WindowManager::eventFilter( QObject* object, QEvent* event )
    {
        if( !enabled() ) return false;

        /*
        if a drag is in progress, the widget will not receive any event
        we trigger on the first MouseMove or MousePress events that are received
        by any widget in the application to detect that the drag is finished
        */
        if( dragInProgress_ && target_ && ( event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonPress ) )
        {

            // store target window (see later)
            QWidget* window( target_.data()->window() );

            /*
            post some mouseRelease event to the target, in order to counter balance
            the mouse press that triggered the drag. Note that it triggers a resetDrag
            */
            QMouseEvent mouseEvent( QEvent::MouseButtonRelease, dragPoint_, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier );
            qApp->sendEvent( target_.data(), &mouseEvent );

            if( event->type() == QEvent::MouseMove )
            {
                /*
                HACK: quickly move the main cursor out of the window and back
                this is needed to get the focus right for the window children
                the origin of this issue is unknown at the moment
                */
                const QPoint cursor = QCursor::pos();
                QCursor::setPos(window->mapToGlobal( window->rect().topRight() ) + QPoint(1, 0) );
                QCursor::setPos(cursor);
            }

            return true;

        }

        if( event->type() == QEvent::MouseButtonPress )
        {

            // cast event and check buttons/modifiers
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );
            if( !( mouseEvent->modifiers() == Qt::NoModifier && mouseEvent->button() == Qt::LeftButton ) )
            { return false; }

            // cast to widget and check mouse grab
            QWidget *widget = static_cast<QWidget*>( object );
            if( canDrag( widget, mouseEvent->pos() ) )
            {

                // save target and drag point
                target_ = widget;
                dragPoint_ = mouseEvent->pos();

                // start timer
                if( dragTimer_.isActive() ) dragTimer_.stop();
                dragTimer_.start( dragDelay_, this );

                /*
                accept the event, to prevent other widget
                to interfere with the drag process
                */
                return true;

            } else return false;

        } else if( event->type() == QEvent::MouseMove && target_ ) {

            // stop timer
            if( dragTimer_.isActive() ) dragTimer_.stop();

            // cast event and check drag distance
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );
            if( QPoint( mouseEvent->pos() - dragPoint_ ).manhattanLength() >= dragDistance_ )
            {
                /*
                trigger startDrag with 0 delay
                this make sure all Qt pending events are processed
                (and notably pending mouseRelease events)
                before actually starting the drag
                */
                dragTimer_.start( 0, this );
            }

            /*
            always accept the event, to prevent other widget
            to interfere with the drag process
            */
            return true;

        } else if( event->type() == QEvent::MouseButtonRelease && target_ ) {

            resetDrag();
            return false;

        }

        return false;

    }

    //_____________________________________________________________
    void WindowManager::timerEvent( QTimerEvent* event )
    {

        if( event->timerId() == dragTimer_.timerId() )
        {
            dragTimer_.stop();
            if( target_ )
            { startDrag( target_.data(), target_.data()->mapToGlobal( dragPoint_ ) ); }

        } else {

            return QObject::timerEvent( event );

        }

    }

    //_____________________________________________________________
    bool WindowManager::isDragableWidget( QWidget* widget ) const
    {

        // check widget
        if( !widget ) return false;

        // all accepted types
        if(
            widget->inherits( "KTitleWidget" ) ||
            ( widget->inherits( "QDialog" ) && widget->isWindow() ) ||
            ( widget->inherits( "QMainWindow" ) && widget->isWindow() ) ||
            widget->inherits( "QGroupBox" ) ||
            widget->inherits( "QMenuBar" ) ||
            widget->inherits( "QStatusBar" ) ||
            widget->inherits( "QTabBar" ) ||
            widget->inherits( "QTabWidget" ) ||
            widget->inherits( "QToolBar" ) )
        { return true; }

        // accept non-selectable labels
        if(
            widget->inherits( "QLabel" ) &&
            widget->parentWidget() &&
            ( widget->parentWidget()->inherits( "QStatusBar" ) || widget->parentWidget()->inherits( "KTitleWidget" ) ) &&
            !static_cast<QLabel*>(widget)->textInteractionFlags().testFlag( Qt::TextSelectableByMouse ) )
        { return true; }

        return false;

    }

    //_____________________________________________________________
    bool WindowManager::canDrag( QWidget* widget, const QPoint& position ) const
    {

        // check enability
        if( !enabled() ) return false;

        // assume isDragable widget is already passed
        // check some special cases where drag should not be effective

        // check mouse grabber
        if( QWidget::mouseGrabber() ) return false;

        /*
        check cursor shape.
        Assume that a changed cursor means that some action is in progress
        and should prevent the drag
        */
        if( widget->cursor().shape() != Qt::ArrowCursor )
        { return false; }

        // check menubar
        if( QMenuBar* menuBar = qobject_cast<QMenuBar*>( widget ) )
        { return !(menuBar->actionAt( position ) || menuBar->activeAction() ); }

        // tabbar. Make sure no tab is under the cursor
        if( QTabBar* tabBar = qobject_cast<QTabBar*>( widget ) )
        { return tabBar->tabAt( position ) == -1; }

        // tabbar. Make sure no child is under the cursor. This should
        // correspond to the empty area alongside the tabs in the tabbar
        if( QTabWidget* tabWidget = qobject_cast<QTabWidget*>( widget ) )
        { return !tabWidget->childAt( position ); }

        // check labels
        if( QLabel* label = qobject_cast<QLabel*>( widget ) )
        { return !label->textInteractionFlags().testFlag( Qt::TextSelectableByMouse ); }

        /*
        check groupboxes
        prevent drag if unchecking grouboxes
        */
        if( QGroupBox *groupBox = qobject_cast<QGroupBox*>( widget ) )
        {
            // non checkable group boxes are always ok
            if( !groupBox->isCheckable() ) return true;

            // gather options to retrieve checkbox subcontrol rect
            QStyleOptionGroupBox opt;
            opt.initFrom( groupBox );
            if( groupBox->isFlat() ) opt.features |= QStyleOptionFrameV2::Flat;
            opt.lineWidth = 1;
            opt.midLineWidth = 0;
            opt.text = groupBox->title();
            opt.textAlignment = groupBox->alignment();
            opt.subControls = (QStyle::SC_GroupBoxFrame | QStyle::SC_GroupBoxCheckBox);
            if (!groupBox->title().isEmpty()) opt.subControls |= QStyle::SC_GroupBoxLabel;

            opt.state |= (groupBox->isChecked() ? QStyle::State_On : QStyle::State_Off);
            if( groupBox->style()->subControlRect(QStyle::CC_GroupBox, &opt, QStyle::SC_GroupBoxCheckBox, groupBox ).contains( position ))
            { return false; }
        }

        return true;

    }

    //____________________________________________________________
    void WindowManager::resetDrag( void )
    {
        target_.clear();
        if( dragTimer_.isActive() ) dragTimer_.stop();
        dragPoint_ = QPoint();
        dragInProgress_ = false;
        qApp->removeEventFilter( this );
    }

    //____________________________________________________________
    void WindowManager::startDrag( QWidget* widget, const QPoint& position )
    {
        if( !( enabled() && widget ) ) return;
        if( QWidget::mouseGrabber() ) return;

        #ifdef Q_WS_X11
        QX11Info info;
        XEvent xev;
        xev.xclient.type = ClientMessage;
        xev.xclient.message_type = netMoveResize_;
        xev.xclient.display = QX11Info::display();
        xev.xclient.window = widget->window()->winId();
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = position.x();
        xev.xclient.data.l[1] = position.y();
        xev.xclient.data.l[2] = 8; // NET::Move
        xev.xclient.data.l[3] = Button1;
        xev.xclient.data.l[4] = 0;
        XUngrabPointer(QX11Info::display(), QX11Info::appTime());
        XSendEvent(QX11Info::display(), QX11Info::appRootWindow(info.screen()), False,
            SubstructureRedirectMask | SubstructureNotifyMask, &xev);

        dragInProgress_ = true;
        qApp->installEventFilter( this );
        #endif // Q_WS_X11

        return;

    }

}