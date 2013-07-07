#include "StdAfx.h"
#include "VrResrouceFactoryCL.h"

VrResrouceFactoryCL::VrResrouceFactoryCL(void)
{
}

VrResrouceFactoryCL::~VrResrouceFactoryCL(void)
{
}

Gdiplus::Bitmap * VrResrouceFactoryCL::CreateImgM( LPCTSTR fileName )
{
   Gdiplus::Bitmap * pBitmap = NULL ;

   CFileFind fd ;
   if ( fd.FindFile( fileName ) )
   {
      WCHAR filePathC[MAX_PATH] ;
      ::MultiByteToWideChar( CP_ACP, 0, fileName, -1, filePathC, MAX_PATH ) ;

      pBitmap = new Gdiplus::Bitmap( filePathC ) ;
   }
   return pBitmap;
}