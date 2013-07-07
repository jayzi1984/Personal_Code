#include "StdAfx.h"
#include "VrPaintCheckCL.h"
#include "VrPaintInfoCL.h"
#include "VrResrouceFactoryCL.h"

VrPaintCheckCL::VrPaintCheckCL(void)
{
   pBKGPicM = NULL ;

   pRingPicM = NULL ;

   pParentM = NULL ;

   selIdM = -1 ;

   subFolderDirM = _T("") ;
}

VrPaintCheckCL::~VrPaintCheckCL(void)
{
   if ( pBKGPicM != NULL)
   {
      delete pBKGPicM ;
      pBKGPicM = NULL ;
   }
   if ( pRingPicM != NULL )
   {
      delete pRingPicM ;
      pRingPicM = NULL ;
   }
}

void VrPaintCheckCL::compuateRealRectM( const CRect & rc )
{
   float scale1 = float ( szBKGM.cx ) / float ( szBKGM.cy ) ;
   float scale2 = float ( rc.Width() ) / float ( rc.Height() ) ;
   BOOL bWid = scale1 > scale2 ? TRUE : FALSE ;

   int x, y ;
   int realWidth, realHeight ;
   if ( bWid )
   {
      x = rc.left ;
      realWidth = rc.Width() ;
      realHeight = int ( float ( szBKGM.cy ) / float ( szBKGM.cx ) * float ( rc.Width() ) ) ;
      y = rc.top + ( rc.Height() - realHeight ) / 2 ;
   }
   else
   {
      y = rc.top ;
      realHeight = rc.Height() ;
      realWidth = int ( float ( szBKGM.cx ) / float ( szBKGM.cy ) * float ( rc.Height() ) ) ;
      x = rc.left + ( rc.Width() - realWidth ) / 2 ;
   }

   realRcM = CRect( x, y, x + realWidth, y + realHeight ) ;
}

BOOL VrPaintCheckCL::CreateM( LPCTSTR workDir, const CRect & rc, CWnd * pParent, int nID )
{
   pParentM = pParent ;
   subFolderDirM = workDir ;
   subFolderDirM += _T("\\Virtual4SRes\\Ctrl\\PaintCheck\\") ;

   CString bkPath, ringPath ;
   VrPaintInfoCL reader( subFolderDirM + _T("config.txt") ) ;
   reader.GetBKPicInfoM( bkPath, szBKGM );
   reader.GetRingPicInfoM( ringPath, szRingM ) ;
   reader.GetPaintCheckInfoM( paintCheckInfoLstM ) ;
   
   compuateRealRectM( rc ) ;

   if ( CWnd::Create( NULL, "VrPaintCheckCL", WS_VISIBLE | WS_CHILD, realRcM, pParent, nID ) == FALSE )
   {
      TRACE0( _T( "VrPaintCheckCL Create Failed!" ) ) ;
      return FALSE ;
   }

   VrResrouceFactoryCL factory ;
   if ( pBKGPicM == NULL && bkPath != _T("") )
   {
      pBKGPicM = factory.CreateImgM( subFolderDirM + bkPath ); 
   }
   if ( pRingPicM == NULL && ringPath != _T("") )
   {
      pRingPicM = factory.CreateImgM( subFolderDirM + ringPath ) ;
   }

   if ( pBKGPicM == NULL || pRingPicM == NULL )
   {
      TRACE0( _T("PaintCheck Img Create Failed!") ) ;
   }

   pParent->InvalidateRect( NULL, FALSE ) ;

   return TRUE ;
}

void VrPaintCheckCL::DrawM( Gdiplus::Graphics * graphics )
{
   if ( pBKGPicM != NULL && pRingPicM != NULL )
   {
      graphics->DrawImage( pBKGPicM, Gdiplus::RectF( realRcM.left, realRcM.top, realRcM.Width(), realRcM.Height() ) ) ;

      int size = int ( paintStateLstM.size() ) ;

      for ( int i=0; i<size; i++ )
      {
         if ( 1 == paintStateLstM[i] )
         {
            CRect realRc;
            changAbsoluteToRealRectM( paintCheckInfoLstM[i].drawX, paintCheckInfoLstM[i].drawY, szRingM, realRc );
            graphics->DrawImage( pRingPicM, Gdiplus::RectF( realRc.left, realRc.top, realRc.Width(), realRc.Height() ) ) ;
         }
      }
   }
}

void VrPaintCheckCL::SetPaintStateM( LPCTSTR paintState )
{
   CString tmp = paintState ;
   ASSERT( tmp.GetLength() == 11 ) ;

   paintStateLstM.resize( 11 ) ;

   for ( int i=0; i<11; i++ )
   {
      TCHAR letter = tmp.GetAt( i ) ;
      paintStateLstM[i] = _ttoi( &letter ) ;
   }

   pParentM->InvalidateRect( NULL, FALSE ) ; 
}

void VrPaintCheckCL::GetPaintStateM( CString & paintState )
{
   int size = int ( paintStateLstM.size() ) ;
   for ( int i=0; i<size; i++ )
   {
      CString tmp ;
      tmp.Format ( _T("%d"), paintStateLstM[i] ) ;
      paintState += tmp ;
   }
}

void VrPaintCheckCL::changAbsoluteToRealRectM( const CRect & absoluteRc, CRect & realRc )
{
   float scale = float ( realRcM.Width() ) / float ( szBKGM.cx ) ;

   realRc.top = LONG ( absoluteRc.top * scale ) ;
   realRc.left = LONG ( absoluteRc.left * scale ) ;
   realRc.bottom = LONG ( absoluteRc.bottom * scale ) ;
   realRc.right = LONG ( absoluteRc.right * scale ) ;
}

void VrPaintCheckCL::changAbsoluteToRealRectM( int absoluteX, int absoluteY, CSize absoluteSize, CRect & realRc )
{
   CRect rc( absoluteX, absoluteY, absoluteX + absoluteSize.cx, absoluteY + absoluteSize.cy ) ;

   changAbsoluteToRealRectM( rc, realRc ) ;

   realRc.OffsetRect( realRcM.left, realRcM.top ) ;
}

int VrPaintCheckCL::checkSelectAreaM( CPoint point )
{
   int sel = -1 ;
   int size = int ( paintCheckInfoLstM.size() ) ;
   for ( int i=0; i<size; i++ )
   {
      CRect realRc ;
      changAbsoluteToRealRectM( paintCheckInfoLstM[i].selRc, realRc ) ;

      if ( realRc.PtInRect( point ) )
      {
         sel = i ;
         break ;
      }
   }
   return sel ;
}

BEGIN_MESSAGE_MAP(VrPaintCheckCL, CWnd)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void VrPaintCheckCL::OnLButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   ASSERT( selIdM == -1 ) ;
   selIdM = checkSelectAreaM( point ) ;

   CWnd::OnLButtonDown(nFlags, point);
}

void VrPaintCheckCL::OnLButtonUp(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   if ( selIdM >= 0 )
   {
      int reSelId = checkSelectAreaM( point ) ;

      if ( selIdM == reSelId )
      {
         paintStateLstM[ selIdM ] = ! paintStateLstM[ selIdM ] ;
      }

      selIdM = -1 ;
   }

   pParentM->InvalidateRect( NULL, FALSE ) ;
   CWnd::OnLButtonUp(nFlags, point);
}

LRESULT VrPaintCheckCL::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
   // TODO: 在此添加专用代码和/或调用基类
   /*if ( WM_LBUTTONDOWN == message )
   {
   }*/

   return CWnd::WindowProc(message, wParam, lParam);
}
