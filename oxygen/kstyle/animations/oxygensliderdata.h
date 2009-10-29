#ifndef oxygensliderdata_h
#define oxygensliderdata_h

//////////////////////////////////////////////////////////////////////////////
// oxygensliderdata.h
// stores event filters and maps sliders to timelines for animations
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

#include "oxygengenericdata.h"

#include <QtGui/QStyle>
#include <QtGui/QStyleOptionSlider>

namespace Oxygen
{

    //! scrollbar data
    class SliderData: public GenericData
    {

        Q_OBJECT

        public:

        //! constructor
        SliderData( QObject* parent, QWidget* target, int maxFrame, int duration ):
        GenericData( parent, target, maxFrame, duration ),
        sliderHovered_( false )
        {}

        //! destructor
        virtual ~SliderData( void )
        {}

        //! event filter
        virtual bool eventFilter( QObject*, QEvent* );

        protected:

        //! hoverMoveEvent
        virtual void hoverMoveEvent( QObject*, QEvent* );

        //! hoverMoveEvent
        virtual void hoverLeaveEvent( QObject*, QEvent* );

        //! hover
        virtual bool sliderHovered( void ) const
        { return sliderHovered_; }

        //! hover
        virtual void setSliderHovered( bool value )
        { sliderHovered_ = value; }

        //! update slider
        virtual void updateSlider( QStyle::SubControl );

        private:

        //! true when slider is hovered
        bool sliderHovered_;

    };

}

#endif