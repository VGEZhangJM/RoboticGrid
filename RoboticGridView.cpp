// RoboticGridView.cpp : implementation of the CRoboticGridView class
//

#include "stdafx.h"
#include "RoboticGrid.h"

#include "RoboticGridDoc.h"
#include "RoboticGridView.h"

#include "SetSizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridView

IMPLEMENT_DYNCREATE(CRoboticGridView, CView)

BEGIN_MESSAGE_MAP(CRoboticGridView, CView)
	//{{AFX_MSG_MAP(CRoboticGridView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_GRID_INIT, OnGridInit)
	ON_COMMAND(ID_GRID_CREATE, OnGridCreate)
	ON_COMMAND(ID_HEX_INIT, OnHexInit)
	ON_COMMAND(ID_HEX_CREATE, OnHexCreate)
	ON_COMMAND(ID_MAP_ZOOMIN, OnMapZoomin)
	ON_COMMAND(ID_MAP_ZOOMOUT, OnMapZoomout)
	ON_COMMAND(ID_MAP_PAN, OnMapPan)
	ON_COMMAND(ID_MAP_FULL, OnMapFull)
	ON_COMMAND(ID_GRID_CALC, OnGridCalc)
	ON_COMMAND(ID_HEX_CALC, OnHexCalc)
	ON_COMMAND(ID_MAP_CALC, OnMapCalc)
	ON_COMMAND(ID_GRID_SAVENET, OnGridSavenet)
	ON_COMMAND(ID_ANALYSE_ADD, OnAnalyseAdd)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ANALYSE_EXEC, OnAnalyseExec)
	ON_COMMAND(ID_HEX_CREATENET, OnHexCreatenet)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MAP_SHOWOR, OnMapShowor)
	ON_COMMAND(ID_GRID_SHOW, OnGridShow)
	ON_COMMAND(ID_GRID_QUERY, OnGridQuery)
	ON_COMMAND(ID_HEX_SHOW, OnHexShow)
	ON_COMMAND(ID_HEX_QUERY, OnHexQuery)
	ON_COMMAND(ID_ANALYSE_CLEAR, OnAnalyseClear)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridView construction/destruction

CRoboticGridView::CRoboticGridView()
{
	// TODO: add construction code here
	m_bShowMap	= true;

	//
	m_bShowGrid	= true;
	//
	m_bShowHex	= true;
}

CRoboticGridView::~CRoboticGridView()
{
}

BOOL CRoboticGridView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridView drawing

