// gMineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gMine.h"
#include "gMineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGMineDlg dialog

CGMineDlg::CGMineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGMineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGMineDlg)
	m_data = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGMineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGMineDlg)
	DDX_Text(pDX, IDC_EDT_DATA, m_data);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGMineDlg, CDialog)
	//{{AFX_MSG_MAP(CGMineDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_RCLICKFIRST, OnBtnRclickfirst)
	ON_BN_CLICKED(IDC_BTN_RCLICKALLMINE, OnBtnRclickallmine)
	ON_BN_CLICKED(IDC_BTN_LCLICKALLNOMINE, OnBtnLclickallnomine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGMineDlg message handlers

BOOL CGMineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	RECT rect;
	rect.left = 0;
	rect.right = 118;
	rect.top = 0;
	rect.bottom = 180;
	MoveWindow(&rect,TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGMineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGMineDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGMineDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

#define ADDR_FIRST 0x01005361 //第一格数据的地址
#define ADDR_W 0x01005334 // 当前的宽
#define ADDR_H 0x01005338 // 当前的高

//棋盘数据存储区的宽和高
#define w 32 //0 ... 29 最大32 后两个byte是0x10
#define h 24 //0 ... 23

#define POS_X_FIRST 19 //第一个格子点的x坐标
#define POS_Y_FIRST 63 //第一个格子点的y坐桓
#define POS_X 16 // 每两个格子中心点的距离
#define POS_Y 16 // 同上。

HWND g_hWnd = NULL;
DWORD g_dwProcessId = 0;
HANDLE g_hProcess = NULL;
int g_w;
int g_h;
byte g_chessdata[h][w];

//初始化全局变量
void GInit()
{
	g_hWnd = ::FindWindow(NULL,"扫雷");
	GetWindowThreadProcessId(g_hWnd,&g_dwProcessId);
	g_hProcess = ::OpenProcess(PROCESS_ALL_ACCESS,FALSE,g_dwProcessId);

	//读取当前的宽和高
	DWORD numberOfBytesRead;
	ReadProcessMemory(g_hProcess,(LPVOID)ADDR_W,&g_w,sizeof(char),&numberOfBytesRead);
	ReadProcessMemory(g_hProcess,(LPVOID)ADDR_H,&g_h,sizeof(char),&numberOfBytesRead);
	
	//读数组
	::ReadProcessMemory(g_hProcess,(LPVOID)ADDR_FIRST,g_chessdata,w * h,&numberOfBytesRead);
}
void GRealease()
{
	if (NULL != g_hWnd)
	{
		CloseHandle(g_hWnd);
	}
	if (NULL != g_hProcess)
	{
		CloseHandle(g_hProcess);
	}
}
//发送右键消息
void RClick(int idxx,int idxy)
{
	LPARAM lParam = (POS_X_FIRST + POS_X * idxx) + ((POS_Y_FIRST + POS_Y * idxy)<<16);
	::SendMessage(g_hWnd,WM_RBUTTONDOWN,0,lParam);
	::SendMessage(g_hWnd,WM_RBUTTONUP,0,lParam);
}
//发送左击消息
void LClick(int idxx,int idxy)
{
	LPARAM lParam = (POS_X_FIRST + POS_X * idxx) + ((POS_Y_FIRST + POS_Y * idxy)<<16);
	::SendMessage(g_hWnd,WM_LBUTTONDOWN,0,lParam);
	::SendMessage(g_hWnd,WM_LBUTTONUP,0,lParam);
}

// 读取数据
void CGMineDlg::OnBtnRead() 
{

	GInit();
	m_data = "";
	for (int i=0;i<g_h;i++)
	{
		for(int j=0;j<g_w;j++)
		{
			char buf[3];
			itoa(g_chessdata[i][j],buf,16);
			if(strlen(buf)<2)
			{
				char t = buf[0];
				buf[1] = t;
				buf[0] = '0';
				buf[2] = 0;
			}
			m_data += buf;
			m_data += " ";
		}
		m_data += "\r\n";
	}
	UpdateData(FALSE);
	GRealease();
}

// 点击第一个格子
void CGMineDlg::OnBtnRclickfirst() 
{
	GInit();
	RClick(0,0);
	GRealease();
}

//给所有 有雷的格子作标记
void CGMineDlg::OnBtnRclickallmine() 
{
	GInit();
	m_data = "";
	for (int i=0;i<g_h;i++)
	{
		for(int j=0;j<g_w;j++)
		{
			if (g_chessdata[i][j]==0x8F)
			{
				RClick(j,i);
				//Sleep(100);
			}
		}
	}
	GRealease();
}

//点击所有的非雷格子
void CGMineDlg::OnBtnLclickallnomine() 
{
	GInit();
	m_data = "";
	for (int i=0;i<g_h;i++)
	{
		for(int j=0;j<g_w;j++)
		{
			if (g_chessdata[i][j]==0x0f)
			{
				LClick(j,i);
				//Sleep(100);
			}
		}
	}
	GRealease();
}
