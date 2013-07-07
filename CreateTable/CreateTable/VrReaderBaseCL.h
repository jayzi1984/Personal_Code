#pragma once

class VrReaderBaseCL
{
public:
   VrReaderBaseCL(void);
   virtual ~VrReaderBaseCL(void);
protected:
   //
   BOOL SearchOneStringM(CStdioFile &fp, LPCTSTR strToSearch);

   //
	BOOL SkipLinesM(CStdioFile &fp, int linesI);

   //
	BOOL ReadOneIntegerM(CStdioFile &fp, int &value);

   //
   BOOL ReadStringM(CStdioFile &fp, CString &str);

   //
   BOOL ReadOneFloatM(CStdioFile &fp, float &value);

   // 将一个有2个float的CString 分解为 2个float
   // 输入参数：
   //         const CString & str 带有2个float的CString
   //         cosnt CString & divideLetter 分割符号
   // 输出参数：
   //         分解后的 2个float
   BOOL analyzeToTwoFloatM( const CString & str, const CString& divideLetter, float *first, float *second );

   // 将一个有3个float的CString 分解为 3个float
   // 输入参数：
   //         const CString & str 带有3个float的CString
   //         cosnt CString & divideLetter 分割符号
   // 输出参数：
   //         分解后的 3个float
   BOOL ReadThreeFloatM( const CString & str, const CString& divideLetter, float *first, float *second, float *third );

   //将一个字符串解释成一个浮点数，如果成功，则返回TRUE, 否则返回FALSE并且将f置成0
   BOOL slSimpleFloatParseF(LPCTSTR lpszText, float &f);

   //将一个字符串解释成一个整数，如果成功，则返回TRUE, 否则返回FALSE
   BOOL slSimpleIntParse(LPCTSTR lpszText, int &d);

   //将一个字符串解释成一个双精度浮点数，如果成功，则返回TRUE, 否则返回FALSE
   BOOL slSimpleFloatParse(LPCTSTR lpszText, double &d);
};
