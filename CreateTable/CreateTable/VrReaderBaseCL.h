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

   // ��һ����2��float��CString �ֽ�Ϊ 2��float
   // ���������
   //         const CString & str ����2��float��CString
   //         cosnt CString & divideLetter �ָ����
   // ���������
   //         �ֽ��� 2��float
   BOOL analyzeToTwoFloatM( const CString & str, const CString& divideLetter, float *first, float *second );

   // ��һ����3��float��CString �ֽ�Ϊ 3��float
   // ���������
   //         const CString & str ����3��float��CString
   //         cosnt CString & divideLetter �ָ����
   // ���������
   //         �ֽ��� 3��float
   BOOL ReadThreeFloatM( const CString & str, const CString& divideLetter, float *first, float *second, float *third );

   //��һ���ַ������ͳ�һ��������������ɹ����򷵻�TRUE, ���򷵻�FALSE���ҽ�f�ó�0
   BOOL slSimpleFloatParseF(LPCTSTR lpszText, float &f);

   //��һ���ַ������ͳ�һ������������ɹ����򷵻�TRUE, ���򷵻�FALSE
   BOOL slSimpleIntParse(LPCTSTR lpszText, int &d);

   //��һ���ַ������ͳ�һ��˫���ȸ�����������ɹ����򷵻�TRUE, ���򷵻�FALSE
   BOOL slSimpleFloatParse(LPCTSTR lpszText, double &d);
};
