//////////////////////////////////////////////////////////////////////////////
// nitrogenexceptionlist.cpp
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

#include <QTextStream>

#include "nitrogenexceptionlist.h"

namespace Nitrogen
{

  //______________________________________________________________
  void NitrogenExceptionList::read( const KConfig& config )
  {

    clear();

    for( int index = 0; true; index++ )
    {

      KConfigGroup group( &config, exceptionGroupName( index ) );
      if( group.exists() )
      {
        NitrogenException exception( group );
        if( exception.regExp().isValid() ) push_back( exception );
      } else break;

    }

  }

  //______________________________________________________________
  void NitrogenExceptionList::write( KConfig& config )
  {

    // remove previous group
    for( int index = 0; true ;index++ )
    {
      KConfigGroup group( &config, exceptionGroupName( index ) );
      if( group.exists() ) group.deleteGroup();
      else break;
    }

    // also add exceptions
    int index(0);
    for( NitrogenExceptionList::const_iterator iter = constBegin(); iter != constEnd(); iter++, index++ )
    {

      KConfigGroup group( &config, exceptionGroupName( index ) );
      iter->write( group );

    }


  }

  //______________________________________________________________
  NitrogenExceptionList NitrogenExceptionList::defaultList( void )
  {

    NitrogenExceptionList out;

    // default exception that covers most commonly used gtk based applications
    NitrogenException exception;
    exception.setType( NitrogenException::WindowClassName );
    exception.regExp().setPattern( "(Firefox)|(Thunderbird)|(Gimp)" );
    exception.setBlendColor( NitrogenException::NoBlending );
    exception.setMask( NitrogenException::BlendColor );
    exception.setEnabled( true );

    out.push_back( exception );
    return out;

  }

  //_______________________________________________________________________
  QString NitrogenExceptionList::exceptionGroupName( int index )
  {
    QString out;
    QTextStream( &out ) << "Windeco Exception " << index;
    return out;
  }


}