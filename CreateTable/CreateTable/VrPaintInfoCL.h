#pragma once
#include "vrreaderbasecl.h"
#include "UserStruct.h"

#include <vector>

class VrPaintInfoCL :
   public VrReaderBaseCL
{
public:
   VrPaintInfoCL( LPCTSTR fileName ) ;
   virtual ~VrPaintInfoCL(void) ;
public:

   //获取油漆检查信息
   void GetPaintCheckInfoM( std::vector< PaintCheckInfoD > & paintCheckInfoLst ) ;

   //获取背景图片
   void GetBKPicInfoM( CString & bkFileName, CSize & sz ) ;

   //获取选中图片
   void GetRingPicInfoM( CString & ringFileName, CSize & sz ) ;

protected:

   //读取油漆检查信息
   BOOL readPaintCheckInfoM( CStdioFile &fp, std::vector< PaintCheckInfoD > & paintCheckInfoLst ) ;

   //读取图片信息
   BOOL readPictureInfoM( CStdioFile &fp ) ;

private:

   //油漆检查信息
   std::vector< PaintCheckInfoD > paintCheckInfoLstM ;

   //背景图片名字
   CString bkgM;

   //选中图片名字
   CString ringM;

   //背景图片大小
   CSize szBKM;

   //选中图片大小
   CSize szRingM;
};
