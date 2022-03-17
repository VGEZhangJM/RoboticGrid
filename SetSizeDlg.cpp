// SetSizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoboticGrid.h"
#include "SetSizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSizeDlg dialog


CSetSizeDlg::CSetSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetSizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetSizeDlg)
	m_dSize = 0.0;
	//}}AFX_DATA_INIT
}


void CSetSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSizeDlg)
	DDX_Text(pDX, IDC_EDIT_SIZE, m_dSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSizeDlg, CDialog)
	//{{AFX_MSG_MAP(CSetSizeDlg)
	ON_EN_CHANGE(IDC_EDIT_SIZE, OnChangeEditSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSizeDlg message handlers

void CSetSizeDlg::OnChangeEditSize() 
{
	UpdateData(TRUE);
}
