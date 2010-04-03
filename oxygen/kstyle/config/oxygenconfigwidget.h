#ifndef oxygenconfigwidget_h
#define oxygenconfigwidget_h

//////////////////////////////////////////////////////////////////////////////
// oxygenconfigwidget.h
// configuration widget
// -------------------
//
// Copyright (c) 2010 Hugo Pereira Da Costa <hugo@oxygen-icons.org>
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

#include <QtGui/QWidget>


namespace Oxygen
{

    class ConfigWidget: public QWidget
    {

        Q_OBJECT

        public:

        //! constructor
        explicit ConfigWidget( QWidget* parent = 0 ):
            QWidget( parent ),
            changed_( false )
        {}

        //! true if changed
        virtual bool isChanged( void ) const
        { return changed_; }

        signals:

        //! emmited when changed
        void changed( bool );

        protected:

        //! set changed state
        virtual void setChanged( bool value )
        {
            changed_ = value;
            emit changed( value );
        }

        private:

        //! changed state
        bool changed_;

    };
}

#endif
