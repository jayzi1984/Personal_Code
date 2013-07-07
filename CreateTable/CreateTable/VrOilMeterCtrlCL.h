#pragma once
#include "afxwin.h"

#include <Gdiplus.h>
#include <vector>

class VrOilMeterCtrlCL :
   public CWnd
{
public:
   VrOilMeterCtrlCL(void);
   ~VrOilMeterCtrlCL(void);

   BOOL CreateM( LPCTSTR workDir, const CRect & rc, CWnd * pParent, int nID ) ;

   void DrawM( Gdiplus::Graphics * graphics ) ;

private:

   void perpareDataM() ;

   void compuateRealRectM( const CRect & rc ) ;

   int compuateStateM( const CPoint & pnt ) ;

private:

   CString subFolderM ;

   CWnd * pParentM ;

   CRect realRcM ;

   CSize szPicM ;

   CPoint cirCenterPntM ;

   int smallRadiusM ;

   int bigRadiusM ;

   int stateM ;

   int lastStateM ;

   std::vector< Gdiplus::Bitmap * > imgLstM ; 

public:
   DECLARE_MESSAGE_MAP()
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
