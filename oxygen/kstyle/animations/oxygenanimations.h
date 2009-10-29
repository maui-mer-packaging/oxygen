#ifndef oxygenanimations_h
#define oxygenanimations_h

//////////////////////////////////////////////////////////////////////////////
// oxygenanimations.h
// container for all animation engines
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

#include "oxygengenericengine.h"
#include "oxygenmenubarengine.h"
#include "oxygenmenuengine.h"
#include "oxygenscrollbarengine.h"
#include "oxygensliderengine.h"
#include "oxygentabbarengine.h"

#include <QtCore/QObject>

namespace Oxygen
{

    //! stores engines
    class Animations: public QObject
    {

        Q_OBJECT

        public:

        //! constructor
        explicit Animations( QObject* );

        //! destructor
        virtual ~Animations( void )
        {}

        /*
        register widget; depending on its type
        returns true if widget was registered
        */

        bool registerWidget( QWidget* widget ) const;

        //! abstractButton engine
        GenericEngine& widgetEnabilityEngine( void ) const
        { return *widgetEnabilityEngine_; }

        //! abstractButton engine
        GenericEngine& abstractButtonEngine( void ) const
        { return *abstractButtonEngine_; }

        //! abstractButton engine
        GenericEngine& toolBarEngine( void ) const
        { return *toolBarEngine_; }

        //! abstractButton engine
        GenericEngine& lineEditEngine( void ) const
        { return *lineEditEngine_; }

        //! menubar engine
        MenuBarBaseEngine& menuBarEngine( void ) const
        { return *menuBarEngine_; }

        //! menu engine
        MenuBaseEngine& menuEngine( void ) const
        { return *menuEngine_; }

        //! abstractButton engine
        ScrollBarEngine& scrollBarEngine( void ) const
        { return *scrollBarEngine_; }

        //! abstractButton engine
        SliderEngine& sliderEngine( void ) const
        { return *sliderEngine_; }

        //! tabbar
        TabBarEngine& tabBarEngine( void ) const
        { return *tabBarEngine_; }

        public slots:

        //! setup engines
        void setupEngines( void );

        private:

        //! widget enability engine
        GenericEngine* widgetEnabilityEngine_;

        //! abstract button engine
        GenericEngine* abstractButtonEngine_;

        //! tool button engine
        GenericEngine* toolBarEngine_;

        //! line editor engine
        GenericEngine* lineEditEngine_;

        //! menubar engine
        MenuBarBaseEngine* menuBarEngine_;

        //! menu engine
        MenuBaseEngine* menuEngine_;

        //! scrollbar engine
        ScrollBarEngine* scrollBarEngine_;

        //! slider engine
        SliderEngine* sliderEngine_;

        //! tabbar engine
        TabBarEngine* tabBarEngine_;

    };

}

#endif
