// setlength.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "setlength.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// setlength dialog


setlength::setlength(CWnd* pParent /*=NULL*/)
	: CDialog(setlength::IDD, pParent)
{
	//{{AFX_DATA_INIT(setlength)
	m_length = 0;
	//}}AFX_DATA_INIT
}


void setlength::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(setlength)
	DDX_Text(pDX, IDC_EDIT1, m_length);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(setlength, CDialog)
	//{{AFX_MSG_MAP(setlength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// setlength message handlers

void setlength::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	//int o=m_length;
    //CString output;
	//output.Format("-%d-",o);
	//MessageBox(output);
	CDialog::OnOK();
}