void CRoboticGridView::OnDraw(CDC* pDC)
{
	CRoboticGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	CRect	rectClient;
	GetClientRect(rectClient);
	
	//m_pMapObj.SetClientRect(rectClient.left)
	//
	if (m_pMap.IsOpened())
	{
		double	dOldShowLeft,dOldShowRight,dOldShowBottom,dOldShowTop;
		m_pMap.GetOldShowExt(dOldShowLeft,dOldShowRight,dOldShowBottom,dOldShowTop);

		//获取显示区域
		double	dShowLeft,dShowRight,dShowBottom,dShowTop;
		m_pMap.GetShowExt(dShowLeft,dShowRight,dShowBottom,dShowTop);
		
		//
		//if(dShowLeft!=dOldShowLeft || dShowRight!=dOldShowRight || dShowBottom!=dOldShowBottom || dShowTop!=dOldShowTop)
		{
			if (m_pMap.InitShow(rectClient,dShowLeft,dShowRight,dShowBottom,dShowTop))
			{
				//重新计算显示区域
				double	dMyShowLeft,dMyShowRight,dMyShowBottom,dMyShowTop;
				m_pMap.ScreenToMap(rectClient.left,rectClient.top,dMyShowLeft,dMyShowTop);
				m_pMap.ScreenToMap(rectClient.right,rectClient.bottom,dMyShowRight,dMyShowBottom);

				if (m_bShowMap)
				{
					m_pMap.Draw(pDC);
				}

				double	dXA,dXB,dYA,dYB;
				m_pMap.GetCoordMapping(dXA,dXB,dYA,dYB);

				if(m_bShowGrid)
				{
					m_pGrid.SetShowExt(dMyShowLeft,dMyShowRight,dMyShowBottom,dMyShowTop);
					m_pGrid.SetCoordMapping(dXA,dXB,dYA,dYB);
					m_pGrid.Draw(pDC,-1);			
				}

				if(m_bShowHex)
				{
					m_pHex.SetCoordMapping(dXA,dXB,dYA,dYB);
					m_pHex.Draw(pDC);
				}
				
				if (m_bShowGrid || m_bShowHex)
				{
					m_pWorkspace.SetCoordMapping(dXA,dXB,dYA,dYB);
					m_pWorkspace.SetShowExt(dMyShowLeft,dMyShowRight,dMyShowBottom,dMyShowTop);
					m_pWorkspace.OnDraw(pDC);
					
					m_pAnalyse.SetCoordMapping(dXA,dXB,dYA,dYB);
					m_pAnalyse.DrawBestRoute(pDC);
				}
			}

			m_pMap.SetOldShowExt(dShowLeft,dShowRight,dShowBottom,dShowTop);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridView printing

BOOL CRoboticGridView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRoboticGridView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRoboticGridView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridView diagnostics

#ifdef _DEBUG
void CRoboticGridView::AssertValid() const
{
	CView::AssertValid();
}

void CRoboticGridView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRoboticGridDoc* CRoboticGridView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRoboticGridDoc)));
	return (CRoboticGridDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRoboticGridView message handlers

void CRoboticGridView::OnFileOpen() 
{
	if (m_pMap.Read("E:\\11-六边形地图模型\\Data\\Data.dat"))
	{
		double	dLeft,dRight,dBottom,dTop;

		m_pMap.GetMapExt(dLeft,dRight,dBottom,dTop);

		m_pMap.SetShowExt(dLeft,dRight,dBottom,dTop);
	}

	Invalidate();
}

void CRoboticGridView::OnGridInit() 
{
	CSetSizeDlg	pDlg;
	double		m_dSize;

	m_dSize			= 1.0;
	pDlg.m_dSize	= m_dSize;

	if (pDlg.DoModal() == IDOK)
	{
		m_dSize	= pDlg.m_dSize;
	}
	else
		return;

	if (m_pMap.IsOpened())
	{
		double	dLeft,dRight;
		double	dBottom,dTop;

		m_pMap.GetMapExt(dLeft,dRight,dBottom,dTop);

		m_pGrid.CreateGrid(m_dSize,dLeft,dRight,dBottom,dTop);
	}
	//Invalidate();
}

void CRoboticGridView::OnGridCreate() 
{
	// TODO: Add your command handler code here

	int	iNumX,iNumY;

	iNumX	= m_pGrid.GetNumX();
	iNumY	= m_pGrid.GetNumY();

	for(int j=0;j<iNumY;j++)
	{
		for (int i=0;i<iNumX;i++)
		{	
			//
			double	dGridX,dGridY;

			m_pGrid.m_pObjList[j*iNumX+i].GetCenter(dGridX,dGridY);
			
			//判断是在哪个多边形中
			{
				int		iSubType = -1;
				bool	bInPolygon	= false;

				//提取数据
				CMap_PolygonElement *pPolyon;
				pPolyon = m_pMap.GetPolygonElement();
				
				while( pPolyon != NULL )
				{
					//
					double* dx;
					double* dy;
					int		iPointNum;
					SMap_DPointCoord *pPointList;

					iPointNum	= pPolyon->GetPointNum();
					pPointList	= pPolyon->GetPointList();

					dx		= new double[iPointNum];
					dy		= new double[iPointNum];
					
					for(int k=0;k<iPointNum;k++)
					{
						dx[k]	= pPointList[k].x;
						dy[k]	= pPointList[k].y;
					}

					if (m_pPublicFunction.PointInPolygon(dGridX,dGridY,iPointNum,dx,dy))
					{
						bInPolygon	= true;
						iSubType	= pPolyon->GetSubType();
					}

					delete	[]dx;
					delete	[]dy;

					pPolyon	= pPolyon->m_pNext;
				}

				if (bInPolygon)
				{
					m_pGrid.m_pObjList[j*iNumX+i].SetTerrainType(iSubType);

					CClientDC	dc(this);
					
					double	dXA,dXB,dYA,dYB;
					m_pMap.GetCoordMapping(dXA,dXB,dYA,dYB);

					m_pGrid.m_pObjList[j*iNumX+i].SetCoordMapping(dXA,dXB,dYA,dYB);

					m_pGrid.m_pObjList[j*iNumX+i].Draw(&dc,-1);
				}
			}
		}
	}

	//
	m_pGrid.CreateSide();	
}

void CRoboticGridView::OnHexInit() 
{
	CSetSizeDlg	pDlg;
	double		m_dSize;
	
	m_dSize			= 1.0;
	pDlg.m_dSize	= m_dSize;
	
	if (pDlg.DoModal() == IDOK)
	{
		m_dSize	= pDlg.m_dSize;
	}
	else
		return;

	if (m_pMap.IsOpened())
	{
		double	dLeft,dRight;
		double	dBottom,dTop;
		
		m_pMap.GetMapExt(dLeft,dRight,dBottom,dTop);
		
		m_pHex.CreateGrid(m_dSize,dLeft,dRight,dBottom,dTop);
	}
	
	Invalidate();	
}

void CRoboticGridView::OnHexCreate() 
{
	int	iNumX,iNumY;
	
	iNumX	= m_pHex.GetNumX();
	iNumY	= m_pHex.GetNumY();
	
	for(int j=0;j<iNumY;j++)
	{
		for (int i=0;i<iNumX;i++)
		{	
			//
			double	dGridX,dGridY;
			//int		iGridSubType;
			
			m_pHex.m_pObjList[j*iNumX+i].GetCenter(dGridX,dGridY);
			
			//判断是在哪个多边形中
			{
				int		iSubType;
				bool	bInPolygon	= false;
				
				//提取数据
				CMap_PolygonElement *pPolyon;
				pPolyon = m_pMap.GetPolygonElement();
				
				while( pPolyon != NULL )
				{
					//
					double* dx;
					double* dy;
					int		iPointNum;
					SMap_DPointCoord *pPointList;
					
					iPointNum	= pPolyon->GetPointNum();
					pPointList	= pPolyon->GetPointList();
					
					dx		= new double[iPointNum];
					dy		= new double[iPointNum];
					
					for(int k=0;k<iPointNum;k++)
					{
						dx[k]	= pPointList[k].x;
						dy[k]	= pPointList[k].y;
					}
					
					if (m_pPublicFunction.PointInPolygon(dGridX,dGridY,iPointNum,dx,dy))
					{
						bInPolygon	= true;
						iSubType	= pPolyon->GetSubType();
					}
					
					delete	[]dx;
					delete	[]dy;
					
					pPolyon	= pPolyon->m_pNext;
				}
				
				if (bInPolygon)
				{
					m_pHex.m_pObjList[j*iNumX+i].SetTerrainType(iSubType);
					
					CClientDC	dc(this);
					
					double	dXA,dXB,dYA,dYB;
					m_pMap.GetCoordMapping(dXA,dXB,dYA,dYB);
					
					m_pHex.m_pObjList[j*iNumX+i].SetCoordMapping(dXA,dXB,dYA,dYB);
					
					m_pHex.m_pObjList[j*iNumX+i].Draw(&dc);
				}
			}
		}
	}	

	//
	m_pHex.CreateSide();
}

void CRoboticGridView::OnMapZoomin() 
{
	if (m_pMap.IsOpened())
	{
		double	dShowLeft,dShowRight,dShowBottom,dShowTop;

		m_pMap.GetShowExt(dShowLeft,dShowRight,dShowBottom,dShowTop);

		double	dCenterX,dCenterY;

		dCenterX	= (dShowLeft+dShowRight)/2;
		dCenterY	= (dShowBottom+dShowTop)/2;

		double	dW,dH;
		dW			= (dShowRight - dShowLeft)/4;
		dH			= (dShowTop - dShowBottom)/4;

		
		dShowLeft	= dCenterX-dW;
		dShowRight	= dCenterX+dW;
		dShowBottom	= dCenterY-dH;
		dShowTop	= dCenterY+dH;

		m_pMap.SetShowExt(dShowLeft,dShowRight,dShowBottom,dShowTop);

		Invalidate();
	}
}

void CRoboticGridView::OnMapZoomout() 
{
	if (m_pMap.IsOpened())
	{
		double	dShowLeft,dShowRight,dShowBottom,dShowTop;
		
		m_pMap.GetShowExt(dShowLeft,dShowRight,dShowBottom,dShowTop);
		
		double	dCenterX,dCenterY;
		
		dCenterX	= (dShowLeft+dShowRight)/2;
		dCenterY	= (dShowBottom+dShowTop)/2;
		
		double	dW,dH;
		dW			= (dShowRight - dShowLeft);
		dH			= (dShowTop - dShowBottom);
		
		
		dShowLeft	= dCenterX-dW;
		dShowRight	= dCenterX+dW;
		dShowBottom	= dCenterY-dH;
		dShowTop	= dCenterY+dH;
		
		m_pMap.SetShowExt(dShowLeft,dShowRight,dShowBottom,dShowTop);
		
		Invalidate();
	}	
}

void CRoboticGridView::OnMapPan() 
{
	m_iAction	= 3;
}

void CRoboticGridView::OnMapFull() 
{
	if (m_pMap.IsOpened())
	{
		double	dShowLeft,dShowRight,dShowBottom,dShowTop;
		
		m_pMap.GetMapExt(dShowLeft,dShowRight,dShowBottom,dShowTop);
		
		
		m_pMap.SetShowExt(dShowLeft,dShowRight,dShowBottom,dShowTop);
		
		Invalidate();
	}		
}

void CRoboticGridView::OnGridCalc() 
{
	// TODO: Add your command handler code here
		
	if (m_pMap.IsOpened())
	{
// 		int		iCount;
// 		double	dArea;
// 		iCount	= m_pGrid.CaleGrid(10001,dArea);
// 
// 		CString	szInfo;
// 		szInfo.Format("iCount = %ld dArea = %lf",iCount,dArea);
// 		AfxMessageBox(szInfo);
		
		//m_pGrid.CalcGrid();
		m_pGrid.SetNullTerrain(69, 90, -1, -1, -1, -1);
	}
}

void CRoboticGridView::OnHexCalc() 
{
	// TODO: Add your command handler code here

	if (m_pMap.IsOpened())
	{
// 		int		iCount;
// 		double	dArea;
// 		iCount	= m_pHex.CalcGrid(10001,dArea);
// 		
// 		CString	szInfo;
// 		szInfo.Format("iCount = %ld dArea = %lf",iCount,dArea);
// 		AfxMessageBox(szInfo);

		//m_pHex.CalcGrid();

				//m_pGrid.CalcGrid();
		m_pHex.SetNullTerrain(81,86, -1, -1, -1, -1, -1, -1);
	}
}

void CRoboticGridView::OnMapCalc() 
{
	if (m_pMap.IsOpened())
	{
// 		double	dArea;
// 		m_pMap.Calculate(10001,dArea);
// 		
// 		CString	szInfo;
// 		szInfo.Format("dArea = %lf",dArea);
// 		AfxMessageBox(szInfo);

		//m_pMap.Calculate();
	}
}

void CRoboticGridView::OnGridSavenet() 
{
	if (m_pMap.IsOpened())
	{
		m_pWorkspace.Release();

		//m_pGrid.SaveNetwork("E:\\99-论文\\Data\\EFC-Grid.grdnet");		
		
		double	dLeft,dRight,dBottom,dTop;
		m_pMap.GetMapExt(dLeft,dRight,dBottom,dTop);
		m_pWorkspace.SetMapExt(dLeft,dRight,dBottom,dTop);

		//
		m_pGrid.CreateNetwork(&m_pWorkspace,10001);

		
		Invalidate();
	}
}

void CRoboticGridView::OnAnalyseAdd() 
{
	m_pAnalyse.SetWorkSpace(&m_pWorkspace);	

	m_iAction	= 4;

	double	dX1, dY1;
	dX1 = -19.370942;
	dY1 = 14.484578;
	m_pAnalyse.AddPassNode(dX1, dY1);

	double	dX2, dY2;
	dX2 = 9.598214;
	dY2 = -13.495671;
	m_pAnalyse.AddPassNode(dX2, dY2);
}


void CRoboticGridView::OnAnalyseExec() 
{
	m_pAnalyse.m_nMaxNodeNum	= m_pWorkspace.m_nNodesNum;
	m_pAnalyse.BestRoute(0);
	
	Invalidate();
}

void CRoboticGridView::OnHexCreatenet() 
{
	if (m_pMap.IsOpened())
	{
		m_pWorkspace.Release();

		//m_pGrid.SaveNetwork("E:\\99-论文\\Data\\EFC-Grid.grdnet");		
		
		double	dLeft,dRight,dBottom,dTop;
		m_pMap.GetMapExt(dLeft,dRight,dBottom,dTop);
		m_pWorkspace.SetMapExt(dLeft,dRight,dBottom,dTop);
		
		//
		m_pHex.CreateNetwork(&m_pWorkspace,10001);

		Invalidate();
	}			
}

void CRoboticGridView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//漫游
	if (m_iAction == 3)
	{
		//AfxMessageBox("图形显示");
		m_ptDown	= point;
		m_ptUp		= point;
		m_bMoveFlag	= false;
	}

	//选节点
	if (m_iAction == 4)
	{
		double	dX,dY;
		
		m_pMap.GetScreentPoint(point.x,point.y,dX,dY);
		//
		//double	dX1, dY1;
		//dX1 = -19.370942;
		//dY1 = 14.484578;
		//m_pAnalyse.AddPassNode(dX1,dY1);

		//double	dX2, dY2;
		//dX2 = 9.598214;
		//dY2 = -13.495671;
		//m_pAnalyse.AddPassNode(dX2, dY2);

		//CString	szInfo;
		//szInfo.Format("x=%lf y=%lf",dX,dY);
		//AfxMessageBox(szInfo);
		
		Invalidate();
	}
	
	
	if (m_iAction == 5)
	{
		double	dX,dY;
		
		m_pMap.GetScreentPoint(point.x,point.y,dX,dY);

		int		iType;
		int		iI,iJ;
		iType	= m_pGrid.Query(dX,dY,iI,iJ);
	
		CString	szInfo;
		szInfo.Format("%ld %ld %ld",iI,iJ,iType);
		AfxMessageBox(szInfo);
	}

	if (m_iAction == 6)
	{
		//double	dX, dY;

		//m_pMap.GetScreentPoint(point.x, point.y, dX, dY);

		//int		iType;
		//int		iI, iJ;
		//iType = m_pHex.Query(dX, dY, iI, iJ);

		//CString	szInfo;
		//szInfo.Format("%ld %ld %ld", iI, iJ, iType);
		//AfxMessageBox(szInfo);
	}

	CView::OnLButtonDown(nFlags, point);
}

