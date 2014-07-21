
// KeyTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KeyTest.h"
#include "KeyTestDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 链接钩子库
#pragma comment(lib, "../Release/Filter.lib")
_declspec(dllimport) void SetKeyFilter(HWND);

// 全局变量
BOOL dwnflag = FALSE;
BOOL upflag = FALSE;
BYTE KeyboardState[256];
CMFCButton* keys[256];
CMFCButton* keys2[256];
BYTE passed[256];
BYTE passed2[256];
int m_passed;

TCHAR szKeyName[32] = " ";
TCHAR szBuffer[256] = " ";

LOGFONT logfont;
CFont font, font2, font3, font4;
COLORREF clrLightGray = RGB(239, 239, 239);
COLORREF green = RGB(0, 255, 0);
COLORREF lgreen = RGB(0, 128, 0);
COLORREF blue = RGB(0, 0, 255);
COLORREF lblue = RGB(0, 0, 64);
COLORREF gb = RGB(0, 128, 128);

HWND	g_hWnd;
HHOOK	g_hMouse = NULL;
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT* Mouse_Info = (MOUSEHOOKSTRUCT*)lParam;
	POINT	pt;
	pt.x = Mouse_Info->pt.x;
	pt.y = Mouse_Info->pt.y;
	ScreenToClient(g_hWnd, &pt);
	if (HC_ACTION == nCode)
		if (WM_LBUTTONDOWN == wParam)
		{  
			/*
			FILE* ofile = fopen("log.txt", "a");
			//fprintf(ofile, "%d, %d\n", Mouse_Info->pt.x, Mouse_Info->pt.y);
			fprintf(ofile, "%d, %d\n", pt.x, pt.y);
			fclose(ofile);
			*/
			// 屏蔽处“重新测试”和“测试完成”两个按钮之外的所有区域的鼠标响应
			if ( pt.y > 50 || pt.x < 140 || pt.x > 525)
				return 1;
		}
	return CallNextHookEx(g_hMouse, nCode, wParam, lParam);	// 回调
}

// CKeyTestDlg 对话框

