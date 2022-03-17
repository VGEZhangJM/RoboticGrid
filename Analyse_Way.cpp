// Analyse_Way.cpp: implementation of the CAnalyse_Way class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Analyse_Way.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnalyse_Way::CAnalyse_Way()
{
	m_nFirstNode	= 0;
	m_nLastNode		= 0;

	m_nPointNum		= 0;
	m_pPointCoord	= NULL;

	m_nWeight		= 0;
	m_nRouteType	= -1;
	strcpy(m_chName,"");

	m_iDirection	= 0;
}

CAnalyse_Way::~CAnalyse_Way()
{
	//if(m_pPointCoord != NULL)	
	//{
	//	delete	[]m_pPointCoord;
	//	m_pPointCoord	= NULL;
	//}
}

bool CAnalyse_Way::GetLine(double dX,double dY,double dMapXA)
{
	double	dMinX,dMaxX,dMinY,dMaxY;
	long	i;
	bool	bFinded;

	double	dLimit;

	//3个像素
	dLimit		= 3.0/dMapXA;
	bFinded		= false;
	
	//计算最大最小值
	for(i=0;i<m_nPointNum;i++)
	{
		if(i == 0)
		{
			dMinX	= dMaxX	= m_pPointCoord[i].x;
			dMinY	= dMaxY	= m_pPointCoord[i].y;
		}
		else
		{
			if(dMinX > m_pPointCoord[i].x)		dMinX	= m_pPointCoord[i].x;
			if(dMaxX < m_pPointCoord[i].x)		dMaxX	= m_pPointCoord[i].x;
			if(dMinY > m_pPointCoord[i].y)		dMinY	= m_pPointCoord[i].y;
			if(dMaxY < m_pPointCoord[i].y)		dMaxY	= m_pPointCoord[i].y;
		}
	}
	
	if((dX>=dMinX-dLimit&&dX<=dMaxX+dLimit) && (dY>=dMinY-dLimit&&dY<=dMaxY+dLimit))
	{
		for(i=0;i<m_nPointNum-1;i++)
		{
			double		dXB,dYB;
			double		dXE,dYE;
			
			dXB		= m_pPointCoord[i].x;
			dYB		= m_pPointCoord[i].y;
			dXE		= m_pPointCoord[i+1].x;
			dYE		= m_pPointCoord[i+1].y;
			
			if(dXB > dXE)	
			{
				dMinX	= dXE;	dMaxX	= dXB;
			}
			else
			{
				dMinX	= dXB;	dMaxX	= dXE;
			}
			
			if(dYB > dYE)
			{
				dMinY	= dYE;	dMaxY	= dYB;
			}
			else
			{
				dMinY	= dYB;	dMaxY	= dYE;
			}
			
			if((dX>=dMinX-dLimit&&dX<=dMaxX+dLimit) && (dY>=dMinY-dLimit&&dY<=dMaxY+dLimit))
			{
				double	dMindx,dMindy;
				double	dd;
				if(fabs(dYB-dYE) <= 1e-10)				//水平
				{
					dMindx	= dMindy	= fabs(dY-dYB);
					dd		= dMindx;
				}
				else	if(fabs(dXB-dXE) <= 1e-10)		//垂直
				{
					dMindx	= dMindy	= fabs(dX-dXB);
					dd		= dMindx;
				}
				else
				{
					dMindx	= fabs((dXE-dXB)*(dY-dYB)/(dYE-dYB)+dXB-dX);
					dMindy	= fabs((dYE-dYB)*(dX-dXB)/(dXE-dXB)+dYB-dY);

					if(dMindx > dMindy)	dd	= dMindy;
					else				dd	= dMindx;
				}
				
				if(dd <dLimit)
				{	
					bFinded	= true;

					break;
				}
			}
		}
	}

	return	bFinded;
}

bool CAnalyse_Way::Clone(CAnalyse_Way* pWay)
{
	//首末结点
	m_nFirstNode	= pWay->m_nFirstNode;
	m_nLastNode		= pWay->m_nLastNode;

	//具体坐标
	m_nPointNum		= pWay->m_nPointNum;
	
	if(m_nPointNum > 0)
	{
		m_pPointCoord	= new	SMap_DPointCoord[m_nPointNum];
		memcpy(m_pPointCoord,pWay->m_pPointCoord,sizeof(SMap_DPointCoord)*m_nPointNum);
	}
	
	//权值
	m_nWeight		= pWay->m_nWeight;
	//名称
	strcpy(m_chName,pWay->m_chName);

	return	true;
}
