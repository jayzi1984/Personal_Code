#pragma once

#include <Gdiplus.h>

class VrResrouceFactoryCL
{
public:
   VrResrouceFactoryCL(void);
   ~VrResrouceFactoryCL(void);

public:

   Gdiplus::Bitmap * CreateImgM( LPCTSTR fileName ) ;
};
