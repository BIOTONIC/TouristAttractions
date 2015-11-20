
// TouristAttractionsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TouristAttractions.h"
#include "TouristAttractionsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTouristAttractionsDlg 对话框



CTouristAttractionsDlg::CTouristAttractionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOURISTATTRACTIONS_DIALOG, pParent)
	, m_msg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTouristAttractionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_msg);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
}

BEGIN_MESSAGE_MAP(CTouristAttractionsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTouristAttractionsDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTouristAttractionsDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTouristAttractionsDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, &CTouristAttractionsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTouristAttractionsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTouristAttractionsDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTouristAttractionsDlg 消息处理程序

BOOL CTouristAttractionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	graph = new Graph();                                                       //实例化Graph对象
	graph->Init();                                                             //初始化

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTouristAttractionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTouristAttractionsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTouristAttractionsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTouristAttractionsDlg::OnCbnSelchangeCombo1()                            //起点下拉框更改 获得选中的序号
{
	int nIndex = m_combo1.GetCurSel();
	CString strText;
	m_combo1.GetLBText(nIndex, strText);
	nStartVex = _ttoi(strText);
}

void CTouristAttractionsDlg::OnCbnSelchangeCombo2()                            //终点下拉框更改 获得选中的序号
{
	int nIndex = m_combo2.GetCurSel();
	CString strText;
	m_combo2.GetLBText(nIndex, strText);
	nEndVex = _ttoi(strText);
}

void CTouristAttractionsDlg::OnBnClickedButton1()                              //点击“关于这个景点按钮”
{
	m_msg = graph->QueryVexInfo(nStartVex);
	UpdateData(FALSE);
}

void CTouristAttractionsDlg::OnBnClickedButton2()                              //点击“所有汉密尔顿道路”
{
	m_msg = graph->DFSTranverse(nStartVex);
	UpdateData(FALSE);
}


void CTouristAttractionsDlg::OnBnClickedButton3()                              //点击“最小生成树”
{
	m_msg = graph->FindMinTree(nStartVex);
	UpdateData(FALSE);
}


void CTouristAttractionsDlg::OnBnClickedButton4()                              //点击“最短路径”
{
	m_msg = graph->FindShortPath(nStartVex, nEndVex);
	UpdateData(FALSE);
}
