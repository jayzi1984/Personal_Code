// CreateTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CreateTable.h"
#include "CreateTableDlg.h"

#include "VrPaintCheckCL.h"
#include "VrOilMeterCtrlCL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCreateTableDlg 对话框




CCreateTableDlg::CCreateTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateTableDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   pPaintCheckM = NULL;

   pOilMeterM = NULL ;
}

CCreateTableDlg::~CCreateTableDlg()
{
   if ( pPaintCheckM != NULL )
   {
      delete pPaintCheckM ;
      pPaintCheckM = NULL ;
   }

   if ( pOilMeterM != NULL )
   {
      delete pOilMeterM ;
      pOilMeterM = NULL ;
   }
}

void CCreateTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCreateTableDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCreateTableDlg 消息处理程序

BOOL CCreateTableDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOW);
   MoveWindow( 100, 100, 900, 700) ;

	// TODO: 在此添加额外的初始化代码
   CreatePaintCheckM() ;

   CreateOilMeterM() ;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CCreateTableDlg::CreatePaintCheckM()
{
   if ( pPaintCheckM == NULL )
   {
      pPaintCheckM = new VrPaintCheckCL() ;
   }
   if ( pPaintCheckM != NULL && pPaintCheckM->m_hWnd == NULL )
   {
      BOOL bOK = pPaintCheckM->CreateM( _T("E:\\c++ test\\CreateTable"), CRect(50,50,250,250), this, 100 ) ;
      if ( bOK != TRUE )
      {
         TRACE0( _T("PaintCheck Create Failed!") ) ;
      }
      pPaintCheckM->SetPaintStateM( _T( "00000000000" ) ) ;
   }
}

void CCreateTableDlg::CreateOilMeterM()
{
   if ( pOilMeterM == NULL )
   {
      pOilMeterM = new VrOilMeterCtrlCL() ;
   }
   if ( pOilMeterM != NULL && pOilMeterM->m_hWnd == NULL )
   {
      BOOL bOK = pOilMeterM->CreateM( _T( "E:\\c++ test\\CreateTable" ), CRect( 50, 300, 250, 500 ), this, 101 ) ;
      if ( bOK != TRUE )
      {
         TRACE0( _T("OilMeter Create Failed!") ) ;
      }
   }
}

void CCreateTableDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCreateTableDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
   {
      CPaintDC dc( this ) ;
      CRect rc ;
      GetClientRect( rc ) ;

      Gdiplus::Bitmap bmp( rc.Width(), rc.Height() ) ;
      Gdiplus::Graphics * pGraphics = Gdiplus::Graphics::FromImage( &bmp ) ;

      pGraphics->Clear( Gdiplus::Color( 255,255,255 ) );

      if ( pPaintCheckM != NULL )
         pPaintCheckM->DrawM( pGraphics ) ;

      if ( pOilMeterM != NULL )
         pOilMeterM->DrawM( pGraphics ) ;

      Gdiplus::Graphics graphics( dc.GetSafeHdc() ) ;

      graphics.DrawImage( &bmp, 0, 0 ) ;

      CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CCreateTableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CCreateTableDlg::OnEraseBkgnd(CDC* pDC)
{
   // TODO: 在此添加消息处理程序代码和/或调用默认值

   //CPaintDC dc( this ) ;
   /*CRect rc ;
   GetClientRect( rc ) ;

   Gdiplus::Bitmap bmp( rc.Width(), rc.Height() ) ;
   Gdiplus::Graphics * pGraphics = Gdiplus::Graphics::FromImage( &bmp ) ;

   pGraphics->Clear( Gdiplus::Color( 255,255,255 ) );

   if ( pPaintCheckM != NULL )
      pPaintCheckM->DrawM( pGraphics ) ;

   Gdiplus::Graphics graphics( pDC->GetSafeHdc() ) ;

   graphics.DrawImage( &bmp, 0, 0 ) ;*/

   return CDialog::OnEraseBkgnd(pDC);
}
