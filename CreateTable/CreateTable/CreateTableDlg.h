// CreateTableDlg.h : 头文件
//

#pragma once

class VrPaintCheckCL;
class VrOilMeterCtrlCL ;

// CCreateTableDlg 对话框
class CCreateTableDlg : public CDialog
{
// 构造
public:
	CCreateTableDlg(CWnd* pParent = NULL);	// 标准构造函数
   ~CCreateTableDlg();

// 对话框数据
	enum { IDD = IDD_CREATETABLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

   void CreatePaintCheckM() ;

   void CreateOilMeterM() ;
private:
   VrPaintCheckCL * pPaintCheckM;  //测试

   VrOilMeterCtrlCL * pOilMeterM ;
public:
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
