#include "StdAfx.h"
#include "VrReaderBaseCL.h"

VrReaderBaseCL::VrReaderBaseCL(void)
{
}

VrReaderBaseCL::~VrReaderBaseCL(void)
{
}

BOOL VrReaderBaseCL::SearchOneStringM(CStdioFile &fp, LPCTSTR strToSearch)
{
   BOOL bOK, bFound;
   CString tmpStr, sStr;

   bFound = FALSE;
   bOK = TRUE;
   sStr = strToSearch;
   while(!bFound && bOK)
   {
      bOK = ReadStringM(fp, tmpStr);
      if(bOK)
      {
         bFound = (sStr == tmpStr);
      }
   }
   return (bFound && bOK);
}

BOOL VrReaderBaseCL::SkipLinesM(CStdioFile &fp, int linesI)
{
   int i = 0;
   CString tmpStr;
   BOOL bOK = TRUE;

   while(i<linesI && bOK)
   {
      bOK = fp.ReadString(tmpStr);  
      i++;
   }

   return bOK;
}

BOOL VrReaderBaseCL::ReadOneIntegerM(CStdioFile &fp, int &value)
{
   BOOL bOK;
   CString tmpStr;

   value = 0;
   bOK = ReadStringM(fp, tmpStr);
   if(bOK)
   {
      int idxI = tmpStr.Find(_T(" "));
      if(idxI > 0)
      {
         tmpStr = tmpStr.Mid(0, idxI);
      }
      bOK = slSimpleIntParse(tmpStr, value);
      if(!bOK)
      {
         tmpStr = CString(_T("文件格式有误，读到的数据是：")) + tmpStr;
         AfxMessageBox(tmpStr);
      }
   }

   return bOK;
}

BOOL VrReaderBaseCL::ReadStringM(CStdioFile &fp, CString &str)
{
   CString tmpStr;
   BOOL bOK = fp.ReadString(tmpStr);
   str = _T("");
   if(bOK)
   {
      if(sizeof(TCHAR) == sizeof(WCHAR))
      {
         char *buff = new char[tmpStr.GetLength() + 1];
         memset(buff, 0, sizeof(char) * tmpStr.GetLength() + 1);
         LPCTSTR sS = tmpStr;
         for(int i=0; i<tmpStr.GetLength(); i++)
         {
            buff[i] = char(sS[i]);
         }
         int nLen = MultiByteToWideChar(CP_ACP, 0,buff, -1, NULL, NULL);
         LPWSTR lpszW = new WCHAR[nLen];
         MultiByteToWideChar(CP_ACP, 0, buff, -1, lpszW, nLen);
         str = CString(lpszW);
         delete[] lpszW;
         delete[] buff;
      }
      else
      {
         str = tmpStr;
      }
   }

   return bOK;
}

BOOL VrReaderBaseCL::ReadOneFloatM(CStdioFile &fp, float &value)
{
   BOOL bOK;
   CString tmpStr;

   value = 0;
   bOK = ReadStringM( fp, tmpStr );
   if(bOK)
   {
      int idxI = tmpStr.Find(_T(" "));
      if(idxI > 0)
      {
         tmpStr = tmpStr.Mid(0, idxI);
      }
      bOK = slSimpleFloatParseF( tmpStr, value );
      if(!bOK)
      {
         tmpStr = CString(_T("文件格式有误，读到的数据是：")) + tmpStr;
         ASSERT(0);
         AfxMessageBox( tmpStr );
      }
   }

   return bOK;
}

BOOL VrReaderBaseCL::analyzeToTwoFloatM( const CString & str, const CString& divideLetter, float *first, float *second )
{
   const int len = str.GetLength();
   int midIdx = str.Find( divideLetter );
   ASSERT( midIdx != -1 );
   if (midIdx != -1)
   {
      CString str1, str2;
      for (int i = midIdx-1; i >= 0; i--)
      {
         str1.Insert( 0, str.GetAt( i ) );
      }
      for (int j = len-1; j > midIdx ; j--)
      {
         str2.Insert( 0, str.GetAt( j ) );
      }
      slSimpleFloatParseF( str1, *first );
      slSimpleFloatParseF( str2, *second );
      return TRUE;
   }
   return FALSE;
}

BOOL VrReaderBaseCL::ReadThreeFloatM( const CString & str, const CString& divideLetter, float *first, float *second, float *third )
{
   const int len = str.GetLength();
   const int firstIdx = str.Find( divideLetter );
   const int secondIdx = str.Find( divideLetter, firstIdx+1 );
   ASSERT( firstIdx != -1 );
   ASSERT( secondIdx != -1 );

   if (firstIdx != -1 && secondIdx != -1)
   {
      CString str1, str2, str3;
      for (int i = firstIdx-1; i >= 0; i--)
      {
         str1.Insert( 0, str.GetAt( i ) );
      }
      for (int j = secondIdx-1; j > firstIdx ; j--)
      {
         str2.Insert( 0, str.GetAt( j ) );
      }
      for (int k = len-1; k > secondIdx ; k--)
      {
         str3.Insert( 0, str.GetAt( k ) );
      }
      slSimpleFloatParseF( str1, *first );
      slSimpleFloatParseF( str2, *second );
      slSimpleFloatParseF( str3, *third );
   }
   return TRUE;
}

BOOL VrReaderBaseCL::slSimpleFloatParseF(LPCTSTR lpszText, float &f)
{
   BOOL retValue;
   double tmp;

   retValue = slSimpleFloatParse(lpszText, tmp);
   if(retValue == TRUE)
   {
       f = (float)tmp;
   }
   else
   {
      f = 0.0f;
   }

   return retValue;
}

BOOL VrReaderBaseCL::slSimpleIntParse(LPCTSTR lpszText, int &d)
{
   ASSERT(lpszText != NULL);
   while(*lpszText == ' ' || *lpszText == '\t')
      lpszText++;

   TCHAR chFirst = lpszText[0];
   long l;

   l = _tcstol(lpszText, (LPTSTR *)&lpszText, 10);
   if( l == 0 && chFirst != '0')
      return FALSE;

   while(*lpszText == ' ' || *lpszText == '\t')
      lpszText++;

   if(*lpszText != '\0')
      return FALSE;

   d = (int)l;

   return TRUE;
}

BOOL VrReaderBaseCL::slSimpleFloatParse(LPCTSTR lpszText, double &d)
{
   ASSERT(lpszText != NULL);
   while(*lpszText == ' ' || *lpszText == '\t')
      lpszText++;

   TCHAR chFirst = lpszText[0];
   d = _tcstod(lpszText, (LPTSTR *)&lpszText);
   if( d == 0.0 && chFirst != '0' && chFirst != '-')
      return FALSE;
   if(*lpszText == '-')
      lpszText++;
   while(*lpszText == ' ' || *lpszText == '\t')
      lpszText++;

   if(*lpszText != '\0')
      return FALSE;

   return TRUE;
}