// RoboticGridView.h : interface of the CRoboticGridView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOTICGRIDVIEW_H__5BD8336B_F4EB_4579_B229_2BDA0799A2B5__INCLUDED_)
#define AFX_ROBOTICGRIDVIEW_H__5BD8336B_F4EB_4579_B229_2BDA0799A2B5__INCLUDED_

#include "Map_Map.h"
#include "Map_Grid.h"
#include "Map_Hex.h"
#include "Analyse_WorkSpace.h"
#include "Analyse_RouteAnalyse.h"

#include "PublicFunction.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRoboticGridView : public CView
{
protected: // create from serialization only
	CRoboticGridView();
	DECLARE_DYNCREATE(CRoboticGridView)

// Attributes
public:
	CRoboticGridDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoboticGridView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRoboticGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMap_Map	m_pMap;

	CMap_Grid	m_pGrid;
	CMap_Hex	m_pHex;

	CAnalyse_WorkSpace	m_pWorkspace;

	CAnalyse_RouteAnalyse	m_pAnalyse;

	CPublicFunction	m_pPublicFunction;
	
	//Êó±ê²Ù×÷
	int		m_iAction;
	CPoint	m_ptDown;
	CPoint	m_ptUp;
	bool	m_bMoveFlag;
	
	//
	bool	m_bShowMap;
	//
	bool	m_bShowGrid;
	//
	bool	m_bShowHex;

// Generated message map functions
protected:
	//{{AFX_MSG(CRoboticGridView)
	afx_msg void OnFileOpen();
	afx_msg void OnGridInit();
	afx_msg void OnGridCreate();
	afx_msg void OnHexInit();
	afx_msg void OnHexCreate();
	afx_msg void OnMapZoomin();
	afx_msg void OnMapZoomout();
	afx_msg void OnMapPan();
	afx_msg void OnMapFull();
	afx_msg void OnGridCalc();
	afx_msg void OnHexCalc();
	afx_msg void OnMapCalc();
	afx_msg void OnGridSavenet();
	afx_msg void OnAnalyseAdd();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAnalyseExec();
	afx_msg void OnHexCreatenet();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMapShowor();
	afx_msg void OnGridShow();
	afx_msg void OnGridQuery();
	afx_msg void OnHexShow();
	afx_msg void OnHexQuery();
	afx_msg void OnAnalyseClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RoboticGridView.cpp
inline CRoboticGridDoc* CRoboticGridView::GetDocument()
   { return (CRoboticGridDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOTICGRIDVIEW_H__5BD8336B_F4EB_4579_B229_2BDA0799A2B5__INCLUDED_)
