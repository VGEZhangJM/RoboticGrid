// Map_Map.cpp: implementation of the CMap_Map class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboticGrid.h"
#include "Map_Map.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap_Map::CMap_Map()
{
	m_pPointListHead	= NULL;
	m_pPointListLast	= NULL;

	m_pLineListHead		= NULL;
	m_pLineListLast		= NULL;

	m_pPolygonListHead	= NULL;
	m_pPolygonListLast	= NULL;

	//缩放系数
	m_dMapXA		= 1.0;
	m_dMapXB		= 0.0;
	m_dMapYA		= 1.0;
	m_dMapYB		= 0.0;

	//
	m_nWinMinX		= 0;
	m_nWinMinY		= 0;
	m_nWinMaxX		= 0;
	m_nWinMaxY		= 0;

	//
	m_dMapLeft		= 0.0;
	m_dMapRight		= 0.0;
	m_dMapBottom	= 0.0;
	m_dMapTop		= 0.0;

	//
	m_dShowLeft		= 0.0;
	m_dShowRight	= 0.0;
	m_dShowBottom	= 0.0;
	m_dShowTop		= 0.0;

	m_dOldShowLeft		= -1.0;
	m_dOldShowRight		= -1.0;
	m_dOldShowBottom	= -1.0;
	m_dOldShowTop		= -1.0;
}

CMap_Map::~CMap_Map()
{
	CMap_PolygonElement	*gf1,*gf2;
	
	if(m_pPolygonListHead != NULL)
	{
		gf1	=gf2	= m_pPolygonListHead;
		do
		{
			gf1		= gf1->m_pNext;
			delete	gf2;
			gf2		= gf1;
		}while(gf1 != NULL);
		
		m_pPolygonListHead	= NULL;
		m_pPolygonListLast	= NULL;
	}
}

bool CMap_Map::IsOpened()
{
	if (m_pPointListHead != NULL)
	{
		return	true;
	}

	if (m_pLineListHead != NULL)
	{
		return	true;
	}
	if (m_pPolygonListHead != NULL)
	{
		return	true;
	}
	
	return	false;
}

bool CMap_Map::Read(char *chPathName)
{
	FILE *fp;

	fp = fopen(chPathName,"r");

	if (fp == NULL)
	{	
		return	false;
	}

	char	chType[64];
	int		iID;
	int		iMainType;
	int		iSubType;
	int		iPointNum;
	
	while (fscanf(fp,"%s%ld%ld%ld%ld",chType,&iID,&iMainType,&iSubType,&iPointNum) == 5)
	{
		if (strcmp(chType,"Region") == 0)
		{	
			CMap_PolygonElement* pPolygon;

			pPolygon	= new CMap_PolygonElement;

			pPolygon->SetID(iID);
			pPolygon->SetMainType(iMainType);
			pPolygon->SetSubType(iSubType);
			pPolygon->SetPointNum(iPointNum);

			pPolygon->Read(fp);

			if (m_pPolygonListHead == NULL)
			{
				m_pPolygonListHead = pPolygon;
				m_pPolygonListLast = pPolygon;
			}
			else
			{
				m_pPolygonListLast->m_pNext = pPolygon;
				m_pPolygonListLast			= pPolygon;
			}
		}
	}
	
	fclose(fp);

	if (m_pPolygonListHead != NULL)
	{
		CMap_PolygonElement* pPolygon;
		
		pPolygon	= m_pPolygonListHead;
		
		while (pPolygon != NULL)
		{
			double	dELeft,dERight;
			double	dEBottom,dETop;
			
			//
			pPolygon->GetElementExt(dELeft,dERight,dEBottom,dETop);
			
			if (pPolygon == m_pPolygonListHead)
			{
				m_dMapLeft		= dELeft;
				m_dMapRight		= dERight;
				m_dMapBottom	= dEBottom;
				m_dMapTop		= dETop;
			}
			else
			{
				if (m_dMapLeft > dELeft)
				{
					m_dMapLeft	= dELeft;
				}
				
				if (m_dMapRight < dERight)
				{
					m_dMapRight	= dERight;
				}
				
				if (m_dMapBottom > dEBottom)
				{
					m_dMapBottom	= dEBottom;
				}
				if (m_dMapTop < dETop)
				{
					m_dMapTop		= dETop;
				}
			}
			
			pPolygon	= pPolygon->m_pNext;
		}
	}
	else
	{
		m_dMapLeft	= 0.0;
		m_dMapRight	= 0.0;
		m_dMapBottom	= 0.0;
		m_dMapTop		= 0.0;
	}
	
	return	true;
}


//显示参数
void CMap_Map::SetCoordMapping(double dXA,double dXB,double dYA,double dYB)
{
	m_dMapXA	= dXA;
	m_dMapXB	= dXB;
	m_dMapYA	= dYA;
	m_dMapYB	= dYB;
}

void CMap_Map::GetCoordMapping(double& dXA,double& dXB,double& dYA,double& dYB)
{
	dXA	= m_dMapXA;
	dXB	= m_dMapXB;
	dYA	= m_dMapYA;
	dYB	= m_dMapYB;
}

void CMap_Map::ScreenToMap(int cx, int cy, double &xx, double &yy)
{
	xx	= (cx - m_dMapXB) / m_dMapXA;
	yy	= (cy - m_dMapYB) / m_dMapYA;
}

