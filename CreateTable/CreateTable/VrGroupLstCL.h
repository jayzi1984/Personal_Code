#pragma once

class VrGroupLstCL : public CWnd
{
public:
   VrGroupLstCL(void);
   ~VrGroupLstCL(void);

   BOOL CreateM( const CRect & rc, CWnd * pParent, int nID ) ;

   void DrawM( CDC * pDC );

private:
   CRect rcM ;
};
