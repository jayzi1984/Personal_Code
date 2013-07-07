#pragma once

class VrShowTableCL : public CWnd
{
public:
   VrShowTableCL(void);
   ~VrShowTableCL(void);

   BOOL CreateM( const CRect & rc, CWnd * pParent, int nID ) ;

   void DrawM( CDC * pDC ) ;

private:

   CRect rcM;
};