//地图到屏幕的转换
void CMap_Map::MapToScreen(double xx, double yy, int &cx, int &cy)
{
	cx	= (int)(xx*m_dMapXA + m_dMapXB + 0.5);
	cy	= (int)(yy*m_dMapYA + m_dMapYB + 0.5);
}

//
void CMap_Map::Draw(CDC* pDC)
{
	CMap_PolygonElement* pPolygon;
	
	pPolygon	= m_pPolygonListHead;
	
	while (pPolygon != NULL)
	{
		pPolygon->SetCoordMapping(m_dMapXA,m_dMapXB,m_dMapYA,m_dMapYB);
	
		pPolygon->Draw(pDC);

		pPolygon	= pPolygon->m_pNext;
	}

	m_dOldShowLeft	= m_dShowLeft;
	m_dOldShowRight	= m_dShowRight;
	m_dOldShowBottom= m_dShowBottom;
	m_dOldShowTop	= m_dShowTop;
}


//
void CMap_Map::GetMapExt(double& dLeft, double& dRight,double& dBottom, double& dTop)
{
	dLeft	= m_dMapLeft;	//19.601416
	dRight	= m_dMapRight;	//351.501229

	dBottom	= m_dMapBottom;	//4.292342
	dTop	= m_dMapTop;	//88.632476
}
void CMap_Map::SetMapExt(double dLeft, double dRight,double dBottom, double dTop)
{
	m_dMapLeft		= dLeft;
	m_dMapRight		= dRight;
	
	m_dMapBottom	= dBottom;
	m_dMapTop		= dTop;
}

//
void CMap_Map::GetShowExt(double& dLeft, double& dRight,double& dBottom, double& dTop)
{
	dLeft	= m_dShowLeft;
	dRight	= m_dShowRight;
	
	dBottom	= m_dShowBottom;
	dTop	= m_dShowTop;
}
void CMap_Map::SetShowExt(double dLeft, double dRight,double dBottom, double dTop)
{
	m_dShowLeft		= dLeft;
	m_dShowRight	= dRight;
	
	m_dShowBottom	= dBottom;
	m_dShowTop		= dTop;
}

//
void CMap_Map::GetOldShowExt(double& dLeft, double& dRight,double& dBottom, double& dTop)
{
	dLeft	= m_dOldShowLeft;
	dRight	= m_dOldShowRight;
	
	dBottom	= m_dOldShowBottom;
	dTop	= m_dOldShowTop;
}
void CMap_Map::SetOldShowExt(double dLeft, double dRight,double dBottom, double dTop)
{
	m_dOldShowLeft		= dLeft;
	m_dOldShowRight		= dRight;
	
	m_dOldShowBottom	= dBottom;
	m_dOldShowTop		= dTop;
}

void CMap_Map::GetScreentPoint(int iX,int iY,double& dX,double& dY)
{
	dX	= (iX - m_dMapXB)/m_dMapXA;
	dY	= (iY - m_dMapYB)/m_dMapYA;
}

bool CMap_Map::InitShow(CRect rRect, double dLeft, double dRight, double dBottom, double dTop)
{
	if(fabs(dRight-dLeft) < 1e-10)	return	false;
	if(fabs(dTop-dBottom) < 1e-10)	return	false;

	double	dScalex = fabs(rRect.Width() / (dRight-dLeft));
	double	dScaley = fabs(rRect.Height() / (dTop-dBottom));
	
	double	dMapScale;

	dMapScale		= (dScalex<dScaley) ? dScalex : dScaley;

	//缩小
	dMapScale		= dMapScale * 0.96;

	double dWinOrgDistX = (rRect.Width() - fabs(dRight-dLeft)*dMapScale) /2.0;
	double dWinOrgDistY = (rRect.Height() - fabs(dTop-dBottom)*dMapScale) /2.0;

	m_dMapXA		= dMapScale;
	m_dMapXB		= dWinOrgDistX - dLeft * dMapScale + rRect.left;
	m_dMapYA		= -1.0 * dMapScale;
	m_dMapYB		= dBottom * dMapScale - dWinOrgDistY + rRect.bottom;
	
	m_nWinMaxX		= rRect.right;
	m_nWinMinX		= rRect.left;
	m_nWinMaxY		= rRect.bottom;
	m_nWinMinY		= rRect.top;
	
	//设置显示区域
	SetShowExt(dLeft,dRight,dBottom,dTop);

	return	true;
}

//
CMap_PolygonElement* CMap_Map::GetPolygonElement()
{
	return	m_pPolygonListHead;
}

//
int CMap_Map::Calculate(int iTerrainType, double& dArea)
{
	CMap_PolygonElement* pPolygon;
	
	pPolygon	= m_pPolygonListHead;
	
	while (pPolygon != NULL)
	{
		//pPolygon->Draw(pDC);
		if (pPolygon->GetSubType() == iTerrainType)
		{	
			dArea	= pPolygon->GetArea();

			return	1;
		}
		
		pPolygon	= pPolygon->m_pNext;
	}

	return	0;
}

//
void CMap_Map::Calculate()
{
	FILE *fp;

	fp	= fopen("d:\\map_area.txt","w");

	if (fp != NULL)
	{

		CMap_PolygonElement* pPolygon;
		
		pPolygon	= m_pPolygonListHead;
		
		while (pPolygon != NULL)
		{
			double	dArea;
			dArea	= pPolygon->GetArea();
				
			fprintf(fp,"%6ld %.6lf\n", pPolygon->GetSubType(), dArea);
				
			pPolygon	= pPolygon->m_pNext;
		}
		
		fclose(fp);
	}
}