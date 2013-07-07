#include "StdAfx.h"
#include "VrPaintInfoCL.h"

VrPaintInfoCL::VrPaintInfoCL( LPCTSTR fileName )
{
   CStdioFile fp ;
   if ( fp.Open( fileName, CFile::modeRead ) )
   {
      BOOL bOK = readPictureInfoM( fp ) ;
      if ( bOK )
      {
         bOK = readPaintCheckInfoM( fp, paintCheckInfoLstM ) ;
      }
   }
   else
   {
      TRACE0( _T("PaintCheck Config Fail!") ) ;
   }
}

VrPaintInfoCL::~VrPaintInfoCL(void)
{
}

void VrPaintInfoCL::GetPaintCheckInfoM( std::vector< PaintCheckInfoD > & paintCheckInfoLst )
{
   paintCheckInfoLst = paintCheckInfoLstM ;
}

void VrPaintInfoCL::GetBKPicInfoM( CString & bkFileName, CSize & sz )
{
   bkFileName = bkgM;

   sz = szBKM;
}

void VrPaintInfoCL::GetRingPicInfoM( CString & ringFileName, CSize & sz )
{
   ringFileName = ringM;

   sz = szRingM;
}

BOOL VrPaintInfoCL::readPaintCheckInfoM( CStdioFile &fp, std::vector< PaintCheckInfoD > & paintCheckInfoLst )
{
   BOOL bOK = SearchOneStringM( fp, _T("[ÏÔÊ¾×ø±ê]") ) ;

   if ( bOK )
   {
      int numI ;

      bOK = ReadOneIntegerM( fp, numI ) ;
      SkipLinesM(fp, 7);

      paintCheckInfoLst.resize( numI ) ;
      for ( int i=0; i<numI && bOK; i++ )
      {
         int idx, selX, selY, selW, selH;
         PaintCheckInfoD tmpInfo;
         bOK = ReadOneIntegerM( fp, idx ) ;
         if ( bOK )
         {
            bOK = ReadOneIntegerM( fp, selX ) ;
         }
         if ( bOK )
         {
            bOK = ReadOneIntegerM( fp, selY ) ;
         }
         if ( bOK )
         {
            bOK = ReadOneIntegerM( fp, selW ) ;
         }
         if ( bOK )
         {
            bOK = ReadOneIntegerM( fp, selH ) ;
         }
         if ( bOK )
         {
            bOK = ReadOneIntegerM( fp, tmpInfo.drawX ) ;
         }
         if ( bOK )
         {
            bOK = ReadOneIntegerM( fp, tmpInfo.drawY ) ;
         }
         if ( bOK )
         {
            tmpInfo.selRc = CRect ( selX, selY, selX + selW, selY + selH ) ;
         }
         if (idx < numI)
            paintCheckInfoLst[idx] = tmpInfo ;
         else
            TRACE0( _T("out of range!") ) ;
      }
   }
   return bOK;
}

BOOL VrPaintInfoCL::readPictureInfoM( CStdioFile &fp )
{
   BOOL bOK = SearchOneStringM( fp, _T("[Í¼Æ¬]") ) ;

   if ( bOK )
   {
      int numI ;

      bOK = ReadOneIntegerM( fp, numI ) ;
      SkipLinesM(fp, 3);

      for ( int i=0; i<numI && bOK; i++ )
      {
         int width, height;
         if ( 0 == i )
         {
            bOK = ReadStringM( fp, bkgM ) ;
            if ( bOK )
            {
               bOK = ReadOneIntegerM( fp, width ) ;
            }
            if ( bOK )
            {
               bOK = ReadOneIntegerM( fp, height ) ;
            }
            if ( bOK )
            {
               szBKM = CSize( width, height ) ;
            }
         }
         else if ( 1 == i ) 
         {
            bOK = ReadStringM( fp, ringM ) ;
            if ( bOK )
            {
               bOK = ReadOneIntegerM( fp, width ) ;
            }
            if ( bOK )
            {
               bOK = ReadOneIntegerM( fp, height ) ;
            }
            if ( bOK )
            {
               szRingM = CSize( width, height ) ;
            }
         }
      }
   }
   return bOK;
}