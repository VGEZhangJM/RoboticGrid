// Analyse_WorkSpace.cpp: implementation of the CAnalyse_WorkSpace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Analyse_WorkSpace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnalyse_WorkSpace::CAnalyse_WorkSpace()
{
	//道路结点数据
	m_pRouteNodeHead	= NULL;
	m_pRouteNodeLast	= NULL;

	//结点数目
	m_nNodesNum			= 0;

	//最大链接弧段数目
	m_nMaxLinkLineNum	= 0;

	//
	m_dMapLeft			= 0.0;
	m_dMapRight			= 0.0;
	m_dMapBottom		= 0.0;
	m_dMapTop			= 0.0;

	//
	m_dShowLeft			= 0.0;
	m_dShowRight		= 0.0;
	m_dShowBottom		= 0.0;
	m_dShowTop			= 0.0;

	//
	m_dMapXA			= 1.0;
	m_dMapXB			= 0.0;
	m_dMapYA			= -1.0;
	m_dMapYB			= 0.0;
}

CAnalyse_WorkSpace::~CAnalyse_WorkSpace()
{
	Release();
}

//加载道路拓扑数据
bool CAnalyse_WorkSpace::Load(CString szPathName)
{
	DWORD dwStartTime = GetTickCount();

	m_szRutPathName	= szPathName;

	//释放数据
	Release();
	
	FILE	*fp;
	fp	= fopen(szPathName,"rb");

	if(fp == NULL)	return	false;
	
	//地图区域
	fread(&m_dMapLeft,sizeof(double),1,fp);
	fread(&m_dMapRight,sizeof(double),1,fp);
	fread(&m_dMapBottom,sizeof(double),1,fp);
	fread(&m_dMapTop,sizeof(double),1,fp);

	//////////////////////////////////////////////////////////////////
	// 结点数据
	fread(&m_nNodesNum,sizeof(long),1,fp);

	for(int i=0;i<m_nNodesNum;i++)
	{
		CAnalyse_RouteNode	*pRouteNode;

		pRouteNode	= new	CAnalyse_RouteNode;

		pRouteNode->m_dMapLeft		= m_dMapLeft;
		pRouteNode->m_dMapBottom	= m_dMapBottom;

		if(pRouteNode->Load(fp))
		{
			//求取最大邻接结点数
			if(m_nMaxLinkLineNum<pRouteNode->m_nLinkLineNum)
				m_nMaxLinkLineNum	= pRouteNode->m_nLinkLineNum;

			if(m_pRouteNodeHead==NULL)
			{
				m_pRouteNodeHead			= pRouteNode;
				m_pRouteNodeLast			= pRouteNode;
			}
			else
			{
				m_pRouteNodeLast->m_pNext	= pRouteNode;
				m_pRouteNodeLast			= pRouteNode;
			}
		}
		else
		{
			delete	pRouteNode;
		}
	}
	//
	//////////////////////////////////////////////////////////////////

	DWORD dwFinishTime = GetTickCount();

	DWORD dwSearchTime;
	dwSearchTime	= dwFinishTime - dwStartTime;

	CString szInfo;
	szInfo.Format(_T("读取道路拓扑数据时间 ：%d ms\n"), (int)dwSearchTime);

	TRACE(szInfo);

	return	true;
}

//释放道路拓扑数据
void CAnalyse_WorkSpace::Release()
{
	if(m_pRouteNodeHead	!= NULL)
	{
		CAnalyse_RouteNode	*pRN1,*pRN2;
		pRN1	= pRN2	= m_pRouteNodeHead;
		
		do
		{
			pRN1	= pRN1->m_pNext;

			delete	pRN2;

			pRN2	= pRN1;

		}while(pRN1!=NULL);

		m_pRouteNodeHead	= NULL;
		m_pRouteNodeLast	= NULL;
	}
}

//获取结点数据s
long CAnalyse_WorkSpace::GetNodeNum()
{
	return	m_nNodesNum;
}