void CRoboticGridView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//漫游
	if (m_iAction == 3)
	{
		double	dX1,dY1,dX2,dY2,dX,dY;
		
		m_pMap.ScreenToMap(m_ptDown.x,m_ptDown.y,dX1,dY1);
		m_pMap.ScreenToMap(m_ptUp.x,m_ptUp.y,dX2,dY2);
		
		dX	= dX2-dX1;
		dY	= dY2-dY1;
		
		double	dLeft,dRight,dBottom,dTop;
		double	dPreLeft,dPreRight,dPreBottom,dPreTop;
		
		m_pMap.GetShowExt(dPreLeft,dPreRight,dPreBottom,dPreTop);
		
		dLeft		= dPreLeft - dX;
		dRight		= dPreRight -dX;
		dBottom		= dPreBottom - dY;
		dTop		= dPreTop - dY;

		m_pMap.SetShowExt(dLeft,dRight,dBottom,dTop);

		Invalidate();
	}
	
	CView::OnLButtonUp(nFlags, point);
}

void CRoboticGridView::OnMouseMove(UINT nFlags, CPoint point) 
{
	//漫游
	if (m_iAction == 3)
	{
		if(nFlags==1 && (MK_LBUTTON))
		{
// 			CClientDC	dc(m_pMainWnd);
// 			
// 			CBitmap* pOldBitmap	= m_pUserDC->SelectObject(m_pUserBitmap);
// 			CBrush backgroundBrush((COLORREF)::GetSysColor(COLOR_WINDOW));
// 			CBrush*	pOldBrush	= m_pUserDC->SelectObject(&backgroundBrush);
			
			m_ptUp		= point;
			
// 			if((m_ptUp.y-m_ptDown.y)>0)
// 				dc.PatBlt(m_rRect.left, m_rRect.top, m_rRect.right, m_ptUp.y-m_ptDown.y, PATCOPY);
// 			else
// 				dc.PatBlt(m_rRect.left, m_rRect.bottom+(m_ptUp.y-m_ptDown.y), m_rRect.right, m_rRect.bottom, PATCOPY);
// 			
// 			if((m_ptUp.x-m_ptDown.x)>0)
// 				dc.PatBlt(m_rRect.left, m_rRect.top, m_ptUp.x-m_ptDown.x, m_rRect.bottom, PATCOPY);
// 			else
// 				dc.PatBlt(m_rRect.right+(m_ptUp.x-m_ptDown.x), m_rRect.top, m_rRect.right, m_rRect.bottom, PATCOPY);
// 			
// 			//
// 			dc.BitBlt(m_ptUp.x-m_ptDown.x, m_ptUp.y-m_ptDown.y,m_rRect.Width(), m_rRect.Height(),m_pUserDC, m_rRect.left, m_rRect.top, SRCCOPY);
// 			
// 			m_pUserDC->SelectObject(pOldBitmap);
// 			m_pUserDC->SelectObject(pOldBrush);
		}		
	}
		
	CView::OnMouseMove(nFlags, point);
}

void CRoboticGridView::OnMapShowor() 
{
	m_bShowMap	= !m_bShowMap;
	
	Invalidate();
}	

void CRoboticGridView::OnGridShow() 
{
	m_bShowGrid	= !m_bShowGrid;

	Invalidate();
}

void CRoboticGridView::OnGridQuery() 
{
	m_iAction	= 5;	
}

void CRoboticGridView::OnHexShow() 
{
	m_bShowHex	= !m_bShowHex;
	
	Invalidate();
}

void CRoboticGridView::OnHexQuery() 
{
	m_iAction	= 5;	
}

void CRoboticGridView::OnAnalyseClear() 
{
	//m_pAnalyse.ReleaseRoute();
}
