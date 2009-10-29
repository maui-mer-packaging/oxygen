#ifndef oxygengenericdata_h
#define oxygengenericdata_h

//////////////////////////////////////////////////////////////////////////////
// oxygenwidgetdata.h
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

#include "oxygenwidgetdata.h"

namespace Oxygen
{


    //! generic data
    class GenericData: public WidgetData
    {

        Q_OBJECT

        public:

        //! constructor
        GenericData( QObject* parent, QWidget* target, int maxFrame, int duration );

        //! destructor
        virtual ~GenericData( void )
        {}

        //! return timeLine
        virtual const TimeLine::Pointer& timeLine() const
        { return timeLine_; }

        //! duration
        virtual void setDuration( int duration )
        { timeLine_->setDuration( duration ); }

        //! maxFrame
        virtual void setMaxFrame( int maxFrame )
        { timeLine_->setFrameRange( 0, maxFrame ); }

        private:

        TimeLine::Pointer timeLine_;

    };

}

#endif