CKeyTestDlg::CKeyTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyTestDlg::IDD, pParent)
{
	m_passed = 0;
	for (int i = 0; i < 256; ++i)
	{
		keys[i] = NULL;
		passed[i] = 0;
		passed2[i] = 0;
	}

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_A, m_a);
	DDX_Control(pDX, IDC_BUTTON_B, m_b);
	DDX_Text(pDX, IDC_EDIT_PASSED, m_passed);
	DDX_Control(pDX, IDC_BUTTON_LCTR, m_lctrl);
	DDX_Control(pDX, IDC_BUTTON_RCTR, m_rctrl);
	DDX_Control(pDX, IDC_BUTTON_ESC, m_esc);
	DDX_Control(pDX, IDC_BUTTON_PRT, m_print);
	DDX_Control(pDX, IDC_BUTTON_ENTER, m_enter);
	DDX_Control(pDX, IDC_BUTTON_F1, m_f1);
	DDX_Control(pDX, IDC_BUTTON_F2, m_f2);
	DDX_Control(pDX, IDC_BUTTON_F3, m_f3);
	DDX_Control(pDX, IDC_BUTTON_F4, m_f4);
	DDX_Control(pDX, IDC_BUTTON_F5, m_f5);
	DDX_Control(pDX, IDC_BUTTON_F6, m_f6);
	DDX_Control(pDX, IDC_BUTTON_F7, m_f7);
	DDX_Control(pDX, IDC_BUTTON_F8, m_f8);
	DDX_Control(pDX, IDC_BUTTON_F9, m_f9);
	DDX_Control(pDX, IDC_BUTTON_F10, m_f10);
	DDX_Control(pDX, IDC_BUTTON_F11, m_f11);
	DDX_Control(pDX, IDC_BUTTON_F12, m_f12);
	DDX_Control(pDX, IDC_BUTTON_DOT, m_dot);
	DDX_Control(pDX, IDC_BUTTON_ONE, m_one);
	DDX_Control(pDX, IDC_BUTTON_TWO, m_two);
	DDX_Control(pDX, IDC_BUTTON_THREE, m_three);
	DDX_Control(pDX, IDC_BUTTON_FOURT, m_four);
	DDX_Control(pDX, IDC_BUTTON_FIVE, m_five);
	DDX_Control(pDX, IDC_BUTTON_SIX, m_six);
	DDX_Control(pDX, IDC_BUTTON_SEVEN, m_seven);
	DDX_Control(pDX, IDC_BUTTON_EIGHT, m_eight);
	DDX_Control(pDX, IDC_BUTTON_NINE, m_nine);
	DDX_Control(pDX, IDC_BUTTON_ZERO, m_zero);
	DDX_Control(pDX, IDC_BUTTON_SUB, m_sub);
	DDX_Control(pDX, IDC_BUTTON_EQAUL, m_equal);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_back);
	DDX_Control(pDX, IDC_BUTTON_TAB, m_tab);
	DDX_Control(pDX, IDC_BUTTON_Q, m_q);
	DDX_Control(pDX, IDC_BUTTON_W, m_w);
	DDX_Control(pDX, IDC_BUTTON_E, m_e);
	DDX_Control(pDX, IDC_BUTTON_R, m_r);
	DDX_Control(pDX, IDC_BUTTON_T, m_t);
	DDX_Control(pDX, IDC_BUTTON_Y, m_y);
	DDX_Control(pDX, IDC_BUTTON_U, m_u);
	DDX_Control(pDX, IDC_BUTTON_I, m_i);
	DDX_Control(pDX, IDC_BUTTON_O, m_o);
	DDX_Control(pDX, IDC_BUTTON_P, m_p);
	DDX_Control(pDX, IDC_BUTTON_LBRK, m_lbrk);
	DDX_Control(pDX, IDC_BUTTON_RBRK, m_rbrk);
	DDX_Control(pDX, IDC_BUTTON_SLASH, m_slash);
	DDX_Control(pDX, IDC_BUTTON_CAPS, m_caps);
	DDX_Control(pDX, IDC_BUTTON_S, m_s);
	DDX_Control(pDX, IDC_BUTTON_D, m_d);
	DDX_Control(pDX, IDC_BUTTON_F, m_f);
	DDX_Control(pDX, IDC_BUTTON_G, m_g);
	DDX_Control(pDX, IDC_BUTTON_H, m_h);
	DDX_Control(pDX, IDC_BUTTON_J, m_j);
	DDX_Control(pDX, IDC_BUTTON_K, m_k);
	DDX_Control(pDX, IDC_BUTTON_L, m_l);
	DDX_Control(pDX, IDC_BUTTON_SCOLON, m_scolon);
	DDX_Control(pDX, IDC_BUTTON_QUOT, m_quot);
	DDX_Control(pDX, IDC_BUTTON_LSHIFT, m_lshift);
	DDX_Control(pDX, IDC_BUTTON_Z, m_z);
	DDX_Control(pDX, IDC_BUTTON_X, m_x);
	DDX_Control(pDX, IDC_BUTTON_V, m_v);
	DDX_Control(pDX, IDC_BUTTON_N, m_n);
	DDX_Control(pDX, IDC_BUTTON_M, m_m);
	DDX_Control(pDX, IDC_BUTTON_COM, m_com);
	DDX_Control(pDX, IDC_BUTTON_PEO, m_peo);
	DDX_Control(pDX, IDC_BUTTON_BSLASH, m_bslash);
	DDX_Control(pDX, IDC_BUTTON_RSHIFT, m_rshift);
	DDX_Control(pDX, IDC_BUTTON_LWIN, m_lwin);
	DDX_Control(pDX, IDC_BUTTON_LALT, m_lalt);
	DDX_Control(pDX, IDC_BUTTON_SPACE, m_space);
	DDX_Control(pDX, IDC_BUTTON_RALT, m_ralt);
	DDX_Control(pDX, IDC_BUTTON_RWIN, m_rwin);
	DDX_Control(pDX, IDC_BUTTON_APP, m_app);
	DDX_Control(pDX, IDC_BUTTON_SCROLL, m_scroll);
	DDX_Control(pDX, IDC_BUTTON_BREAK, m_break);
	DDX_Control(pDX, IDC_BUTTON_INSERT, m_insert);
	DDX_Control(pDX, IDC_BUTTON_HOME, m_home);
	DDX_Control(pDX, IDC_BUTTON_PUP, m_pup);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_delete);
	DDX_Control(pDX, IDC_BUTTON_END, m_end);
	DDX_Control(pDX, IDC_BUTTON_PDWN, m_pdwn);
	DDX_Control(pDX, IDC_BUTTON_UP, m_up);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_left);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_down);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_right);
	DDX_Control(pDX, IDC_BUTTON_NLOCK, m_nlock);
	DDX_Control(pDX, IDC_BUTTON_NBSLASH, m_nbslash);
	DDX_Control(pDX, IDC_BUTTON_NSTAR, m_nstar);
	DDX_Control(pDX, IDC_BUTTON_NSUB, m_nsub);
	DDX_Control(pDX, IDC_BUTTON_NSEVEN, m_nseven);
	DDX_Control(pDX, IDC_BUTTON_NEIGHT, m_neight);
	DDX_Control(pDX, IDC_BUTTON_NNINE, m_nnine);
	DDX_Control(pDX, IDC_BUTTON_NFOUR, m_nfour);
	DDX_Control(pDX, IDC_BUTTON_NFIVE, m_nfive);
	DDX_Control(pDX, IDC_BUTTON_NSIX, m_nfix);
	DDX_Control(pDX, IDC_BUTTON_NONE, m_none);
	DDX_Control(pDX, IDC_BUTTON_NTWO, m_ntwo);
	DDX_Control(pDX, IDC_BUTTON_NTHREE, m_nthree);
	DDX_Control(pDX, IDC_BUTTON_NZERO, m_nzero);
	DDX_Control(pDX, IDC_BUTTON_NDOT, m_ndot);
	DDX_Control(pDX, IDC_BUTTON_NENTER, m_nenter);
	DDX_Control(pDX, IDC_BUTTON_NADD, m_nadd);
	DDX_Control(pDX, IDC_BUTTON_C, m_c);
	DDX_Control(pDX, IDC_BUTTON_MUTE, m_mute);
	DDX_Control(pDX, IDC_BUTTON_VDOWN, m_vdown);
	DDX_Control(pDX, IDC_BUTTON_VUP, m_vup);
	DDX_Control(pDX, IDC_BUTTON_PREV, m_prev);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_pause);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_next);
	DDX_Control(pDX, IDC_BUTTON_FN, m_fn);
	DDX_Control(pDX, IDC_BUTTON_MUSIC, m_music);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stop);

	//DDX_Control(pDX, IDC_RADIO_NUM, *num);

	//DDX_Control(pDX, IDC_BUTTON_CLEAR, m_clear);
	//DDX_Control(pDX, IDC_BUTTON_DONE, m_done);
}

