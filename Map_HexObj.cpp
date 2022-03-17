// Map_HexObj.cpp: implementation of the CMap_HexObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboticGrid.h"
#include "Map_HexObj.h"

#include <MATH.H>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap_HexObj::CMap_HexObj()
{
	m_iI	= -1;
	m_iJ	= -1;
	
	m_dInitiativeX	= 0.0;
	m_dInitiativeY	= 0.0;
	
	m_dSize	= 0.0;
	
	m_iTerrainType	= -1;
	m_iSideTypeA	= -1;
	m_iSideTypeB	= -1;
	m_iSideTypeC	= -1;
	m_iSideTypeD	= -1;
	m_iSideTypeE	= -1;
	m_iSideTypeF	= -1;
}

CMap_HexObj::~CMap_HexObj()
{
	
}

//
void CMap_HexObj::Init(int iI,int iJ, double dOrignX,double dOrignY, double dSize)
{
	m_iI	= iI;
	m_iJ	= iJ;
	
	m_dInitiativeX	= dOrignX;
	m_dInitiativeY	= dOrignY;
	
	//指的是对边的距离
	m_dSize	= dSize;
	
	//
	//具体的尺寸
	double	dSizeX,dSizeY;
	dSizeX		= sqrt(3.0)/2.0*dSize;
	dSizeY		= dSize;

	//
	//计算坐标
	//列被2整除
	//这里算
	if(m_iI%2==0)
	{
		m_dCenterX	= ( ( 2.0/3 * dSizeX ) + m_iI * dSizeX );
		m_dCenterY	= ( ( 1.0/2 * dSizeY ) + m_iJ * dSizeY );
	}
	else
		//列不被整除
	{
		m_dCenterX	= ( ( 2.0/3 * dSizeX ) + m_iI * dSizeX );
		m_dCenterY	= ( dSizeY + m_iJ * dSizeY );
	}
	
	// 计算六角格的六个角点的坐标值
	{
		// 第一个点：
		m_dCornerX[0]	= m_dCenterX + ( 1.0/3 * dSizeX );
		m_dCornerY[0]	= m_dCenterY - ( 1.0/2 * dSizeY );
		
		// 第二个点：
		m_dCornerX[1]	= m_dCenterX - ( 1.0/3 * dSizeX );
		m_dCornerY[1]	= m_dCenterY - ( 1.0/2 * dSizeY );
		
		// 第三个点：
		m_dCornerX[2]	= m_dCenterX - ( 2.0/3 * dSizeX );
		m_dCornerY[2]	= m_dCenterY;
		
		// 第四个点：
		m_dCornerX[3]	= m_dCenterX - ( 1.0/3 * dSizeX );
		m_dCornerY[3]	= m_dCenterY + ( 1.0/2 * dSizeY );
		
		// 第五个点：
		m_dCornerX[4]	= m_dCenterX + ( 1.0/3 * dSizeX );
		m_dCornerY[4]	= m_dCenterY + ( 1.0/2 * dSizeY );
		
		// 第六个点：
		m_dCornerX[5]	= m_dCenterX + ( 2.0/3 * dSizeX );
		m_dCornerY[5]	= m_dCenterY;
	}
}


void CMap_HexObj::GetCenter(double& dX,double& dY)
{
	dX	= m_dInitiativeX + m_dCenterX;
	dY	= m_dInitiativeY + m_dCenterY;
}

//显示参数
void CMap_HexObj::SetCoordMapping(double dXA,double dXB,double dYA,double dYB)
{
	m_dMapXA	= dXA;
	m_dMapXB	= dXB;
	m_dMapYA	= dYA;
	m_dMapYB	= dYB;
}

