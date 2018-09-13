// gMineDlg.h : header file
//

#if !defined(AFX_GMINEDLG_H__805B0F88_7E23_4E9A_8BC0_AC3351C65749__INCLUDED_)
#define AFX_GMINEDLG_H__805B0F88_7E23_4E9A_8BC0_AC3351C65749__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGMineDlg dialog

class CGMineDlg : public CDialog
{
// Construction
public:
	CGMineDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGMineDlg)
	enum { IDD = IDD_GMINE_DIALOG };
	CString	m_data;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGMineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGMineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnRclickfirst();
	afx_msg void OnBtnRclickallmine();
	afx_msg void OnBtnLclickallnomine();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GMINEDLG_H__805B0F88_7E23_4E9A_8BC0_AC3351C65749__INCLUDED_)
