// Map_GridObj.cpp: implementation of the CMap_GridObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboticGrid.h"
#include "Map_GridObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap_GridObj::CMap_GridObj()
{
	m_iI	= -1;
	m_iJ	= -1;
	
	m_dOrignX	= 0.0;
	m_dOrignY	= 0.0;
	
	m_dSize	= 0.0;

	m_iTerrainType	= -1;

	m_iSideTypeA	= -1;
	m_iSideTypeB	= -1;
	m_iSideTypeC	= -1;
	m_iSideTypeD	= -1;
}

CMap_GridObj::~CMap_GridObj()
{

}

//
void CMap_GridObj::Init(int iI,int iJ, double dOrignX,double dOrignY, double dHeight)
{
	m_iI	= iI;
	m_iJ	= iJ;

	m_dOrignX	= dOrignX;
	m_dOrignY	= dOrignY;
	
	m_dSize	= dHeight;

	m_dCenterX	= iI * dHeight + dOrignX + dHeight/2;
	m_dCenterY	= iJ * dHeight + dOrignY + dHeight/2;
}

//ÏÔÊ¾²ÎÊý
void CMap_GridObj::SetCoordMapping(double dXA,double dXB,double dYA,double dYB)
{
	m_dMapXA	= dXA;
	m_dMapXB	= dXB;
	m_dMapYA	= dYA;
	m_dMapYB	= dYB;
}

void CMap_GridObj::Draw(CDC* pDC,int iTerrainType)
{
	if (m_iTerrainType == -1)
	{
		return;
	}	

	if (iTerrainType != -1)
	{
		if (m_iTerrainType != iTerrainType)
		{
			return;
		}
	}
	
	double	dLeft,dRight;
	double	dBottom,dTop;

	dLeft	= m_dOrignX + m_iI*m_dSize;
	dRight	= dLeft + m_dSize;

	dBottom	= m_dOrignY + m_iJ*m_dSize;
	dTop	= dBottom + m_dSize;

	int	iLeft,iRight;
	int iBottom,iTop;
	
	iLeft	= (int)(dLeft*m_dMapXA + m_dMapXB + 0.5);
	iRight	= (int)(dRight*m_dMapXA + m_dMapXB + 0.5);
	iBottom	= (int)(dBottom*m_dMapYA + m_dMapYB + 0.5);
	iTop	= (int)(dTop*m_dMapYA + m_dMapYB + 0.5);

	if (m_iTerrainType == 10001)
	{
		DrawRectangle(pDC,iLeft,iRight,iBottom,iTop,RGB(255,255,255),RGB(250,250,250));
	}
	else	if (m_iTerrainType == 20001  || m_iTerrainType == 20002)
	{
		DrawRectangle(pDC,iLeft,iRight,iBottom,iTop,RGB(255,255,255),RGB(229,218,232));
	}
	else	if (m_iTerrainType == 20003 || m_iTerrainType == 20004)
	{
		DrawRectangle(pDC,iLeft,iRight,iBottom,iTop,RGB(255,255,255),RGB(250,236,205));
	}
	else	if (m_iTerrainType == 20007 || m_iTerrainType == 20008)
	{
		DrawRectangle(pDC,iLeft,iRight,iBottom,iTop,RGB(255,255,255),RGB(229, 218, 232));
	}
	else
	{
		DrawRectangle(pDC,iLeft,iRight,iBottom,iTop,RGB(255,255,255),RGB(250, 236, 205));
	}


	POINT		ptPoint[2];
	
	ptPoint[0].x	= iLeft;	ptPoint[0].y	= iTop;	
	ptPoint[1].x	= iRight;	ptPoint[1].y	= iTop;		
	if (m_iSideTypeA == 0)
	{
		DrawLine(pDC,2,ptPoint,RGB(255,255,255));
	}
	if (m_iSideTypeA == 1)
	{
		DrawLine(pDC,2,ptPoint,RGB(192,192,192));
	}
	if (m_iSideTypeA == 2)
	{
		DrawLine(pDC,2,ptPoint,RGB(0,0,0));
	}
	
	
	ptPoint[0].x	= iRight;	ptPoint[0].y	= iTop;	
	ptPoint[1].x	= iRight;	ptPoint[1].y	= iBottom;		
	if (m_iSideTypeB == 0)
	{
		DrawLine(pDC,2,ptPoint,RGB(255,255,255));
	}
	if (m_iSideTypeB == 1)
	{
		DrawLine(pDC,2,ptPoint,RGB(192,192,192));
	}
	if (m_iSideTypeB == 2)
	{
		DrawLine(pDC,2,ptPoint,RGB(0,0,0));
	}
	
	
	ptPoint[0].x	= iRight;	ptPoint[0].y	= iBottom;	
	ptPoint[1].x	= iLeft;	ptPoint[1].y	= iBottom;		
	if (m_iSideTypeC == 0)
	{
		DrawLine(pDC,2,ptPoint,RGB(255,255,255));
	}
	if (m_iSideTypeC == 1)
	{
		DrawLine(pDC,2,ptPoint,RGB(192,192,192));
	}
	if (m_iSideTypeC == 2)
	{
		DrawLine(pDC,2,ptPoint,RGB(0,0,0));
	}
	
	ptPoint[0].x	= iLeft;	ptPoint[0].y	= iBottom;	
	ptPoint[1].x	= iLeft;	ptPoint[1].y	= iTop;		
	if (m_iSideTypeD == 0)
	{
		DrawLine(pDC,2,ptPoint,RGB(255,255,255));
	}
	if (m_iSideTypeD == 1)
	{
		DrawLine(pDC,2,ptPoint,RGB(192,192,192));
	}
	if (m_iSideTypeD == 2)
	{
		DrawLine(pDC,2,ptPoint,RGB(0,0,0));
	}
}

