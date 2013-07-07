#pragma once
#include "vrreaderbasecl.h"

#include <vector>

class VrOilMeterInfoCL :
   public VrReaderBaseCL
{
public:
   VrOilMeterInfoCL( LPCTSTR fileName );
   ~VrOilMeterInfoCL(void);

public:

   void GetPicNameLstM( std::vector<CString> & picNameLst ) ;

   CSize GetPicSizeM() ;

   void GetCirInfoM( CPoint & point, int & smallRadius, int & bigRadius ) ;

private:

   BOOL readPicNameLstM( CStdioFile & fp, std::vector<CString> & picNameLst ) ;

   BOOL readPicInfoM( CStdioFile & fp ) ;

private:

   std::vector< CString > picNameLstM ;

   CSize szPicM ;

   CPoint cirCenterM ;

   int smallRadiusM ;

   int bigRadiusM ;
};