//
long CAnalyse_WorkSpace::GetPointNo(double &xx, double &yy)
{
	CAnalyse_RouteNode	*pRouteNode;

	double				dMinLength;
	long				nReturnNo;
	double				dX,dY;

	nReturnNo	= -1;
	dMinLength	= 0.0;
	dX			= 0.0;
	dY			= 0.0;

	pRouteNode	= m_pRouteNodeHead;
	while(pRouteNode != NULL)
	{
		if(pRouteNode->m_nPointNo >= 0)
		{
			double	dCoordX,dCoordY;
			double	dMinX,dMinY;
			double	dMin;

			dCoordX	= pRouteNode->m_dCoordX;
			dCoordY	= pRouteNode->m_dCoordY;
			dMinX	= fabs(dCoordX-xx);
			dMinY	= fabs(dCoordY-yy);

			if(dMinX>dMinY)		//获取最大的差值
				dMin	= dMinX;
			else
				dMin	= dMinY;

			if(pRouteNode == m_pRouteNodeHead)
			{
				nReturnNo	= pRouteNode->m_nPointNo;
				dMinLength	= dMin;

				dX			= dCoordX;
				dY			= dCoordY;
			}
			else
			{
				if(dMin<dMinLength)
				{
					nReturnNo	= pRouteNode->m_nPointNo;
					dMinLength	= dMin;

					dX			= dCoordX;
					dY			= dCoordY;
				}
			}		
		}

		pRouteNode	= pRouteNode->m_pNext;
	}

	xx	= dX;
	yy	= dY;

	return	nReturnNo;
}

//
void CAnalyse_WorkSpace::OnDraw(CDC *pDC)
{
	if(m_pRouteNodeHead == NULL)	return;
	
	HPEN	hOldPen,hNewPen;
	HBRUSH	hOldBrush,hNewBrush;

	hNewPen		= CreatePen(PS_SOLID,1,RGB(0,0,192));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);
	
	hNewBrush	= (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush	= (HBRUSH)SelectObject(pDC->m_hDC,hNewBrush);
	
	//绘制结点部分
	CRect				rRect;

	CAnalyse_RouteNode	*pRouteNode;

	pRouteNode	= m_pRouteNodeHead;
	while(pRouteNode != NULL)
	{
		if (pRouteNode->m_nLinkLineNum != 0)
		{
			long	iCX,iCY;

			double	dX,dY;

			dX	= pRouteNode->m_dCoordX;
			dY	= pRouteNode->m_dCoordY;

			//if((dX>=m_dShowLeft&&dX<m_dShowRight) && (dY>=m_dShowBottom&&dY<m_dShowTop))
			{
				iCX	= (long)(dX * m_dMapXA + m_dMapXB + 0.5);
				iCY	= (long)(dY * m_dMapYA + m_dMapYB + 0.5);

				rRect.left	= iCX - 2;
				rRect.right	= iCX + 2;
				rRect.bottom= iCY - 2;
				rRect.top	= iCY + 2;

				pDC->Rectangle(rRect);
			}

			POINT	ptCoord[2];
			
			ptCoord[0].x	= iCX;
			ptCoord[0].y	= iCY;

			for (int i=0;i<pRouteNode->m_nLinkLineNum;i++)
			{
				ptCoord[1].x	= (long)(pRouteNode->m_pNodeLink[i].m_dX * m_dMapXA + m_dMapXB + 0.5);
				ptCoord[1].y	= (long)(pRouteNode->m_pNodeLink[i].m_dY * m_dMapYA + m_dMapYB + 0.5);
					
				pDC->Polyline(ptCoord,2);
			}
		}

		pRouteNode	= pRouteNode->m_pNext;
	}

	SelectObject(pDC->m_hDC,hOldBrush);	

	SelectObject(pDC->m_hDC,hOldPen);
	DeleteObject(hNewPen);	
}

//
void CAnalyse_WorkSpace::SetCoordMapping(double dXA, double dXB, double dYA, double dYB)
{
	m_dMapXA	= dXA;
	m_dMapXB	= dXB;
	m_dMapYA	= dYA;
	m_dMapYB	= dYB;
}

//
void CAnalyse_WorkSpace::SetShowExt(double dLeft, double dRight, double dBottom, double dTop)
{
	m_dShowLeft		= dLeft;
	m_dShowRight	= dRight;
	m_dShowBottom	= dBottom;
	m_dShowTop		= dTop;
}