void CMap_GridObj::GetCenter(double& dX,double& dY)
{
	dX	= m_dCenterX;
	dY	= m_dCenterY;
}

void CMap_GridObj::GetExt(double& dLeft,double& dRight,double& dBottom,double& dTop)
{
	dLeft	= m_dOrignX + m_iI*m_dSize;
	dRight	= dLeft + m_dSize;
	
	dBottom	= m_dOrignY + m_iJ*m_dSize;
	dTop	= dBottom + m_dSize;	
}

void CMap_GridObj::SetTerrainType(int iTerrainType)
{
	if (iTerrainType == 20001 || iTerrainType == 20002 || iTerrainType == 20003 || iTerrainType == 20004)
		iTerrainType = -1;

	m_iTerrainType	= iTerrainType;
}

int CMap_GridObj::GetTerrainType()
{
	return	m_iTerrainType;
}

void CMap_GridObj::DrawRectangle(CDC* pDC, int iLeft, int iRight, int iBottom, int iTop, COLORREF crLine, COLORREF crFull)
{
	POINT	ptPoints[5];

	ptPoints[0].x	= iLeft;	ptPoints[0].y	= iTop;
	ptPoints[1].x	= iLeft;	ptPoints[1].y	= iBottom;
	ptPoints[2].x	= iRight;	ptPoints[2].y	= iBottom;
	ptPoints[3].x	= iRight;	ptPoints[3].y	= iTop;
	ptPoints[4]		= ptPoints[0];

// 	CPen	*pNewPen,*pOldPen;
// 	pNewPen		= new	CPen;
// 	pNewPen->CreatePen(PS_SOLID,1,crLine);
// 	pOldPen		= pDC->SelectObject(pNewPen);
	
	CGdiObject	*pBackup;
	pBackup		= pDC->SelectStockObject(NULL_PEN);
	
	
	CBrush	*pNewBrush,*pOldBrush;
	pNewBrush		= new	CBrush;
	pNewBrush->CreateSolidBrush(crFull);
	pOldBrush		= pDC->SelectObject(pNewBrush);
	
	pDC->Polygon(ptPoints,5);
	
	pDC->SelectObject(pOldBrush);
	delete	pNewBrush;	

	pDC->SelectObject(pBackup);	

// 	pDC->SelectObject(pOldPen);
// 	delete	pNewPen;
}

void CMap_GridObj::DrawLine(CDC* pDC, int iPointNum, POINT* pPoint, COLORREF crLine)
{
	CPen	*pNewPen,*pOldPen;
	pNewPen		= new	CPen;
	pNewPen->CreatePen(PS_SOLID,1,crLine);
	pOldPen		= pDC->SelectObject(pNewPen);
	
	pDC->Polyline(pPoint,iPointNum);
	
	pDC->SelectObject(pOldPen);
	delete	pNewPen;
}
