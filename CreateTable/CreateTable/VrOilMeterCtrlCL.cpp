#include "StdAfx.h"
#include "VrOilMeterCtrlCL.h"
#include "VrOilMeterInfoCL.h"
#include "VrResrouceFactoryCL.h"

#include <Math.h>

#define ANGLE_CALIBRATION 0.196f

VrOilMeterCtrlCL::VrOilMeterCtrlCL(void)
{
   pParentM = NULL ;

   subFolderM = _T("") ;

   stateM = 0 ;

   smallRadiusM = -1 ;

   bigRadiusM = -1;

   lastStateM = -1 ;
}

VrOilMeterCtrlCL::~VrOilMeterCtrlCL(void)
{
   int size = int ( imgLstM.size() ) ;
   for ( int i=0; i<size; i++ )
   {
      if ( imgLstM[i] != NULL )
      {
         delete imgLstM[i] ;
         imgLstM[i] = NULL ;
      }
   }
   imgLstM.clear() ;
}

void VrOilMeterCtrlCL::perpareDataM()
{
   VrOilMeterInfoCL reader( subFolderM + _T( "config.txt" ) ) ;

   std::vector< CString > picNameLst ;
   reader.GetPicNameLstM( picNameLst ) ;
   szPicM = reader.GetPicSizeM() ;
   reader.GetCirInfoM( cirCenterPntM, smallRadiusM, bigRadiusM ) ;

   VrResrouceFactoryCL factory ;
   int size = int ( picNameLst.size() ) ;
   for( int i=0; i<size; i++ )
   {
      Gdiplus::Bitmap * pBitmap = factory.CreateImgM( subFolderM + picNameLst[i] ) ;
      if ( pBitmap != NULL )
      {
         imgLstM.push_back( pBitmap ) ;
      }
   }
}

void VrOilMeterCtrlCL::compuateRealRectM( const CRect & rc )
{
   BOOL bWid = rc.Width() > rc.Height() ? FALSE : TRUE ;
   
   int x, y ;
   int width, height ;
   if ( bWid )
   {
      x = rc.left ;
      y = rc.top + ( rc.Height() - rc.Width() ) / 2 ;
      width = rc.Width() ;
      height = rc.Width() ;
   }
   else
   {
      x = rc.left + ( rc.Width() - rc.Height() ) / 2 ;
      y = rc.top ;
      width = rc.Height() ;
      height = rc.Height() ;
   }

   realRcM = CRect( x, y, x + width, y + height ) ;
}

BOOL VrOilMeterCtrlCL::CreateM( LPCTSTR workDir, const CRect & rc, CWnd * pParent, int nID )
{
   subFolderM = workDir ;
   subFolderM += _T( "\\Virtual4SRes\\Ctrl\\OilMeter\\" ) ;
   pParentM = pParent ;

   perpareDataM() ;
   compuateRealRectM( rc ) ;

   if ( CWnd::Create( NULL, _T("VrOilMeterCtrlCL"), WS_CHILD | WS_VISIBLE, realRcM, pParent, nID ) == FALSE )
   {
      TRACE0( _T("VrOilMeterCtrlCL Create Failed!") ) ;
      return FALSE ;
   }

   pParent->InvalidateRect( NULL, FALSE ) ;
   return TRUE ;
}

void VrOilMeterCtrlCL::DrawM( Gdiplus::Graphics * graphics )
{
   if ( graphics != NULL && stateM >= 0 && stateM < int ( imgLstM.size() ) && imgLstM[stateM] != NULL )
   {
      graphics->DrawImage( imgLstM[stateM], Gdiplus::RectF( realRcM.left, realRcM.top, realRcM.Width(), realRcM.Height() ) ) ;
   }
}

int VrOilMeterCtrlCL::compuateStateM( const CPoint & pnt )
{
   int retVal = -1 ;
   float scale = float( realRcM.Width() ) / float( szPicM.cx ) ;

   int centX = int ( float ( cirCenterPntM.x ) * scale ) ;
   int centY = int ( float ( cirCenterPntM.y ) * scale ) ;
   int front = int ( float ( smallRadiusM ) * scale ) ;
   int back  = int ( float ( bigRadiusM ) * scale ) ;

   float dis = sqrt( float ( ( centX - pnt.x ) * ( centX - pnt.x ) ) + float ( ( centY - pnt.y ) * ( centY - pnt.y ) ) ) ;

   if( dis >= front && dis <= back && pnt.x > centX && pnt.y < centY )
   {
      float angle = asin( float( centY - pnt.y ) / dis ) ;

      retVal = int ( angle / ANGLE_CALIBRATION ) + 1;

      if ( retVal > 9 )
      {
         retVal = 9 ;
      }
   }

   return retVal ;
}

BEGIN_MESSAGE_MAP(VrOilMeterCtrlCL, CWnd)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void VrOilMeterCtrlCL::OnLButtonDown(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   int state = compuateStateM( point ) ;
   if ( state != -1 )
   {
      lastStateM = state ;
   }
   CWnd::OnLButtonDown(nFlags, point);
}

void VrOilMeterCtrlCL::OnLButtonUp(UINT nFlags, CPoint point)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值
   int state = compuateStateM( point ) ;
   if ( state == lastStateM && state != -1 )
   {
      stateM = state ;
   }
   lastStateM = -1 ;

   pParentM->InvalidateRect( NULL, FALSE ) ;
   CWnd::OnLButtonUp(nFlags, point);
}
