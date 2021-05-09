#if !defined(AFX_SETLENGTH_H__0E96133C_546A_490E_B9BE_3F242A8DACA2__INCLUDED_)
#define AFX_SETLENGTH_H__0E96133C_546A_490E_B9BE_3F242A8DACA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// setlength.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// setlength dialog

class setlength : public CDialog
{
// Construction
public:
	setlength(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(setlength)
	enum { IDD = IDD_DIALOG1 };
	int		m_length;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(setlength)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(setlength)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETLENGTH_H__0E96133C_546A_490E_B9BE_3F242A8DACA2__INCLUDED_)
