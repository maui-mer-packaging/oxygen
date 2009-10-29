#ifndef oxygenmenuengine_h
#define oxygenmenuengine_h

//////////////////////////////////////////////////////////////////////////////
// oxygenmenuengine.h
// stores event filters and maps widgets to timelines for animations
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
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

#include "oxygenbaseengine.h"
#include "oxygendatamap.h"
#include "oxygenmenudata.h"

namespace Oxygen
{

    //! widget index
    enum WidgetIndex
    {
        Current,
        Previous
    };

    //! stores menu hovered action and timeLine
    class MenuBaseEngine: public BaseEngine
    {
        Q_OBJECT

        public:

        //! constructor
        MenuBaseEngine( QObject* parent ):
        BaseEngine( parent )
        {}

        //! destructor
        virtual ~MenuBaseEngine( void )
        {}

        //! register menubar
        virtual bool registerWidget( QWidget* ) = 0;

        //! true if widget is animated
        virtual bool isAnimated( const QObject*, WidgetIndex )
        { return false; }

        //! opacity
        virtual qreal opacity( const QObject*, WidgetIndex )
        { return -1; }

        //! return 'hover' rect position when widget is animated
        virtual QRect animatedRect( const QObject*, WidgetIndex )
        { return QRect(); }

        //! enability
        virtual void setEnabled( bool value ) = 0;

        //! max frame
        virtual void setMaxFrame( int value ) = 0;

        //! duration
        virtual void setDuration( int ) = 0;

    };

    //! stores menu hovered action and timeLine
    class MenuEngineV1: public MenuBaseEngine
    {
        Q_OBJECT

        public:

        //! constructor
        MenuEngineV1( QObject* parent ):
        MenuBaseEngine( parent )
        {}

        //! destructor
        virtual ~MenuEngineV1( void )
        {}

        //! register menubar
        virtual bool registerWidget( QWidget* );

        //! true if widget is animated
        virtual bool isAnimated( const QObject* object, WidgetIndex index )
        { return (bool) timeLine( object, index ); }

        //! animation opacity
        virtual qreal opacity( const QObject* object, WidgetIndex index )
        {
            TimeLine::Pointer timeLine( MenuEngineV1::timeLine( object, index ) );
            return timeLine ? timeLine->ratio() : -1;
        }

        //! return 'hover' rect position when widget is animated
        virtual QRect animatedRect( const QObject*, WidgetIndex );

        //! enability
        virtual void setEnabled( bool value )
        {
            BaseEngine::setEnabled( value );
            data_.setEnabled( value );
        }

        //! duration
        virtual void setDuration( int duration )
        {
            BaseEngine::setDuration( duration );
            foreach( const DataMap<MenuDataV1>::Value& value, data_ )
            { value->setDuration( duration ); }
        }

        //! max frame
        virtual void setMaxFrame( int value )
        {
            BaseEngine::setMaxFrame( value );
            data_.setMaxFrame( value );
        }

        protected slots:

        //! remove widget from map
        virtual void unregisterWidget( QObject* object )
        { if( object ) data_.remove( object ); }

        protected:

        //! return timeLine associated to action at given position, if any
        virtual TimeLine::Pointer timeLine( const QObject*, WidgetIndex );

        private:

        //! data map
        DataMap<MenuDataV1> data_;

    };

}

#endif