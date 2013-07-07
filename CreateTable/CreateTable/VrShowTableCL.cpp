#include "StdAfx.h"
#include "VrShowTableCL.h"

VrShowTableCL::VrShowTableCL(void)
{
}

VrShowTableCL::~VrShowTableCL(void)
{
}

BOOL VrShowTableCL::CreateM( const CRect & rc, CWnd * pParent, int nID )
{
   if ( ! CWnd::Create( NULL, _T( "VrShowTableCL" ), WS_CHILD | WS_VISIBLE, rc, pParent, nID ) )
   {
      ::AfxMessageBox( _T("VrShowTableCL Create Failed !") ) ;
      return FALSE ;
   }

   rcM = rc ;
   return TRUE ;
}

void VrShowTableCL::DrawM( CDC * pDC )
{

}