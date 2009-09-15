#ifndef nitrogenconfiguration_h
#define nitrogenconfiguration_h

//////////////////////////////////////////////////////////////////////////////
// nitrogenconfiguration.h
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

#include <KConfigGroup>

namespace NitrogenConfig
{

  static const QString TITLE_ALIGNMENT = "TitleAlignment";
  static const QString BUTTON_SIZE = "ButtonSize";
  static const QString DRAW_SEPARATOR = "DrawSeparator";
  static const QString DRAW_TITLE_OUTLINE = "DrawTitleOutline";
  static const QString FRAME_BORDER = "FrameBorder";
  static const QString BLEND_COLOR = "BlendColor";
  static const QString SIZE_GRIP_MODE = "SizeGripMode";
  static const QString USE_OXYGEN_SHADOWS = "UseOxygenShadows";

}

namespace Nitrogen
{

  class NitrogenConfiguration
  {

    public:

    //! button size enumeration
    enum ButtonSize
    {
      ButtonSmall = 18,
      ButtonDefault = 22,
      ButtonLarge = 32,
      ButtonHuge = 48
    };

    //! frame border enumeration
    enum FrameBorder
    {
      BorderNone = 0,
      BorderNoSide = 1,
      BorderTiny = 2,
      BorderDefault = 4,
      BorderLarge = 8,
      BorderVeryLarge = 12,
      BorderHuge = 18,
      BorderVeryHuge = 27,
      BorderOversized = 40
    };

    //! blend color enumeration
    enum BlendColorType {
      NoBlending,
      RadialBlending
    };

    //! size grip mode
    enum SizeGripMode
    {
      SizeGripNever,
      SizeGripWhenNeeded
    };

    //! default constructor
    NitrogenConfiguration( void );

    //! constructor from KConfig
    NitrogenConfiguration( KConfigGroup );

    //! destructor
    virtual ~NitrogenConfiguration( void )
    {}

    //! equal to operator
    bool operator == ( const NitrogenConfiguration& ) const;

    //! write to kconfig group
    virtual void write( KConfigGroup& ) const;

    //!@name title alignment
    //@{

    static QString titleAlignmentName( Qt::Alignment, bool translated );
    static Qt::Alignment titleAlignment( QString, bool translated );

    virtual Qt::Alignment titleAlignment() const
    { return titleAlignment_; }

    virtual QString titleAlignmentName( bool translated ) const
    { return titleAlignmentName( titleAlignment(), translated ); }

    virtual void setTitleAlignment( Qt::Alignment value )
    { titleAlignment_ = value; }

    virtual void setTitleAlignment( QString value, bool translated )
    { titleAlignment_ = titleAlignment( value, translated ); }

    //@}

    //!@name button size
    //@{

    static QString buttonSizeName( ButtonSize, bool translated );
    static ButtonSize buttonSize( QString, bool translated );
    static int iconScale( ButtonSize );

    virtual ButtonSize buttonSize( void ) const
    { return buttonSize_; }

    virtual int iconScale( void ) const
    { return iconScale( buttonSize() ); }

    virtual QString buttonSizeName( bool translated ) const
    { return buttonSizeName( buttonSize(), translated ); }

    virtual void setButtonSize( ButtonSize value )
    { buttonSize_ = value; }

    //@}

    //!@name frame border
    //@{

    static QString frameBorderName( FrameBorder, bool translated );
    static FrameBorder frameBorder( QString, bool translated );

    virtual FrameBorder frameBorder() const
    { return frameBorder_; }

    virtual QString frameBorderName( bool translated ) const
    { return frameBorderName( frameBorder(), translated ); }

    virtual void setFrameBorder( FrameBorder value )
    { frameBorder_ = value; }

    virtual void setFrameBorder( QString value, bool translated )
    { frameBorder_ = frameBorder( value, translated ); }

    //@}

    //!@name blend color
    //@{

    static QString blendColorName( BlendColorType, bool translated );
    static BlendColorType blendColor( QString, bool translated );

    virtual BlendColorType blendColor( void ) const
    { return blendColor_; }

    virtual QString blendColorName( bool translated ) const
    { return blendColorName( blendColor(), translated ); }

    virtual void setBlendColor( BlendColorType value )
    { blendColor_ = value; }

    virtual void setBlendColor( QString value, bool translated )
    { blendColor_ = blendColor( value, translated ); }

    //@}

    //!@name size grip
    //@{

    static QString sizeGripModeName( SizeGripMode, bool translated );
    static SizeGripMode sizeGripMode( QString, bool translated );

    virtual SizeGripMode sizeGripMode( void ) const
    { return sizeGripMode_; }

    virtual QString sizeGripModeName( bool translated ) const
    { return sizeGripModeName( sizeGripMode(), translated ); }

    virtual void setSizeGripMode( SizeGripMode value )
    { sizeGripMode_ = value; }

    virtual void setSizeGripMode( QString value, bool translated )
    { sizeGripMode_ = sizeGripMode( value, translated ); }

    //! draw size grip
    virtual bool drawSizeGrip( void ) const
    { return (sizeGripMode() == SizeGripWhenNeeded && frameBorder() == BorderNone ); }

    //@}

    //! separator
    virtual bool drawSeparator( void ) const
    { return drawSeparator_; }

    //! separator
    virtual void setDrawSeparator( bool value )
    { drawSeparator_ = value; }

    //! title outline
    virtual bool drawTitleOutline( void ) const
    { return drawTitleOutline_; }

    //! title outline
    virtual void setDrawTitleOutline( bool value )
    { drawTitleOutline_ = value; }

    //! oxygen shadows
    virtual bool useOxygenShadows( void ) const
    { return useOxygenShadows_; }

    //! oxygen shadows
    virtual void setUseOxygenShadows( bool value )
    { useOxygenShadows_ = value; }

    private:

    //! title alignment
    Qt::Alignment titleAlignment_;

    //! button size
    ButtonSize buttonSize_;

    //! blend color
    FrameBorder frameBorder_;

    //! frame border
    BlendColorType blendColor_;

    //! size grip mode
    SizeGripMode sizeGripMode_;

    //! separator
    bool drawSeparator_;

    //! active window title outline
    bool drawTitleOutline_;

    //! oxygen shadows
    bool useOxygenShadows_;

  };

}

#endif