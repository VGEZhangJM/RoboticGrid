// Map_PolygonElement.cpp: implementation of the CMap_PolygonElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboticGrid.h"
#include "Map_PolygonElement.h"

#include "PublicFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap_PolygonElement::CMap_PolygonElement()
{
	m_iID			= 0;
	//子类
	m_iSubType		= 0;
	//主类
	m_iMainType		= 0;
	
	m_iPointNum		= 0;	
	m_pPointList	= NULL;

	m_pNext			= NULL;

	m_dLeft		= m_dRight	= 0.0;
	m_dBottom	= m_dTop	= 0.0;

	//缩放系数
	m_dMapXA		= 1.0;
	m_dMapXB		= 0.0;
	m_dMapYA		= 1.0;
	m_dMapYB		= 0.0;
}

CMap_PolygonElement::~CMap_PolygonElement()
{
	if (m_pPointList != NULL)
	{
		delete []m_pPointList;
		m_pPointList	= NULL;
	}
}

//读取文件
bool CMap_PolygonElement::Read(FILE *fp)
{
	if (fp == NULL)
	{
		return	false;
	}
	
// 	int	iID;
// 	int	iMainType;
// 	int iSubType;
// 	int iPointNum;
// 	
// 	fscanf(fp,"%ld%ld%ld%ld",&iID,&iMainType,&iSubType,&iPointNum);
// 	
// 	m_iID = iID;
// 	m_iMainType = iMainType;
// 	m_iSubType = iSubType;
// 	m_iPointNum = iPointNum;
	
	m_pPointList = new SMap_DPointCoord[m_iPointNum];
	for (int i=0;i<m_iPointNum;i++)
	{
		double dx,dy;
		
		fscanf(fp,"%lf%lf",&dx,&dy);

		//做个变换
		//高度172m 宽度是162m
		
		double	dMLeft,dMRight,dMBottom,dMTop;

		dMLeft		= 19.601416;
		dMRight		= 351.501229;
		dMBottom	= 4.292342;
		dMTop		= 88.632476;
		
		dx		= (dx-(dMLeft+dMRight)/2)/(dMRight-dMLeft)*162;
		dy		= (dy-(dMBottom+dMTop)/2)/(dMTop-dMBottom)*172;
		
		//
		m_pPointList[i].x = dx;
		m_pPointList[i].y = dy;

		if (i == 0)
		{
			m_dLeft		= m_dRight		= dx;
			m_dBottom	= m_dTop		= dy;
		}
		else
		{
			if(m_dLeft > dx)	m_dLeft		= dx;
			if(m_dRight < dx)	m_dRight	= dx;

			if(m_dBottom > dy)	m_dBottom	= dy;
			if(m_dTop < dy)		m_dTop		= dy;
		}
	}

	return	true;
}

//
void CMap_PolygonElement::SetID(int iID)
{
	m_iID = iID;
}

int CMap_PolygonElement::GetID()
{
	return	m_iID;
}

void CMap_PolygonElement::SetMainType(int iMainType)
{
	m_iMainType = iMainType;
}

int CMap_PolygonElement::GetMainType()
{
	return	m_iMainType;
}

void CMap_PolygonElement::	SetSubType(int iSubType)
{
	m_iSubType = iSubType;
}

int CMap_PolygonElement::GetSubType()
{
	return m_iSubType;
}

void CMap_PolygonElement::SetPointNum(int iPointNum)
{
	m_iPointNum = iPointNum;
}

int CMap_PolygonElement::GetPointNum()
{
	return	m_iPointNum;
}

void CMap_PolygonElement::GetElementExt(double& dLeft, double& dRight, double& dBottom,double& dTop)
{
	dLeft	= m_dLeft;
	dRight	= m_dRight;
	dBottom	= m_dBottom;
	dTop	= m_dTop;
}

//
void CMap_PolygonElement::SetCoordMapping(double dXA,double dXB,double dYA,double dYB)
{
	m_dMapXA	= dXA;
	m_dMapXB	= dXB;
	m_dMapYA	= dYA;
	m_dMapYB	= dYB;	
}

void CMap_PolygonElement::Draw(CDC* pDC)
{
	if (m_iPointNum > 0)
	{
		POINT* pPoint;
		pPoint	= new POINT[m_iPointNum];
		
		for (int i=0;i<m_iPointNum;i++)
		{
			pPoint[i].x	= (int)(m_pPointList[i].x*m_dMapXA + m_dMapXB + 0.5);
			pPoint[i].y	= (int)(m_pPointList[i].y*m_dMapYA + m_dMapYB + 0.5);
		}

		CPen	*pNewPen,*pOldPen;
		
		pNewPen	= new	CPen;
		pNewPen->CreatePen(PS_SOLID,1,RGB(60,60,60));
		pOldPen	= pDC->SelectObject(pNewPen);
			
		CBrush *pNewBrush,*pOldBrush;
		
		if (m_iSubType == 10001)
		{
			pNewBrush	= new CBrush;
			pNewBrush->CreateSolidBrush(RGB(255,255,255));
			pOldBrush	= pDC->SelectObject(pNewBrush);

		}
		else
		{
			pNewBrush	= new CBrush;
			pNewBrush->CreateSolidBrush(RGB(23,222,221));
			pOldBrush	= pDC->SelectObject(pNewBrush);
		}


		pDC->Polygon(pPoint,m_iPointNum);


		pDC->SelectObject(pOldBrush);
		delete	pNewBrush;

		pDC->SelectObject(pOldPen);
		delete	pNewPen;

		delete	[]pPoint;
		pPoint	= NULL;
	}
	
// 	{
// 		int	iLeft,iRight;
// 		int iBottom,iTop;
// 		
// 		iLeft	= (int)(m_dLeft*m_dMapXA + m_dMapXB + 0.5);
// 		iRight	= (int)(m_dRight*m_dMapXA + m_dMapXB + 0.5);
// 		iBottom	= (int)(m_dBottom*m_dMapYA + m_dMapYB + 0.5);
// 		iTop	= (int)(m_dTop*m_dMapYA + m_dMapYB + 0.5);
// 		
// 		pDC->Rectangle(iLeft,iBottom,iRight,iTop);
// 	}
}

SMap_DPointCoord* CMap_PolygonElement::GetPointList()
{
	return	m_pPointList;
}

double CMap_PolygonElement::GetArea()
{
	double	dArea	= 0.0;
	if(m_iPointNum > 0)
	{
		double	*dx;
		double	*dy;
		
		dx	= new	double[m_iPointNum];
		dy	= new	double[m_iPointNum];

		for(int i=0;i<m_iPointNum;i++)
		{
			dx[i]	= m_pPointList[i].x;
			dy[i]	= m_pPointList[i].y;
		}
		
		CPublicFunction	pFunc;

		dArea	= pFunc.GetArea(m_iPointNum,dx,dy);

		delete	[]dx;
		delete	[]dy;
	}

	return	dArea;
}