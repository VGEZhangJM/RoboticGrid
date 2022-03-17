// RoboticGrid.h : main header file for the ROBOTICGRID application
//

#if !defined(AFX_ROBOTICGRID_H__B92C3952_C89A_4EA8_9DA1_D3DA31A36044__INCLUDED_)
#define AFX_ROBOTICGRID_H__B92C3952_C89A_4EA8_9DA1_D3DA31A36044__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridApp:
// See RoboticGrid.cpp for the implementation of this class
//

class CRoboticGridApp : public CWinApp
{
public:
	CRoboticGridApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoboticGridApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRoboticGridApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOTICGRID_H__B92C3952_C89A_4EA8_9DA1_D3DA31A36044__INCLUDED_)