void CMap_HexObj::Draw(CDC* pDC)
{
	if (m_iTerrainType == -1)
	{
		return;
	}
	
	for (int i=0;i<6;i++)
	{
		double	dX,dY;
		dX	= m_dInitiativeX + m_dCornerX[i];
		dY	= m_dInitiativeY + m_dCornerY[i];

		m_ptCornerPoint[i].x	= (int)(dX*m_dMapXA + m_dMapXB + 0.5);
		m_ptCornerPoint[i].y	= (int)(dY*m_dMapYA + m_dMapYB + 0.5);
	}
	m_ptCornerPoint[6]	= m_ptCornerPoint[0];
	

	if (m_iTerrainType == 10001)
	{
		DrawPolyon(pDC,7,m_ptCornerPoint,RGB(255,255,255),RGB(250,250,250));
	}
	else	if (m_iTerrainType == 20001  || m_iTerrainType == 20002)
	{
		DrawPolyon(pDC,7,m_ptCornerPoint,RGB(255,255,255),RGB(229,218,232));
	}
	else	if (m_iTerrainType == 20003 || m_iTerrainType == 20004)
	{
		DrawPolyon(pDC,7,m_ptCornerPoint,RGB(255,255,255),RGB(250,236,205));
	}
	else	if (m_iTerrainType == 20007 || m_iTerrainType == 20008)
	{
		DrawPolyon(pDC,7,m_ptCornerPoint,RGB(255,255,255),RGB(229, 218, 232));
	}
	else
	{
		DrawPolyon(pDC,7,m_ptCornerPoint,RGB(255,255,255),RGB(250, 236, 205));
	}

	POINT		ptPoint[2];

	ptPoint[0]	= m_ptCornerPoint[3];
	ptPoint[1]	= m_ptCornerPoint[4];	
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


	ptPoint[0]	= m_ptCornerPoint[4];
	ptPoint[1]	= m_ptCornerPoint[5];	
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

	
	ptPoint[0]	= m_ptCornerPoint[5];
	ptPoint[1]	= m_ptCornerPoint[0];	
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

	ptPoint[0]	= m_ptCornerPoint[0];
	ptPoint[1]	= m_ptCornerPoint[1];	
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

	ptPoint[0]	= m_ptCornerPoint[1];
	ptPoint[1]	= m_ptCornerPoint[2];	
	if (m_iSideTypeE == 0)
	{
		DrawLine(pDC,2,ptPoint,RGB(255,255,255));
	}
	if (m_iSideTypeE == 1)
	{
		DrawLine(pDC,2,ptPoint,RGB(192,192,192));
	}
	if (m_iSideTypeE == 2)
	{
		DrawLine(pDC,2,ptPoint,RGB(0,0,0));
	}

	ptPoint[0]	= m_ptCornerPoint[2];
	ptPoint[1]	= m_ptCornerPoint[3];	
	if (m_iSideTypeF == 0)
	{
		DrawLine(pDC,2,ptPoint,RGB(255,255,255));
	}
	if (m_iSideTypeF == 1)
	{
		DrawLine(pDC,2,ptPoint,RGB(192,192,192));
	}
	if (m_iSideTypeF == 2)
	{
		DrawLine(pDC,2,ptPoint,RGB(0,0,0));
	}

 	//{
 	//	int cx,cy;
 	//	double	dCX,dCY;
 	//	dCX	= m_dInitiativeX + m_dCenterX;
 	//	dCY	= m_dInitiativeY + m_dCenterY;
 	//	cx	= (int)(dCX*m_dMapXA + m_dMapXB + 0.5);
 	//	cy	= (int)(dCY*m_dMapYA + m_dMapYB + 0.5);
 	//	
 	//	CString	szInfo;
 	//	szInfo.Format("%ld %ld",m_iI,m_iJ);
 	//	pDC->TextOut(cx,cy,szInfo);
 	//}
}

void CMap_HexObj::DrawPolyon(CDC* pDC, int iPointNum, POINT* pPoint, COLORREF crLine,COLORREF crFull)
{
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
	
	pDC->Polygon(pPoint,iPointNum);
	
	pDC->SelectObject(pOldBrush);
	delete	pNewBrush;	
	
 	pDC->SelectObject(pBackup);	
// 
// 	pDC->SelectObject(pOldPen);
// 	delete	pNewPen;
}

void CMap_HexObj::DrawLine(CDC* pDC, int iPointNum, POINT* pPoint, COLORREF crLine)
{
	CPen	*pNewPen,*pOldPen;
	pNewPen		= new	CPen;
	pNewPen->CreatePen(PS_SOLID,1,crLine);
	pOldPen		= pDC->SelectObject(pNewPen);

	pDC->Polyline(pPoint,iPointNum);

	pDC->SelectObject(pOldPen);
	delete	pNewPen;
}

void CMap_HexObj::SetTerrainType(int iTerrainType)
{
	if (iTerrainType == 20001 || iTerrainType == 20002 || iTerrainType == 20003 || iTerrainType == 20004)
		iTerrainType = -1;

	m_iTerrainType	= iTerrainType;
}

int CMap_HexObj::GetTerrainType()
{
	return	m_iTerrainType;
}
