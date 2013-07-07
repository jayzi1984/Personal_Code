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

   //��ȡ��������Ϣ
   void GetPaintCheckInfoM( std::vector< PaintCheckInfoD > & paintCheckInfoLst ) ;

   //��ȡ����ͼƬ
   void GetBKPicInfoM( CString & bkFileName, CSize & sz ) ;

   //��ȡѡ��ͼƬ
   void GetRingPicInfoM( CString & ringFileName, CSize & sz ) ;

protected:

   //��ȡ��������Ϣ
   BOOL readPaintCheckInfoM( CStdioFile &fp, std::vector< PaintCheckInfoD > & paintCheckInfoLst ) ;

   //��ȡͼƬ��Ϣ
   BOOL readPictureInfoM( CStdioFile &fp ) ;

private:

   //��������Ϣ
   std::vector< PaintCheckInfoD > paintCheckInfoLstM ;

   //����ͼƬ����
   CString bkgM;

   //ѡ��ͼƬ����
   CString ringM;

   //����ͼƬ��С
   CSize szBKM;

   //ѡ��ͼƬ��С
   CSize szRingM;
};
