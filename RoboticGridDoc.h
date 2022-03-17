// RoboticGridDoc.h : interface of the CRoboticGridDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOTICGRIDDOC_H__71B56F58_B1AC_47D7_850F_44A71467378A__INCLUDED_)
#define AFX_ROBOTICGRIDDOC_H__71B56F58_B1AC_47D7_850F_44A71467378A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRoboticGridDoc : public CDocument
{
protected: // create from serialization only
	CRoboticGridDoc();
	DECLARE_DYNCREATE(CRoboticGridDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoboticGridDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRoboticGridDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRoboticGridDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOTICGRIDDOC_H__71B56F58_B1AC_47D7_850F_44A71467378A__INCLUDED_)
