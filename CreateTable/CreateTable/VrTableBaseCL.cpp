#include "StdAfx.h"
#include "VrTableBaseCL.h"

VrTableBaseCL::VrTableBaseCL(void)
{
}

VrTableBaseCL::~VrTableBaseCL(void)
{
}

void VrTableBaseCL::DrawM(CDC * pDC)
{
   groupLstCtrlM.DrawM( pDC ) ;

   showTableCtrlM.DrawM( pDC ) ;
}

BOOL VrTableBaseCL::CreateM( const CRect & rc, CWnd * pParent, int nID )
{
   if ( ! CWnd::Create( NULL, _T("VrTableBaseCL"), WS_CHILD | WS_VISIBLE, rc, pParent, nID ) )
   {
      ::AfxMessageBox( _T( "VrTableBaseCL Create Failed !" ) ) ;
      return FALSE ;
   }
   pParentM = pParent;

   //划分选择表单区域和显示表单区域
   CRect groupRc = CRect( rc.left, rc.top, rc.left + rc.Width() / 3, rc.bottom ) ;

   CRect showRc = CRect( rc.left + rc.Width() / 3, rc.top, rc.left, rc.bottom ) ;

   //创建
   groupLstCtrlM.CreateM( groupRc, this, nID + 1 ) ;

   showTableCtrlM.CreateM( showRc, this, nID + 2 ) ;

   return TRUE;

}