void CAnalyse_WorkSpace::SetMapExt(double dLeft,double dRight,double dBottom,double dTop)
{
	m_dMapLeft		= dLeft;
	m_dMapRight		= dRight;
	m_dMapBottom	= dBottom;
	m_dMapTop		= dTop;
}

//断路
void CAnalyse_WorkSpace::DisWay(long nFirstNode,long nLastNode)
{
	CAnalyse_RouteNode	*pRouteNode;

	pRouteNode	= m_pRouteNodeHead;
	while(pRouteNode != NULL)
	{
		pRouteNode->DisWay(nFirstNode,nLastNode);

		pRouteNode	= pRouteNode->m_pNext;
	}
}

//恢复断路
void CAnalyse_WorkSpace::UnDisWay(long nFirstNode,long nLastNode)
{
	CAnalyse_RouteNode	*pRouteNode;

	pRouteNode	= m_pRouteNodeHead;
	while(pRouteNode != NULL)
	{
		pRouteNode->UnDisWay(nFirstNode,nLastNode);

		pRouteNode	= pRouteNode->m_pNext;
	}
}

//避开结点
void CAnalyse_WorkSpace::DisNode(long nNode)
{
	CAnalyse_RouteNode	*pRouteNode;

	pRouteNode	= m_pRouteNodeHead;
	while(pRouteNode != NULL)
	{
		pRouteNode->DisNode(nNode);

		pRouteNode	= pRouteNode->m_pNext;
	}
}

//恢复避开结点
void CAnalyse_WorkSpace::UnDisNode(long nNode)
{
	CAnalyse_RouteNode	*pRouteNode;

	pRouteNode	= m_pRouteNodeHead;
	while(pRouteNode != NULL)
	{
		pRouteNode->UnDisNode(nNode);

		pRouteNode	= pRouteNode->m_pNext;
	}
}

//
void CAnalyse_WorkSpace::SetNodesNum(int iNodeNum)
{
	m_nNodesNum	= iNodeNum;
}

//
SMap_DPointCoord* CAnalyse_WorkSpace::GetLineFeature(long nFirstNode, long nLastNode, long& nRouteType, long &nPointNum, long &nWeight, char *chName)
{
	CAnalyse_RouteNode	*pRouteNode;
	SMap_DPointCoord	*pPointCoord;

	nPointNum	= 0;
	pPointCoord	= NULL;

	pRouteNode	= m_pRouteNodeHead;
	while(pRouteNode != NULL)
	{
		if(abs(pRouteNode->m_nPointNo)==nFirstNode || abs(pRouteNode->m_nPointNo)==nLastNode)
		{
			for(int i=0;i<pRouteNode->m_nLinkLineNum;i++)
			{
				double	dX,dY;
				dX	= pRouteNode->m_dCoordX;
				dY	= pRouteNode->m_dCoordY;

				//
				if(pPointCoord == NULL)
				{
					if(abs(pRouteNode->m_pNodeLink[i].m_pLinkFirstNode)==nFirstNode && abs(pRouteNode->m_pNodeLink[i].m_pLinkLastNode)==nLastNode)
					{
						//权值
						nWeight		= (long)(pRouteNode->m_pNodeLink[i].m_pLinkWeight);

						//道路性质
						nRouteType	= 0;
											
						nPointNum	= 2;

						strcpy(chName,"无名路");
						
						double	dXX,dYY;
						dXX	= pRouteNode->m_pNodeLink[i].m_dX;
						dYY	= pRouteNode->m_pNodeLink[i].m_dY;

						//
						if(nPointNum > 0)
						{
							pPointCoord	= new	SMap_DPointCoord[nPointNum];

							pPointCoord[0].x	= dX;	pPointCoord[0].y	= dY;
							pPointCoord[1].x	= dXX;	pPointCoord[1].y	= dYY;
						}


					}
				}
				//

				if(pPointCoord != NULL)	break;
			}
		}

		if(pPointCoord != NULL)	break;

		pRouteNode	= pRouteNode->m_pNext;
	}


	return	pPointCoord;	
}