BEGIN_MESSAGE_MAP(CKeyTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON_DONE, &CKeyTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CKeyTestDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_DONE, &CKeyTestDlg::OnBnClickedButtonDone)
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CKeyTestDlg 消息处理程序

BOOL CKeyTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowPos(&wndTopMost,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);	// 对话框置顶

	// 初始化按键数组
	keys[VK_ESCAPE] = &m_esc;
	keys[VK_F1] = &m_f1;
	keys[VK_F2] = &m_f2;
	keys[VK_F3] = &m_f3;
	keys[VK_F4] = &m_f4;
	keys[VK_F5] = &m_f5;
	keys[VK_F6] = &m_f6;
	keys[VK_F7] = &m_f7;
	keys[VK_F8] = &m_f8;
	keys[VK_F9] = &m_f9;
	keys[VK_F10] = &m_f10;
	keys[VK_F11] = &m_f11;
	keys[VK_F12] = &m_f12;
	keys[0xC0] = &m_dot;
	keys['1'] = &m_one;
	keys['2'] = &m_two;
	keys['3'] = &m_three;
	keys['4'] = &m_four;
	keys['5'] = &m_five;
	keys['6'] = &m_six;
	keys['7'] = &m_seven;
	keys['8'] = &m_eight;
	keys['9'] = &m_nine;
	keys['0'] = &m_zero;
	keys[0xBD] = &m_sub;
	keys[0xBB] = &m_equal;
	keys[VK_BACK] = &m_back;
	keys[VK_TAB] = &m_tab;
	keys['Q'] = &m_q;
	keys['W'] = &m_w;
	keys['E'] = &m_e;
	keys['R'] = &m_r;
	keys['T'] = &m_t;
	keys['Y'] = &m_y;
	keys['U'] = &m_u;
	keys['I'] = &m_i;
	keys['O'] = &m_o;
	keys['P'] = &m_p;
	keys[0xDB] = &m_lbrk;
	keys[0xDD] = &m_rbrk;
	keys[0xDC] = &m_slash;
	keys[VK_CAPITAL] = &m_caps;
	keys['A'] = &m_a;
	keys['S'] = &m_s;
	keys['D'] = &m_d;
	keys['F'] = &m_f;
	keys['G'] = &m_g;
	keys['H'] = &m_h;
	keys['J'] = &m_j;
	keys['K'] = &m_k;
	keys['L'] = &m_l;
	keys[0xBA] = &m_scolon;
	keys[0xDE] = &m_quot;
	keys[VK_RETURN] = &m_enter;
	keys[VK_SHIFT] = &m_lshift;
	keys['Z'] = &m_z;
	keys['X'] = &m_x;
	keys['C'] = &m_c;
	keys['V'] = &m_v;
	keys['B'] = &m_b;
	keys['N'] = &m_n;
	keys['M'] = &m_m;
	keys[0xBC] = &m_com;
	keys[0xBE] = &m_peo;
	keys[0xBF] = &m_bslash;
	keys2[VK_SHIFT] = &m_rshift;	// 1
	keys[VK_CONTROL] = &m_lctrl;
	keys[VK_LWIN] = &m_lwin;
	keys[VK_MENU] = &m_lalt;
	keys[VK_SPACE] = &m_space;
	keys2[VK_MENU] = &m_ralt;		// 2
	keys[VK_RWIN] = &m_rwin;
	keys[VK_APPS] = &m_app;
	keys2[VK_CONTROL] = &m_rctrl;	// 3
	keys[VK_SNAPSHOT] = &m_print;
	keys[VK_SCROLL] = &m_scroll;
	keys[VK_PAUSE] = &m_break;
	keys[VK_INSERT] = &m_insert;
	keys[VK_HOME] = &m_home;
	keys[VK_PRIOR] = &m_pup;
	keys[VK_DELETE] = &m_delete;
	keys[VK_END] = &m_end;
	keys[VK_NEXT] = &m_pdwn;
	keys[VK_UP] = &m_up;
	keys[VK_LEFT] = &m_left;
	keys[VK_DOWN] = &m_down;
	keys[VK_RIGHT] = &m_right;
	keys[VK_NUMLOCK] = &m_nlock;
	keys[VK_DIVIDE] = &m_nbslash;
	keys[VK_MULTIPLY] = &m_nstar;
	keys[VK_SUBTRACT] = &m_nsub;
	keys[VK_NUMPAD7] = &m_nseven;
	keys[VK_NUMPAD8] = &m_neight;
	keys[VK_NUMPAD9] = &m_nnine;
	keys[VK_NUMPAD4] = &m_nfour;
	keys[VK_NUMPAD5] = &m_nfive;
	keys[VK_NUMPAD6] = &m_nfix;
	keys[VK_NUMPAD1] = &m_none;
	keys[VK_NUMPAD2] = &m_ntwo;
	keys[VK_NUMPAD3] = &m_nthree;
	keys[VK_NUMPAD0] = &m_nzero;
	keys[VK_DECIMAL] = &m_ndot;
	keys2[VK_RETURN] = &m_nenter;	// 4
	keys[VK_ADD] = &m_nadd;

	// 多媒体键
	keys[0xAD] = &m_mute;
	keys[0xAE] = &m_vdown;
	keys[0xAF] = &m_vup;
	keys[0xB1] = &m_prev;
	keys[0xB3] = &m_pause;
	keys[0xB0] = &m_next;
	keys[0xFF] = &m_fn;

	keys[0xB5] = &m_music;
	keys[0xB2] = &m_stop;

	/* 修改字体大小和颜色 */
	// 静态框和顶层按钮
	CFont* pfont = GetDlgItem(IDC_STATIC_PASSED)->GetFont();
	pfont->GetLogFont(&logfont);
	logfont.lfHeight = logfont.lfHeight * 1.5;
	logfont.lfWidth  = logfont.lfWidth * 1.5;
	font.CreateFontIndirect(&logfont);
	GetDlgItem(IDC_STATIC_PASSED)->SetFont(&font);
	GetDlgItem(IDC_STATIC_CODE)->SetFont(&font);
	GetDlgItem(IDC_STATIC_KNAME)->SetFont(&font);
	GetDlgItem(IDC_BUTTON_CLEAR)->SetFont(&font);
	GetDlgItem(IDC_BUTTON_DONE)->SetFont(&font);
	GetDlgItem(IDC_BUTTON_CLEAR)->SetFont(&font);
	
	// 编辑框
	pfont = GetDlgItem(IDC_EDIT_KNAME)->GetFont();
	pfont->GetLogFont(&logfont);
	logfont.lfHeight =logfont.lfHeight * 2;
	logfont.lfWidth  = logfont.lfWidth * 2;
	font2.CreateFontIndirect(&logfont);
	GetDlgItem(IDC_EDIT_KNAME)->SetFont(&font2);

	pfont = GetDlgItem(IDC_EDIT_PASSED)->GetFont();
	pfont->GetLogFont(&logfont);
	logfont.lfHeight =logfont.lfHeight * 3;
	logfont.lfWidth  = logfont.lfWidth * 3;
	font3.CreateFontIndirect(&logfont);
	GetDlgItem(IDC_EDIT_PASSED)->SetFont(&font3);
	GetDlgItem(IDC_EDIT_CODE)->SetFont(&font3);

	// 所有按键初始化为白色
	pfont = GetDlgItem(IDC_EDIT_KNAME)->GetFont();
	pfont->GetLogFont(&logfont);
	logfont.lfHeight = logfont.lfHeight * 0.8;
	logfont.lfWidth  = logfont.lfWidth * 0.8;
	font4.CreateFontIndirect(&logfont);

	keys[0xFF]->SetFaceColor(clrLightGray);	// 特殊键Fn
	//keys[0xFF]->SetTextColor(RGB(0, 255, 255));
	keys[0xFF]->SetFont(&font4);
	for (int i = 0; i < 0xDF; ++i)		
		if (keys[i])
		{
			keys[i]->SetFaceColor(clrLightGray);
			keys[i]->SetFont(&font4);
		}
	for (int i = 0x0D; i < 0x13; ++i)	// rshift:10, rctrl:11, ralt:12, nenter:0D
		if (keys2[i])
		{
			keys2[i]->SetFaceColor(clrLightGray);
			keys2[i]->SetFont(&font4);
		}

	num = (CMFCButton*)GetDlgItem(IDC_RADIO_NUM);
	caps = (CMFCButton*)GetDlgItem(IDC_RADIO_CAPS);
	scroll = (CMFCButton*)GetDlgItem(IDC_RADIO_SCROLL);
	//num->SetFaceColor(RGB(0, 255, 0));

	// 设置指示灯
	::GetKeyboardState(KeyboardState);
	if (KeyboardState[VK_NUMLOCK] & 0x01)
		num->SetCheck(TRUE);
	else
		num->SetCheck(FALSE);
	if (KeyboardState[VK_CAPITAL] & 0x01)
		caps->SetCheck(TRUE);
	else
		caps->SetCheck(FALSE);
	if (KeyboardState[VK_SCROLL] & 0x01)
		scroll->SetCheck(TRUE);
	else
		scroll->SetCheck(FALSE);

	CRect rectWnd;
	GetWindowRect(&rectWnd);		//得到当前窗口（对话框）的坐标
	listRect.AddTail(&rectWnd);		//将坐标添加到链表listRect的末尾（注意是CList<CRect,CRect>listRect;类的成员变量）

	CWnd *pWndChild = GetWindow(GW_CHILD);
	while (pWndChild)	//依次得到对话框上控件的坐标，并将所有的控件坐标存储在链表中
	{
		if (pWndChild->GetDlgCtrlID() != IDC_BUTTON_CLEAR && pWndChild->GetDlgCtrlID() != IDC_BUTTON_DONE)
		{
			pWndChild->GetWindowRect(&rectWnd);
			listRect.AddTail(&rectWnd);		//由于依次将控件坐标添加到链表末尾，所以开头的坐标是对话框的坐标
		}
		pWndChild = pWndChild->GetNextWindow();
	}


	// 安装进程内鼠标钩子和全局键盘钩子
	g_hWnd = GetSafeHwnd();
	g_hMouse = SetWindowsHookEx(WH_MOUSE, MouseProc, NULL, GetCurrentThreadId());
	SetKeyFilter(g_hWnd);	// 安装键盘钩子

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKeyTestDlg::OnPaint()
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
HCURSOR CKeyTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CKeyTestDlg::PreTranslateMessage(MSG* pMsg)
{
	GetKeyboardState(KeyboardState);
	/*
	if (pMsg->lParam == 1)
	{
		GetKeyboardState(KeyboardState);
		KeyboardState[VK_NUMLOCK] |= 0x01;
		SetKeyboardState(KeyboardState);
	}
	*/
	// TODO: 在此添加专用代码和/或调用基类
	if( WM_KEYDOWN == pMsg->message || WM_SYSKEYDOWN== pMsg->message
		/*|| pMsg->wParam == 255 && ::GetKeyState(255)&0x80*/
		|| pMsg->wParam == VK_RETURN && ::GetKeyState(VK_RETURN)&0x80 
		|| pMsg->wParam == VK_SNAPSHOT && ::GetKeyState(VK_SNAPSHOT)&0x80
		/*::GetAsyncKeyState(VK_SNAPSHOT)&0x80 keyboardstate[VK_SNAPSHOT]&0x80*/)
	{
		GetKeyNameText(pMsg->lParam,szKeyName,sizeof (szKeyName) / sizeof (TCHAR));
		if (strlen(szKeyName) == 0)
			wsprintf(szKeyName, "%c", pMsg->wParam);
		SetDlgItemText(IDC_EDIT_KNAME,szKeyName);
		wsprintf(szBuffer,"%X",pMsg->wParam);
		SetDlgItemText(IDC_EDIT_CODE, szBuffer);

		std::string str(szKeyName, szKeyName + 3);
		if ((str == "Num") && (szKeyName[4] >= '0' && szKeyName[4] <= '9' || szKeyName[4] == 'D') 
				&& (KeyboardState[VK_NUMLOCK]&0x01) == 0 && dwnflag == FALSE)
		{
			dwnflag = TRUE;
			if (szKeyName[4] == 'D')
				PostMessage(pMsg->message, VK_DECIMAL, pMsg->lParam);
			else
				PostMessage(pMsg->message, VK_NUMPAD0 + int(szKeyName[4] - '0'), pMsg->lParam);
			/*
			switch (szKeyName[4])
			{
			case '0':
				PostMessage(pMsg->message, VK_NUMPAD0, pMsg->lParam);
				break;
			case '1':
				PostMessage(pMsg->message, VK_NUMPAD1, pMsg->lParam);
				break;
			case '2':
				PostMessage(pMsg->message, VK_NUMPAD2, pMsg->lParam);
				break;
			case '3':
				PostMessage(pMsg->message, VK_NUMPAD3, pMsg->lParam);
				break;
			case '4':
				PostMessage(pMsg->message, VK_NUMPAD4, pMsg->lParam);
				break;
			case '5':
				PostMessage(pMsg->message, VK_NUMPAD5, pMsg->lParam);
				break;
			case '6':
				PostMessage(pMsg->message, VK_NUMPAD6, pMsg->lParam);
				break;
			case '7':
				PostMessage(pMsg->message, VK_NUMPAD7, pMsg->lParam);
				break;
			case '8':
				PostMessage(pMsg->message, VK_NUMPAD8, pMsg->lParam);
				break;
			case '9':
				PostMessage(pMsg->message, VK_NUMPAD9, pMsg->lParam);
				break;
			case 'D':
				PostMessage(pMsg->message, VK_DECIMAL, pMsg->lParam);
				break;
			}
			*/
			return 1;
		}

		if (keys[pMsg->wParam])
		{		
			if ((pMsg->wParam == VK_SHIFT || pMsg->wParam == VK_CONTROL 
				|| pMsg->wParam == VK_MENU || pMsg->wParam == VK_RETURN) 
				&& strlen(szKeyName) > 5)
			{ // 同编码按键的处理：左右shift、ctrl、alt；两个回车；逗号与截屏
				keys2[pMsg->wParam]->SetFaceColor(lblue);
				keys2[pMsg->wParam]->SetState(TRUE);
				if (passed2[pMsg->wParam] == 0)
				{
					passed2[pMsg->wParam] = 1;
					++m_passed;
					UpdateData(FALSE);			
				}
			}
			else
			{
				if (dwnflag == TRUE) dwnflag = FALSE;
				//keys[nChar]->SetState(BST_CHECKED);
				keys[pMsg->wParam]->SetFaceColor(lblue);
				keys[pMsg->wParam]->SetState(TRUE);
				if (passed[pMsg->wParam] == 0)
				{
					passed[pMsg->wParam] = 1;
					++m_passed;
					UpdateData(FALSE);
				}
			}

			// Ctrl + C，重新测试
			if (::GetKeyState(VK_CONTROL)&0x80)
			{
				if (pMsg->wParam == VK_F4)
				{
					keys[VK_F4]->SetState(FALSE);
					keys[VK_CONTROL]->SetState(FALSE);

					keys[0xFF]->SetFaceColor(clrLightGray);	// 特殊键Fn
					passed[0xFF] = 0;
					for (int i = 0; i < 0xDF; ++i)
						if (keys[i])
						{
							keys[i]->SetFaceColor(clrLightGray);
							passed[i] = 0;
						}
					for (int i = 0x0D; i < 0x13; ++i)	// rshift:10, rctrl:11, ralt:12, nenter:0D
						if (keys2[i])
						{
							keys2[i]->SetFaceColor(clrLightGray);
							passed2[i] = 0;
						}
					m_passed = 0;
					UpdateData(FALSE);
				}
				/*
				if (pMsg->wParam == 'D' && m_passed < 113)
				{
					if (keys[0xFF] && passed[0xFF] == 0)
						keys[0xFF]->SetFaceColor(RGB(128, 0, 0));	// 特殊键Fn
					for (int i = 0; i < 0xDF; ++i)
						if (keys[i] && passed[i] == 0)
							keys[i]->SetFaceColor(RGB(128, 0, 0));
					for (int i = 0x0D; i < 0x13; ++i)	// rshift:10, rctrl:11, ralt:12, nenter:0D
						if (keys2[i] && passed2[i] == 0)
							keys2[i]->SetFaceColor(RGB(128, 0, 0));
				}
				*/
			}
		}

		// 设置指示灯
		::GetKeyboardState(KeyboardState);
		if (KeyboardState[VK_NUMLOCK] & 0x01)
			num->SetCheck(TRUE);
		else
			num->SetCheck(FALSE);
		if (KeyboardState[VK_CAPITAL] & 0x01)
			caps->SetCheck(TRUE);
		else
			caps->SetCheck(FALSE);
		if (KeyboardState[VK_SCROLL] & 0x01)
			scroll->SetCheck(TRUE);
		else
			scroll->SetCheck(FALSE);

		//if (::GetKeyState(VK_RETURN)&0x80 || ::GetKeyState(VK_SNAPSHOT)&0x80)
			return TRUE;	// 截取消息，按键不再咚咚响，光标在编辑框里时回车不再退出
	}

	if (WM_KEYUP == pMsg->message || WM_SYSKEYUP == pMsg->message
		|| pMsg->wParam == VK_RETURN && (::GetKeyState(VK_RETURN)&0x80) == 0
		|| pMsg->wParam == VK_SNAPSHOT && (::GetKeyState(VK_SNAPSHOT)&0x80) == 0)
	{
		GetKeyNameText(pMsg->lParam,szKeyName,sizeof (szKeyName) / sizeof (TCHAR));
		if (strlen(szKeyName) == 0)
			wsprintf(szKeyName, "%c", pMsg->wParam);
		SetDlgItemText(IDC_EDIT_KNAME,szKeyName);	
		wsprintf(szBuffer,"%X",pMsg->wParam);
		SetDlgItemText(IDC_EDIT_CODE, szBuffer);

		std::string str(szKeyName, szKeyName + 3);
		if ((str == "Num") && (szKeyName[4] >= '0' && szKeyName[4] <= '9' || szKeyName[4] == 'D') 
			&& (KeyboardState[VK_NUMLOCK]&0x01) == 0 && upflag == FALSE)
		{
			upflag = TRUE;
			if (szKeyName[4] == 'D')
				PostMessage(pMsg->message, VK_DECIMAL, pMsg->lParam);
			else
				PostMessage(pMsg->message, VK_NUMPAD0 + int(szKeyName[4] - '0'), pMsg->lParam);
			/*
			switch (szKeyName[4])
			{
			case '0':
				PostMessage(pMsg->message, VK_NUMPAD0, pMsg->lParam);
				break;
			case '1':
				PostMessage(pMsg->message, VK_NUMPAD1, pMsg->lParam);
				break;
			case '2':
				PostMessage(pMsg->message, VK_NUMPAD2, pMsg->lParam);
				break;
			case '3':
				PostMessage(pMsg->message, VK_NUMPAD3, pMsg->lParam);
				break;
			case '4':
				PostMessage(pMsg->message, VK_NUMPAD4, pMsg->lParam);
				break;
			case '5':
				PostMessage(pMsg->message, VK_NUMPAD5, pMsg->lParam);
				break;
			case '6':
				PostMessage(pMsg->message, VK_NUMPAD6, pMsg->lParam);
				break;
			case '7':
				PostMessage(pMsg->message, VK_NUMPAD7, pMsg->lParam);
				break;
			case '8':
				PostMessage(pMsg->message, VK_NUMPAD8, pMsg->lParam);
				break;
			case '9':
				PostMessage(pMsg->message, VK_NUMPAD9, pMsg->lParam);
				break;
			case 'D':
				PostMessage(pMsg->message, VK_DECIMAL, pMsg->lParam);
				break;
			}
			*/
			return 1;
		}

		if (keys[pMsg->wParam]&&passed[pMsg->wParam] || keys2[pMsg->wParam]&&passed2[pMsg->wParam])
		{
			if ((pMsg->wParam == VK_SHIFT || pMsg->wParam == VK_CONTROL 
				|| pMsg->wParam == VK_MENU || pMsg->wParam == VK_RETURN) 
				&& strlen(szKeyName) > 5)
			{
				keys2[pMsg->wParam]->SetFaceColor(lgreen);
				keys2[pMsg->wParam]->SetState(FALSE);
			}
			else
			{
				if (upflag == TRUE) upflag = FALSE;
				keys[pMsg->wParam]->SetFaceColor(lgreen);
				keys[pMsg->wParam]->SetState(FALSE);
			}
		}

		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CKeyTestDlg::WinHelp(DWORD dwData, UINT nCmd)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (nCmd) return ;		// 屏蔽F1弹出帮助

	CDialogEx::WinHelp(dwData, nCmd);
}

/*
// 测试完成，高亮标记未测试的按键
void CKeyTestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
}
*/


void CKeyTestDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	//keys['C']->SetState(FALSE);
	//keys[VK_CONTROL]->SetState(FALSE);

	keys[0xFF]->SetFaceColor(clrLightGray);	// 特殊键Fn
	passed[0xFF] = 0;
	for (int i = 0; i < 0xDF; ++i)
		if (keys[i])
		{
			keys[i]->SetFaceColor(clrLightGray);
			passed[i] = 0;
		}
	for (int i = 0x0D; i < 0x13; ++i)	// rshift:10, rctrl:11, ralt:12, nenter:0D
		if (keys2[i])
		{
			keys2[i]->SetFaceColor(clrLightGray);
			passed2[i] = 0;
		}
	m_passed = 0;
	UpdateData(FALSE);
}


