#ifndef oxygentimeline_h
#define oxygentimeline_h
//////////////////////////////////////////////////////////////////////////////
// oxygentimeline.h
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

#include <QtCore/QPointer>
#include <QtCore/QTimeLine>
#include <QtCore/QTextStream>

namespace Oxygen
{

    class TimeLine: public QTimeLine
    {

        Q_OBJECT

        public:

        //! TimeLine shared pointer
        typedef QPointer<TimeLine> Pointer;

        //! constructor
        TimeLine( int duration, QObject* parent ):
            QTimeLine( duration, parent )
            {}

        //! destructor
        virtual ~TimeLine( void )
        {}

        //! true if running
        bool isRunning( void ) const
        { return state() == QTimeLine::Running; }

        //! progress ratio
        qreal ratio( void ) const
        {
            static const qreal offset = 0.1;
            static const qreal scale = 1.0 - offset*2;
            return offset + scale*qreal( currentFrame() )/qreal( endFrame() );
        }

        //! restart
        void restart( void )
        {
            if( isRunning() ) stop();
            start();
        }

    };

}

#endif