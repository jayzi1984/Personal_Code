#pragma once
#include "afxwin.h"
#include "UserStruct.h"

#include <vector>
#include <Gdiplus.h>

class VrPaintCheckCL :
   public CWnd
{
public:
   VrPaintCheckCL(void);
   ~VrPaintCheckCL(void);

   BOOL CreateM( LPCTSTR workDir, const CRect & rc, CWnd * pParent, int nID ) ;

   void DrawM( Gdiplus::Graphics * graphics ) ;

   void SetPaintStateM( LPCTSTR paintState ) ;

   void GetPaintStateM( CString & paintState ) ;

private:

   void compuateRealRectM( const CRect & rc ) ;

   void changAbsoluteToRealRectM( const CRect & absoluteRc, CRect & realRc ) ;

   void changAbsoluteToRealRectM( int absoluteX, int absoluteY, CSize absoluteSize, CRect & realRc ) ;

   int checkSelectAreaM( CPoint point ) ;

private:

   std::vector< PaintCheckInfoD > paintCheckInfoLstM ;

   Gdiplus::Bitmap * pBKGPicM ;

   Gdiplus::Bitmap * pRingPicM ;

   CSize szBKGM ;

   CSize szRingM ;

   CString subFolderDirM ;

   CRect realRcM ;

   std::vector< int > paintStateLstM;

   CWnd * pParentM ;

   int selIdM ;

public:

   DECLARE_MESSAGE_MAP()

   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected:

   virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
   
};