void CKeyTestDlg::OnBnClickedButtonDone()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_passed < 113)
	{
		if (keys[0xFF] && passed[0xFF] == 0)
			keys[0xFF]->SetFaceColor(RGB(128, 0, 0));	// 特殊键Fn
		for (int i = 0; i < 0xDF; ++i)
			if (keys[i] && passed[i] == 0)
				keys[i]->SetFaceColor(RGB(128, 0, 0));
		for (int i = 0x0D; i < 0x13; ++i)	// rshift:10, rctrl:11, ralt:12, nenter:0D
			if (keys2[i] && passed2[i] == 0)
				keys2[i]->SetFaceColor(RGB(128, 0, 0));
	}
}


LRESULT CKeyTestDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// 客户区模拟标题栏，可以拖动
	UINT nFlags = CDialogEx::OnNcHitTest(point);
	if (nFlags == HTCLIENT)
		return HTCAPTION;

	return CDialogEx::OnNcHitTest(point);
}


void CKeyTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
}


HBRUSH CKeyTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	/* 不要判断nCtlColor变量，会带来莫名其妙的问题
	if (nCtlColor == CTLCOLOR_BTN && pWnd->GetDlgCtrlID() == IDC_BUTTON_CLEAR ||
		nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_STATIC_PASSED ||
		nCtlColor == CTLCOLOR_EDIT && pWnd->GetDlgCtrlID() == IDC_EDIT_CODE)
	{
		pDC->SetTextColor(gb);
		//pDC->SetBkColor(RGB(255,255,0));	//设置文本背景色
		//pDC->SetBkMode(TRANSPARENT);		//设置背景透明
		//CBrush m_brush;
		//hbr = (HBRUSH)m_brush.CreateSolidBrush(gb);;	// 背景颜色
	}
	*/
	switch (pWnd->GetDlgCtrlID())
	{
		/*
	//case IDC_BUTTON_CLEAR:
	//case IDC_BUTTON_DONE:
	case IDC_STATIC_PASSED:
	case IDC_STATIC_CODE:
	case IDC_STATIC_KNAME:
	*/
	case IDC_STATIC_NUM:
	case IDC_STATIC_CAPS:
	case IDC_STATIC_SCROLL:
		pDC->SetTextColor(blue);
		break;
	case IDC_EDIT_PASSED:
	case IDC_EDIT_CODE:
	case IDC_EDIT_KNAME:
		pDC->SetTextColor(gb);
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CKeyTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (listRect.GetCount()>0)//看链表是否为空
	{
		CRect rectDlgNow;
		GetWindowRect(&rectDlgNow);//得到当前对话框的坐标
		POSITION mp=listRect.GetHeadPosition();//取得存储在链表中的头元素，其实就是前边的对话框坐标
		CRect rectDlgSaved;
		rectDlgSaved=listRect.GetNext(mp);
		ScreenToClient(rectDlgNow);
		float fRateScaleX=(float)(rectDlgNow.right-rectDlgNow.left)/(rectDlgSaved.right-rectDlgSaved.left);//拖拉后的窗口大小与原来窗口大小的比例
		float fRateScaleY=(float)(rectDlgNow.bottom-rectDlgNow.top)/(rectDlgSaved.bottom-rectDlgSaved.top);
		ClientToScreen(rectDlgNow);
		CRect rectChildSaved;
		CWnd *pWndChild=GetWindow(GW_CHILD);
		while (pWndChild)
		{
			if (pWndChild->GetDlgCtrlID() != IDC_BUTTON_CLEAR && pWndChild->GetDlgCtrlID() != IDC_BUTTON_DONE)
			{
				rectChildSaved=listRect.GetNext(mp);
				rectChildSaved.left=rectDlgNow.left+(int)((rectChildSaved.left-rectDlgSaved.left)*fRateScaleX);
				rectChildSaved.top=rectDlgNow.top+(int)((rectChildSaved.top-rectDlgSaved.top)*fRateScaleY);
				rectChildSaved.right=rectDlgNow.right+(int)((rectChildSaved.right-rectDlgSaved.right)*fRateScaleX);
				rectChildSaved.bottom=rectDlgNow.bottom+(int)((rectChildSaved.bottom-rectDlgSaved.bottom)*fRateScaleY);
				ScreenToClient(rectChildSaved);
				pWndChild->MoveWindow(rectChildSaved);
			}
			pWndChild = pWndChild->GetNextWindow();
		}
	}
	Invalidate(); //强制重绘窗口
}
