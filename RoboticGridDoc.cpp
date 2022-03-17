// RoboticGridDoc.cpp : implementation of the CRoboticGridDoc class
//

#include "stdafx.h"
#include "RoboticGrid.h"

#include "RoboticGridDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridDoc

IMPLEMENT_DYNCREATE(CRoboticGridDoc, CDocument)

BEGIN_MESSAGE_MAP(CRoboticGridDoc, CDocument)
	//{{AFX_MSG_MAP(CRoboticGridDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridDoc construction/destruction

CRoboticGridDoc::CRoboticGridDoc()
{
	// TODO: add one-time construction code here

}

CRoboticGridDoc::~CRoboticGridDoc()
{
}

BOOL CRoboticGridDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRoboticGridDoc serialization

void CRoboticGridDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridDoc diagnostics

#ifdef _DEBUG
void CRoboticGridDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRoboticGridDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridDoc commands
