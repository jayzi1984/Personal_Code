#include "StdAfx.h"
#include "VrOilMeterInfoCL.h"

VrOilMeterInfoCL::VrOilMeterInfoCL( LPCTSTR fileName )
{
   CStdioFile fp ;
   if ( fp.Open( fileName, CFile::modeRead ) == TRUE )
   {
      BOOL bOK = readPicNameLstM( fp, picNameLstM ) ;
      if ( bOK )
      {
         bOK = readPicInfoM( fp ) ;
      }
   }
}

VrOilMeterInfoCL::~VrOilMeterInfoCL(void)
{
}

void VrOilMeterInfoCL::GetPicNameLstM( std::vector<CString> & picNameLst )
{
   picNameLst = picNameLstM ;
}

CSize VrOilMeterInfoCL::GetPicSizeM()
{
   return szPicM ;
}

void VrOilMeterInfoCL::GetCirInfoM( CPoint & point, int & smallRadius, int & bigRadius )
{
   point = cirCenterM ;

   smallRadius = smallRadiusM ;

   bigRadius = bigRadiusM ;
}

BOOL VrOilMeterInfoCL::readPicNameLstM( CStdioFile & fp, std::vector<CString> & picNameLst )
{
   BOOL bOK = SearchOneStringM( fp, "[Img]" ) ;

   if ( bOK )
   {
      int numI ;
      bOK = ReadOneIntegerM( fp, numI ) ;
      picNameLst.resize( numI ) ;

      SkipLinesM( fp, 2 ) ;

      for ( int i=0; i<numI && bOK; i++ )
      {
         int idx ;
         bOK = ReadOneIntegerM( fp, idx ) ;
         if ( bOK )
         {
            bOK = ReadStringM( fp, picNameLstM[i] ) ;
         }
      }
   }

   return bOK ;
}

BOOL VrOilMeterInfoCL::readPicInfoM( CStdioFile & fp )
{
   BOOL bOK = SearchOneStringM( fp, _T("[ImgInfo]") ) ;

   if ( bOK )
   {
      SkipLinesM( fp, 6 ) ;

      int cx, cy, pntx, pnty ;
      bOK = ReadOneIntegerM( fp, cx ) ;
      if ( bOK )
      {
         bOK = ReadOneIntegerM( fp, cy ) ;
      }
      if ( bOK )
      {
         bOK = ReadOneIntegerM( fp, pntx ) ;
      }
      if ( bOK )
      {
         bOK = ReadOneIntegerM( fp, pnty ) ;
      }
      if ( bOK )
      {
         bOK = ReadOneIntegerM( fp, smallRadiusM ) ;
      }
      if ( bOK )
      {
         bOK = ReadOneIntegerM( fp, bigRadiusM ) ;
      }
      if ( bOK )
      {
         szPicM = CSize( cx, cy ) ;

         cirCenterM = CPoint( pntx, pnty ) ;
      }
   }

   return bOK ;
}