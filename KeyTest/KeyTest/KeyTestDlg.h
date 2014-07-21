
// KeyTestDlg.h : 头文件
//

#pragma once
#include "afxbutton.h"


// CKeyTestDlg 对话框
class CKeyTestDlg : public CDialogEx
{
// 构造
public:
	CKeyTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KEYTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

	CMFCButton m_esc;
	CMFCButton m_enter;
	CMFCButton m_f1;
	CMFCButton m_f2;
	CMFCButton m_f3;
	CMFCButton m_f4;
	CMFCButton m_f5;
	CMFCButton m_f6;
	CMFCButton m_f7;
	CMFCButton m_f8;
	CMFCButton m_f9;
	CMFCButton m_f10;
	CMFCButton m_f11;
	CMFCButton m_f12;
	CMFCButton m_dot;
	CMFCButton m_one;
	CMFCButton m_two;
	CMFCButton m_three;
	CMFCButton m_four;
	CMFCButton m_five;
	CMFCButton m_six;
	CMFCButton m_seven;
	CMFCButton m_eight;
	CMFCButton m_nine;
	CMFCButton m_zero;
	CMFCButton m_sub;
	CMFCButton m_equal;
	CMFCButton m_back;
	CMFCButton m_tab;
	CMFCButton m_q;
	CMFCButton m_w;
	CMFCButton m_e;
	CMFCButton m_r;
	CMFCButton m_t;
	CMFCButton m_y;
	CMFCButton m_u;
	CMFCButton m_i;
	CMFCButton m_o;
	CMFCButton m_p;
	CMFCButton m_lbrk;
	CMFCButton m_rbrk;
	CMFCButton m_slash;
	CMFCButton m_caps;
	CMFCButton m_a;
	CMFCButton m_s;
	CMFCButton m_d;
	CMFCButton m_f;
	CMFCButton m_g;
	CMFCButton m_h;
	CMFCButton m_j;
	CMFCButton m_k;
	CMFCButton m_l;
	CMFCButton m_scolon;
	CMFCButton m_quot;
	CMFCButton m_lshift;
	CMFCButton m_z;
	CMFCButton m_x;
	CMFCButton m_c;
	CMFCButton m_v;
	CMFCButton m_b;
	CMFCButton m_n;
	CMFCButton m_m;
	CMFCButton m_com;
	CMFCButton m_peo;
	CMFCButton m_bslash;
	CMFCButton m_rshift;
	CMFCButton m_lctrl;
	CMFCButton m_lwin;
	CMFCButton m_lalt;
	CMFCButton m_space;
	CMFCButton m_ralt;
	CMFCButton m_rwin;
	CMFCButton m_app;
	CMFCButton m_rctrl;
	CMFCButton m_print;
	CMFCButton m_scroll;
	CMFCButton m_break;
	CMFCButton m_insert;
	CMFCButton m_home;
	CMFCButton m_pup;
	CMFCButton m_delete;
	CMFCButton m_end;
	CMFCButton m_pdwn;
	CMFCButton m_up;
	CMFCButton m_left;
	CMFCButton m_down;
	CMFCButton m_right;
	CMFCButton m_nlock;
	CMFCButton m_nbslash;
	CMFCButton m_nstar;
	CMFCButton m_nsub;
	CMFCButton m_nseven;
	CMFCButton m_neight;
	CMFCButton m_nnine;
	CMFCButton m_nfour;
	CMFCButton m_nfive;
	CMFCButton m_nfix;
	CMFCButton m_none;
	CMFCButton m_ntwo;
	CMFCButton m_nthree;
	CMFCButton m_nzero;
	CMFCButton m_ndot;
	CMFCButton m_nenter;
	CMFCButton m_nadd;
	CMFCButton m_mute;
	CMFCButton m_vdown;
	CMFCButton m_vup;
	CMFCButton m_prev;
	CMFCButton m_pause;
	CMFCButton m_next;
	CMFCButton m_fn;
	CMFCButton m_music;
	CMFCButton m_stop;

	CMFCButton* num;
	CMFCButton* caps;
	CMFCButton* scroll;

	//afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonDone();
	afx_msg LRESULT OnNcHitTest(CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//CMFCButton m_clear;
	//CMFCButton m_done;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CList<CRect, CRect> listRect;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
