// CreateTableDlg.h : ͷ�ļ�
//

#pragma once

class VrPaintCheckCL;
class VrOilMeterCtrlCL ;

// CCreateTableDlg �Ի���
class CCreateTableDlg : public CDialog
{
// ����
public:
	CCreateTableDlg(CWnd* pParent = NULL);	// ��׼���캯��
   ~CCreateTableDlg();

// �Ի�������
	enum { IDD = IDD_CREATETABLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

   void CreatePaintCheckM() ;

   void CreateOilMeterM() ;
private:
   VrPaintCheckCL * pPaintCheckM;  //����

   VrOilMeterCtrlCL * pOilMeterM ;
public:
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
