#ifndef nitrogenclient_h
#define nitrogenclient_h

//////////////////////////////////////////////////////////////////////////////
// nitrogenclient.h
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
// Copyright (c) 2003, 2004 David Johnson <david@usermode.org>
// Copyright (c) 2006, 2007 Riccardo Iaconelli <ruphy@fsfe.org>
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

#include <kcommondecoration.h>

#include "kdeversion.h"
#include "nitrogenconfiguration.h"
#include "lib/helper.h"
#include "lib/tileset.h"


namespace Nitrogen
{

    class NitrogenSizeGrip;

    class NitrogenClient : public KCommonDecorationUnstable
    {

        Q_OBJECT

        public:

        //! constructor
        NitrogenClient(KDecorationBridge *b, KDecorationFactory *f);

        //! destructor
        virtual ~NitrogenClient();

        virtual QString visibleName() const;
        virtual KCommonDecorationButton *createButton(::ButtonType type);
        virtual bool decorationBehaviour(DecorationBehaviour behaviour) const;

        //! true if window is maximized
        virtual bool isMaximized( void ) const;

        //! true when separator is to be drawn
        virtual bool drawSeparator( void ) const
        { return isActive() && configuration().drawSeparator() && !configuration().drawTitleOutline(); }

        //! true when oxygen 'glow' shadow is to be drawn for active window
        virtual bool useOxygenShadows( void ) const
        { return isActive() && configuration().useOxygenShadows(); }

        //! dimensions
        virtual int layoutMetric(LayoutMetric lm, bool respectWindowState = true, const KCommonDecorationButton * = 0) const;

        //! window shape
        virtual void updateWindowShape();

        //! initialization
        virtual void init();

        // reset
        virtual void reset( unsigned long changed );

        //! return associated configuration
        NitrogenConfiguration configuration( void ) const;

        //! helper class
        OxygenHelper& helper( void ) const
        { return helper_; }

        //! palette background
        QPalette backgroundPalette( const QWidget*, QPalette ) const;

        //! window background
        virtual void renderWindowBackground( QPainter*, const QRect&, const QWidget*, const QPalette& ) const;

        //! window border
        // this draws a "blue" border around active window
        virtual void renderWindowBorder( QPainter*, const QRect&, const QWidget*, const QPalette& ) const;

        //! title outline
        virtual void renderTitleOutline( QPainter*, const QRect&, const QPalette& ) const;

        //! triggered when window activity is changed
        virtual void activeChange();

        //! triggered when maximize state changed
        virtual void maximizeChange();

        //! triggered when window shade is changed
        virtual void shadeChange();

        public slots:

        //! reset configuration
        void resetConfiguration( void );

        protected:

        //! paint
        void paintEvent( QPaintEvent* );

        //! shadows
        TileSet *shadowTiles(const QColor& color, bool active);

        //! shadows
        QPixmap shadowPixmap( const QColor& color, bool active ) const;

        private:

        class ShadowTilesOption {

          public:

          //! constructor
          ShadowTilesOption( void ):
            width(0),
            active(false)
          {}

          //! equal to operator
          bool operator == ( const ShadowTilesOption& other ) const
          {
            return
              windowColor == other.windowColor &&
              innerColor == other.innerColor &&
              width == other.width &&
              active == other.active;
          }

          QColor windowColor;
          QColor innerColor;
          qreal width;
          bool active;
        };

        //! calculate mask
        QRegion calcMask( void ) const;

        //! text color
        QColor titlebarTextColor(const QPalette&);

        //!@name size grip
        //@{

        //! create size grip
        void createSizeGrip( void );

        //! delete size grip
        void deleteSizeGrip( void );

        // size grip
        bool hasSizeGrip( void ) const
        { return (bool)sizeGrip_; }

        //! size grip
        NitrogenSizeGrip& sizeGrip( void ) const
        { return *sizeGrip_; }

        //@}

        //! configuration
        NitrogenConfiguration configuration_;

        //! used to invalidate color cache
        bool colorCacheInvalid_;

        //! stored color
        QColor cachedTitlebarTextColor_;

        //! size grip widget
        NitrogenSizeGrip* sizeGrip_;

        ShadowTilesOption inactiveShadowTilesOption_;
        ShadowTilesOption activeShadowTilesOption_;
        TileSet *inactiveShadowTiles_;
        TileSet *activeShadowTiles_;

        //! helper
        OxygenHelper& helper_;

        //! true when initialized
        bool initialized_;

    };


} // namespace Nitrogen

#endif // EXAMPLECLIENT_H