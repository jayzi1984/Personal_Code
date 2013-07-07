#pragma once

#include "VrGroupLstCL.h"
#include "VrShowTableCL.h"

class VrTableBaseCL : public CWnd
{
   
public:
   VrTableBaseCL(void) ;
   virtual ~VrTableBaseCL(void) ;

   void DrawM(CDC * pDC) ;

   BOOL CreateM( const CRect & rc, CWnd * pParent, int nID ) ;


private:

   CWnd * pParentM;  //¸¸´°¿ÚÖ¸Õë

   VrGroupLstCL groupLstCtrlM;

   VrShowTableCL showTableCtrlM;
};
