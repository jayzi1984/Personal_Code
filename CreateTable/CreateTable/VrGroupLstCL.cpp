#include "StdAfx.h"
#include "VrGroupLstCL.h"

VrGroupLstCL::VrGroupLstCL(void)
{
}

VrGroupLstCL::~VrGroupLstCL(void)
{
}

BOOL VrGroupLstCL::CreateM( const CRect & rc, CWnd * pParent, int nID )
{
   if ( ! CWnd::Create( NULL, _T( "VrGroupLstCL" ), WS_CHILD | WS_VISIBLE, rc, pParent, nID ) )
   {
      ::AfxMessageBox( _T("VrGroupLstCL Create Failed !") ) ;
      return FALSE;
   }
   rcM = rc ;
   return TRUE ;
}

void VrGroupLstCL::DrawM( CDC * pDC )
{
}