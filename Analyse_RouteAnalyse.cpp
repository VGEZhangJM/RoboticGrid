// Analyse_RouteAnalyse.cpp: implementation of the CAnalyse_RouteAnalyse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Analyse_RouteAnalyse.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAnalyse_RouteAnalyse::CAnalyse_RouteAnalyse()
{
	//道路拓扑数据的结点数
	m_nMaxNodeNum		= 0;

	//道路拓扑数据的结点数的最大值
	m_nMaxLinkLineNum	= 0;

	m_pWorkSpace		= NULL;

	//最短路径
	m_pWayList.RemoveAll();

	//判断矩阵指针
	m_pDJ				= NULL;		
	//邻接结点矩阵指针
	m_pJ				= NULL;

	//
	m_pNodesInWay		= NULL;	
	m_nNodesNumInWay	= 0;
	
	//最短距离
	m_dDistanceMin		= 0.0;
	
	//显示参数
	m_dMapXA			= 1.0;
	m_dMapXB			= 0.0;
	m_dMapYA			= -1.0;
	m_dMapYB			= 0.0;

	//必经结点
	m_pPassNodes.RemoveAll();
	//避开结点
	m_pDisNodes.RemoveAll();
}

CAnalyse_RouteAnalyse::~CAnalyse_RouteAnalyse()
{
	//必经结点数据
	ReleasePassNode();
	
	//最短路径数据
	ReleaseWay();

	//断开路段数据
	ReleaseDisWay();

	//道路拓扑数据
	ReleaseRoute();

	//
	ReleaseWayInfo();
}

//创建赋值矩阵
void CAnalyse_RouteAnalyse::CreateArray(int iMode)
{
	if(m_pWorkSpace == NULL)	return;

	//m_pJ : 结点矩阵
	//m_pDJ: 权值矩阵

	//构造m_pDJ、m_pJ
	if(m_pDJ != NULL)	{	delete	[]m_pDJ;	m_pDJ	= NULL;		}
	if(m_pJ != NULL)	{	delete	[]m_pJ;		m_pJ	= NULL;		}
	
	m_pDJ	= new	double[(m_nMaxNodeNum+1)*(m_nMaxLinkLineNum+1)];
	m_pJ	= new	long[(m_nMaxNodeNum+1)*(m_nMaxLinkLineNum+1)];

	//初始化m_pDJ、m_pJ		
	for(int i=0;i<m_nMaxNodeNum+1;i++)
	{
		for(int j=0;j<m_nMaxLinkLineNum+1;j++)
		{
			m_pJ[i*(m_nMaxLinkLineNum+1)+j]		= 0; 
			m_pDJ[i*(m_nMaxLinkLineNum+1)+j]	= -1;		//断路
		}
	}
	
	//从WorkSpace中取出相关链号，再依据相关链号取出结点号
	//同时给m_pDJ、m_pJ赋值
	{
		CAnalyse_WorkSpace	*pWorkSpace;

		pWorkSpace	= m_pWorkSpace;
		
		if(pWorkSpace)
		{
			CAnalyse_RouteNode	*pRouteNode;
			
			pRouteNode	= pWorkSpace->m_pRouteNodeHead;
			while(pRouteNode != NULL)
			{
				long	nPointNo;
				nPointNo	= pRouteNode->m_nPointNo;
				
				//如果<0,表示改点是被修正的点，计算时抛弃
				if(nPointNo >= 0)
				{
					{
						for(int j=0;j<pRouteNode->m_nLinkLineNum;j++)
						{
							//距离权值
							if(iMode == 0)
							{
								long	nCorrelation;
								long	nWeight;
								
								//
								//if((pRouteNode->m_pLinkFirstNode)[j]==nPointNo)		nCorrelation	= (pRouteNode->m_pLinkLastNode)[j];
								//if((pRouteNode->m_pLinkLastNode)[j]==nPointNo)		nCorrelation	= (pRouteNode->m_pLinkFirstNode)[j];
								//nWeight	= (pRouteNode->m_pLinkWeight)[j];

								if(pRouteNode->m_pNodeLink[j].m_pLinkFirstNode == nPointNo)	nCorrelation	= pRouteNode->m_pNodeLink[j].m_pLinkLastNode;
								if(pRouteNode->m_pNodeLink[j].m_pLinkLastNode == nPointNo)	nCorrelation	= pRouteNode->m_pNodeLink[j].m_pLinkFirstNode;
								nWeight	= (long)(pRouteNode->m_pNodeLink[j].m_pLinkWeight);

								
								//用以处理断路情况
								if(nWeight<0)	nWeight	= -1;

								//
								m_pJ[nPointNo*(m_nMaxLinkLineNum+1)+(j+1)]		= nCorrelation;
								m_pDJ[nPointNo*(m_nMaxLinkLineNum+1)+(j+1)]		= nWeight;	
							}
						}
					}
				}
				
				pRouteNode	= pRouteNode->m_pNext;
			}
		}
	}
}

//返回值是该行中的最小值以及该值的行列号
//di,dj:为返回值
//p:相当于最短距离
double CAnalyse_RouteAnalyse::SearchMinFromRow(long &di, long &dj, long *p)
{
	double	dDistanceMin	= -1.0;
	double	dDistance;

	di	= 1;
	dj	= 1;

	//
	for(int j=1;j<m_nMaxNodeNum+1;j++)
	{
		if(p[j]!=-1)
		{
			for(int i=1;i<(m_nMaxLinkLineNum+1);i++)
			{
				//改进，以权值排序
				if(m_pDJ[j*(m_nMaxLinkLineNum+1)+i] != -1)
				{
					dDistance	= m_pDJ[j*(m_nMaxLinkLineNum+1)+i];
	
					if(dDistance!=-1.0)
					{	
						if(dDistanceMin==-1.0)
						{
							dDistanceMin	= dDistance;
							di				= j;
							dj				= i;
						}
						else
						{
							if(dDistanceMin>dDistance)
							{
								dDistanceMin	= dDistance;
								di				= j;
								dj				= i;
							}
						}
					}

					break;
				}
			}
		}
	}

	return	dDistanceMin;
}

//
double CAnalyse_RouteAnalyse::SearchMinFromRow(long &di,long &dj,long *q,long iNum)
{
	double	dDistanceMin	= -1.0;
	double	dDistance;

	long	w;
	long	II;

	int		iS,iFS;
	iS	= 0;
	iFS	= 0;
	for(int ZJM=0;ZJM<iNum;ZJM++)
	{
		if(q[ZJM] > 0)	iS++;
		else			iFS++;
	}

	CString	szInfo;
	szInfo.Format("有用 %6ld 无用 %6ld 总数 %6ld\n",iS,iFS,iNum);
	TRACE(szInfo);

	di	= 1;
	dj	= 1;

	//
	for(int j=0;j<iNum;j++)
	{
		w	= q[j];

		if(w>0)
		{
			II	= w*(m_nMaxLinkLineNum+1);
			
			bool	bFind;

			bFind	= false;

			for(int i=1;i<(m_nMaxLinkLineNum+1);i++)
			{
				//改进，以权值排序
				if(m_pDJ[II+i] != -1)
				{
					dDistance	= m_pDJ[II+i];

					if(dDistance!=-1.0)
					{	
						if(dDistanceMin==-1.0)
						{
							dDistanceMin	= dDistance;
							di				= w;
							dj				= i;
						}
						else
						{
							if(dDistanceMin>dDistance)
							{
								dDistanceMin	= dDistance;
								di				= w;
								dj				= i;
							}
						}
					}

					bFind	= true;

					break;
				}
			}

			if(!bFind)
			{
				q[j]	= -q[j];
			}
		}
	}

	return	dDistanceMin;
}

double CAnalyse_RouteAnalyse::SearchMinFromRow(long &di,long &dj)
{
	double	dDistanceMin	= -1.0;
	double	dDistance;

	long	w;
	long	II;

	di	= 1;
	dj	= 1;
	
	//
	//{
	//	CString	szInfo;
	////	szInfo.Format("%6ld",m_pUnUsedNode.GetSize());
	//	TRACE(szInfo);
	//}	
	//TRACE("\n");
	int i, j;

	for(j=0;j<m_pUnUsedNode.GetSize();j++)
	{
		w	= m_pUnUsedNode[j];

		if(w>0)
		{
			II	= w*(m_nMaxLinkLineNum+1);
			
			bool	bFind;

			bFind	= false;

			for(i=1;i<(m_nMaxLinkLineNum+1);i++)
			{
				//改进，以权值排序
				if(m_pDJ[II+i] != -1)
				{
					dDistance	= m_pDJ[II+i];

					if(dDistance!=-1.0)
					{	
						if(dDistanceMin==-1.0)
						{
							dDistanceMin	= dDistance;
							di				= w;
							dj				= i;
						}
						else
						{
							if(dDistanceMin>dDistance)
							{
								dDistanceMin	= dDistance;
								di				= w;
								dj				= i;
							}
						}
					}

					bFind	= true;

					break;
				}
			}

			if(!bFind)
			{
				//需要删除的,记录在m_pUsedNode中，但是需要降序排列
				//q[j]	= -q[j];
				if(m_pUsedNode.GetSize() == 0)
				{
					m_pUsedNode.Add(j);
				}
				else
				{	
					for(i=0;i<m_pUsedNode.GetSize();i++)
					{
						if(m_pUsedNode[i] > j)
						{
							break;
						}
					}	

					m_pUsedNode.InsertAt(i,j);
				}
			}
		}
	}

	//整理m_pUnUsedNode，保证所有的节点是没有被处理的
	{
		if(m_pUsedNode.GetSize() != 0)
		{
			for(int I=m_pUsedNode.GetSize()-1;I>=0;I--)
			{
				m_pUnUsedNode.RemoveAt(m_pUsedNode[I]);
			}

			m_pUsedNode.RemoveAll();
		}
	}

	return	dDistanceMin;
}

//寻找路径
void CAnalyse_RouteAnalyse::GetWay(long &nWayNum, long nSP, long nEP, long *pCode)
{
	long	nTheNo;

	if(m_pNodesInWay != NULL)	{	delete	[]m_pNodesInWay;	m_pNodesInWay		= NULL;	}

	m_pNodesInWay	= new	long[m_nMaxNodeNum];

	nWayNum	= 0;
	nTheNo	= nEP;

	//记录
	m_pNodesInWay[nWayNum]		= nTheNo;

	do
	{
		nTheNo					= pCode[nTheNo];
		nWayNum++;
		m_pNodesInWay[nWayNum]	= nTheNo;
	}while(nTheNo!=nSP);

	//调整顺序
	int i;
	for(i=0;i<(nWayNum+1)/2;i++)
	{
		long	nTemp;
		nTemp						= m_pNodesInWay[i];
		m_pNodesInWay[i]			= m_pNodesInWay[nWayNum-i];
		m_pNodesInWay[nWayNum-i]	= nTemp;
	}

	for(i=0;i<nWayNum;i++)
	{
		long		nFirstNode,nLastNode;
	
		nFirstNode	= m_pNodesInWay[i];
		nLastNode	= m_pNodesInWay[i+1];
		
		long				nPointNum;
		SMap_DPointCoord	*pPointCoord;
		
		long		nRouteType;
		long		nWeight;
		char		chName[30];

		//加上弧段号
		pPointCoord	= GetLineFeature(nFirstNode,nLastNode,nRouteType,nPointNum,nWeight,chName);

		if(pPointCoord != NULL)
		{
			CAnalyse_Way	*pWay;
			
			pWay	= new	CAnalyse_Way;

			pWay->m_nFirstNode		= nFirstNode;
			pWay->m_nLastNode		= nLastNode;

			pWay->m_nRouteType		= nRouteType;
			pWay->m_nPointNum		= nPointNum;
			pWay->m_pPointCoord		= pPointCoord;

			pWay->m_nWeight			= nWeight;
			strcpy(pWay->m_chName,chName);
			
			m_pWayList.Add(pWay);
		}
	}

	//建立路径说明	
	m_pWaysInfo.RemoveAll();

	//只有一条线段
	if(m_pWayList.GetSize() == 1)
	{
		//沿着的路径
		CString	szFollowWayName;
		long	nDistance;

		szFollowWayName	= m_pWayList[0]->m_chName;
		nDistance		= m_pWayList[0]->m_nWeight;
		
		CString	szInfo;

		szInfo.Format("沿着【%s】路前行%.2lf米到达目的地\n",szFollowWayName,nDistance);

		TRACE(szInfo);
		
		m_pWaysInfo.Add(szInfo);
	}
	//多条线段
	else
	{
		long nTotalDistance	= 0;

		for(i=0;i<m_pWayList.GetSize()-1;i++)
		{
			//沿着的路径
			CString	szFollowWayName;
			CString	szArriveWayName;
			long	nDistance;

			szFollowWayName	= m_pWayList[i]->m_chName;
			szArriveWayName	= m_pWayList[i+1]->m_chName;
			nDistance		= m_pWayList[i]->m_nWeight;
			nTotalDistance = nTotalDistance + nDistance;
			
			double		dXIn,dYIn;
			double		dXOut,dYOut;
			double		dXO,dYO;
				
			dXIn	= m_pWayList[i]->m_pPointCoord[m_pWayList[i]->m_nPointNum-2].x;
			dYIn	= m_pWayList[i]->m_pPointCoord[m_pWayList[i]->m_nPointNum-2].y;

			dXO		= m_pWayList[i]->m_pPointCoord[m_pWayList[i]->m_nPointNum-1].x;
			dYO		= m_pWayList[i]->m_pPointCoord[m_pWayList[i]->m_nPointNum-1].y;

			dXOut	= m_pWayList[i+1]->m_pPointCoord[1].x;
			dYOut	= m_pWayList[i+1]->m_pPointCoord[1].y;
			
			m_pWayList[i]->m_iDirection	= m_pFunc.JudgeDirection(dXIn,dYIn,dXOut,dYOut,dXO,dYO);

			CString	szInfo;

			if(m_pWayList[i]->m_iDirection == 1)
				szInfo.Format("沿着【%s】路前行%6ld毫米 直行 到达【%s】路\n",szFollowWayName,nDistance,szArriveWayName);
			if(m_pWayList[i]->m_iDirection == 2)
				szInfo.Format("沿着【%s】路前行%6ld毫米 左转 到达【%s】路\n",szFollowWayName,nDistance,szArriveWayName);
			if(m_pWayList[i]->m_iDirection == 3)
				szInfo.Format("沿着【%s】路前行%6ld毫米 右转 到达【%s】路\n",szFollowWayName,nDistance,szArriveWayName);
			
			m_pWaysInfo.Add(szInfo);
		}
		
		//沿着的路径
		CString	szFollowWayName;
		long	nDistance;

		szFollowWayName	= m_pWayList[i]->m_chName;
		nDistance		= m_pWayList[i]->m_nWeight;
		
		CString	szInfo;

		szInfo.Format("沿着【%s】路前行%6ld毫米到达目的地\n",szFollowWayName,nDistance/10);
		TRACE(szInfo);

		m_pWaysInfo.Add(szInfo);

		szInfo.Format("总路程：%6ld 毫米\n", nTotalDistance + nDistance);
		TRACE(szInfo);

		AfxMessageBox(szInfo);
	}
}

//最短路径【结点必须从1开始，否则会出问题】
bool CAnalyse_RouteAnalyse::BestRoute(int iMode,long nSP, long nEP)
{
	if(nSP == nEP)
	{
		MessageBox(NULL,_T("同一接点,道路分析没有意义!!!"), _T("提示信息"), MB_ICONEXCLAMATION  | MB_OK);
		return	false;
	}

	DWORD dwSearchTime;
	DWORD dwAllSearchTime;
	
	dwSearchTime	= 0;

	DWORD dwAllStartTime = GetTickCount();

	//构造矩阵
	CreateArray(iMode);
	
	int i;
	//标记向量p
	long	*p;
	p	= new	long[m_nMaxNodeNum+1];		
	for(i=0;i<m_nMaxNodeNum+1;i++)
	{
		p[i]	= -1;
	}

	//已标记的行q
	long	*q;
	long	iQNum;
	q	= new	long[m_nMaxNodeNum+1];		
	for(i=0;i<m_nMaxNodeNum+1;i++)
	{
		q[i]	= 0;
	}
	iQNum	= 0;

	//初始化
	double		dmin;
	long		di,dj;
	long		w;
	long		ri,rj;
	long		row;

	//相当于第一步：d(s)=0
	p[nSP]			= 0;
	m_dDistanceMin	= 0.0;
	row				= nSP;

	//方法1：记录已标记的向量
	//q[iQNum]		= nSP;
	//iQNum++;

	//方法2：
	m_pUnUsedNode.Add(nSP);
	
	//最短路径的搜索过程
	do
	{
		DWORD dwStartTime = GetTickCount();

		//在已标记的行中，求所有元素的最小值dMin，并记录最小元素的di、dj
		//dmin	= SearchMinFromRow(di,dj,q,iQNum);
		//dmin	= SearchMinFromRow(di,dj,p);
		dmin	= SearchMinFromRow(di,dj);

		DWORD dwFinishTime = GetTickCount();

		dwSearchTime	= dwSearchTime + (dwFinishTime - dwStartTime);

		if(dmin==-1)
		{
			MessageBox(NULL,_T("不存在最短路径!"), _T("提示信息"), MB_ICONEXCLAMATION  | MB_OK);
			
			delete	[]p;
			
			ReleaseRoute();

			return	false;	
		}

		m_dDistanceMin	= dmin;
		w				= m_pJ[di*(m_nMaxLinkLineNum+1)+dj];
		
		if(p[w]==-1)
		{
			p[w]= di;	//这个很巧妙，将结点连接在了一起。

			//方法1：记录已标记的向量
			//q[iQNum]		= w;
			//iQNum++;

			//方法2：
			m_pUnUsedNode.Add(w);

			for(int j=1;j<(m_nMaxLinkLineNum+1);j++)
			{
				if(m_pJ[w*(m_nMaxLinkLineNum+1)+j]==di)
				{
					ri	= w;
					rj	= j;

					break;
				}
			}

			//修正坐标
			for(int k=1;k<m_nMaxLinkLineNum+1;k++)
			{
				if(m_pDJ[w*(m_nMaxLinkLineNum+1)+k]!=-1)
					m_pDJ[w*(m_nMaxLinkLineNum+1)+k]	= m_pDJ[w*(m_nMaxLinkLineNum+1)+k]+m_dDistanceMin;	
			}
		}
		else
		{
			for(int j=1;j<(m_nMaxLinkLineNum+1);j++)
			{
				if(m_pJ[w*(m_nMaxLinkLineNum+1)+j]==di)
				{
					ri	= w;
					rj	= j;
					break;
				}
			}
		}

		m_pDJ[di*(m_nMaxLinkLineNum+1)+dj]	= -1;	//已经搜索过
		m_pDJ[ri*(m_nMaxLinkLineNum+1)+rj]	= -1;	//已经搜索过
	}while(p[nEP]==-1);

	//
	m_pUnUsedNode.RemoveAll();
	m_pUsedNode.RemoveAll();

	DWORD dwAllFinishTime = GetTickCount();
	dwAllSearchTime		= dwAllFinishTime - dwAllStartTime;

	CString szInfo;
	szInfo.Format(_T("路径搜索时间 ：%d ms %d ms\n"), (int)dwAllSearchTime,(int)dwSearchTime);

	TRACE(szInfo);

	//AfxMessageBox(szInfo);

	//根据标记p寻前点，完成最短路径的搜索
	GetWay(m_nNodesNumInWay,nSP,nEP,p);

	//删除中间变量
	delete	[]p;

	delete	[]q;
	
	//删除
	ReleaseRoute();

	return	true;
}

//获取距离
double CAnalyse_RouteAnalyse::GetDistance()
{
	return	m_dDistanceMin;
}

//找和搜索点最近的目标点，都是可以找到的
long CAnalyse_RouteAnalyse::GetPointNo(double &xx, double &yy)
{
	if(m_pWorkSpace == NULL)		return	-1;

	
	return	m_pWorkSpace->GetPointNo(xx,yy);
}

//释放最短路径搜索的中间信息
void CAnalyse_RouteAnalyse::ReleaseRoute()
{
	if(m_pDJ != NULL)			{	delete	[]m_pDJ;			m_pDJ			= NULL;		}
	if(m_pJ != NULL)			{	delete	[]m_pJ;				m_pJ			= NULL;		}
	if(m_pNodesInWay != NULL)	{	delete	[]m_pNodesInWay;	m_pNodesInWay	= NULL;		}
}

//
SMap_DPointCoord* CAnalyse_RouteAnalyse::GetLineFeature(long nFirstNode, long nLastNode, long& nRuteType, long& nPointNum,long &nWeight,char *chName)
{
	nPointNum	= 0;

	if(m_pWorkSpace == NULL)		return	NULL;
	
	return	m_pWorkSpace->GetLineFeature(nFirstNode,nLastNode,nRuteType,nPointNum,nWeight,chName);	
}

//释放数据
void CAnalyse_RouteAnalyse::ReleaseWay()
{
	if(m_pWayList.GetSize() != 0)
	{
		for(int i=0;i<m_pWayList.GetSize();i++)
		{
			CAnalyse_Way	*pWay;
		
			pWay	= m_pWayList[i];
			
			if(pWay->m_pPointCoord != NULL)	delete	[]pWay->m_pPointCoord;

			delete	pWay;
		}

		m_pWayList.RemoveAll();
	}
}

//
void CAnalyse_RouteAnalyse::ReleaseWayInfo()
{
	if(m_pWaysInfo.GetSize() != 0)
	{
		m_pWayList.RemoveAll();
	}
}

//坐标映射
void CAnalyse_RouteAnalyse::SetCoordMapping(double dMapXA, double dMapXB, double dMapYA, double dMapYB)
{
	m_dMapXA	= dMapXA;
	m_dMapXB	= dMapXB;

	m_dMapYA	= dMapYA;
	m_dMapYB	= dMapYB;
}

//绘制拓扑网络
void CAnalyse_RouteAnalyse::DrawNetwork(CDC *pDC)
{
	if(m_pWorkSpace == NULL)	return;
		
	m_pWorkSpace->SetCoordMapping(m_dMapXA,m_dMapXB,m_dMapYA,m_dMapYB);
	m_pWorkSpace->SetShowExt(m_dShowLeft,m_dShowRight,m_dShowBottom,m_dShowTop);

	m_pWorkSpace->OnDraw(pDC);
}

//绘制最短路径
void CAnalyse_RouteAnalyse::DrawBestRoute(CDC *pDC)
{
	if(m_pWayList.GetSize() == NULL)	return;

	HPEN	hOldPen,hNewPen;

	hNewPen		= CreatePen(PS_SOLID,2,RGB(255,0,0));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);

	POINT		*pPoints;
	int			nPointNum;
	
	//////////////////////////////////////////////////////////
	//绘制线
	for(int j=0;j<m_pWayList.GetSize();j++)
	{
		nPointNum	= m_pWayList[j]->m_nPointNum;
		pPoints		= new	POINT[nPointNum];
		
		for(int i=0;i<nPointNum;i++)
		{
			pPoints[i].x	= (long)(m_pWayList[j]->m_pPointCoord[i].x * m_dMapXA + m_dMapXB + 0.5);
			pPoints[i].y	= (long)(m_pWayList[j]->m_pPointCoord[i].y * m_dMapYA + m_dMapYB + 0.5);

			//CString	szInfo;
			//szInfo.Format("%lf %lf %lf %lf %lf %lf\n",m_dMapXA,m_dMapXB,m_dMapYA,m_dMapYB,m_pWayList[j]->m_pPointCoord[i].x ,m_pWayList[j]->m_pPointCoord[i].y);

			//TRACE(szInfo);
		}
		

		pDC->Polyline(pPoints,nPointNum);

		delete	[]pPoints;
	}

	SelectObject(pDC->m_hDC,hOldPen);
	DeleteObject(hNewPen);
	//////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////
	//绘制节点
	hNewPen		= CreatePen(PS_SOLID,1,RGB(255,0,0));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);

	HBRUSH	hOldBrush,hNewBrush;
	hNewBrush	= CreateSolidBrush(RGB(255,255,255));
	hOldBrush	= (HBRUSH)SelectObject(pDC->m_hDC,hNewBrush);

	for(int j=0;j<m_pWayList.GetSize();j++)
	{		
		long	nX,nY;

		nX	= (long)(m_pWayList[j]->m_pPointCoord[0].x * m_dMapXA + m_dMapXB + 0.5);
		nY	= (long)(m_pWayList[j]->m_pPointCoord[0].y * m_dMapYA + m_dMapYB + 0.5);

		pDC->Ellipse(nX-3,nY-3,nX+3,nY+3);

		nX	= (long)(m_pWayList[j]->m_pPointCoord[m_pWayList[j]->m_nPointNum-1].x * m_dMapXA + m_dMapXB + 0.5);
		nY	= (long)(m_pWayList[j]->m_pPointCoord[m_pWayList[j]->m_nPointNum-1].y * m_dMapYA + m_dMapYB + 0.5);

		pDC->Ellipse(nX-3,nY-3,nX+3,nY+3);
	}

	SelectObject(pDC->m_hDC,hOldBrush);
	DeleteObject(hNewBrush);

	SelectObject(pDC->m_hDC,hOldPen);
	DeleteObject(hNewPen);
	//////////////////////////////////////////////////////////
}


//增加必经结点
bool CAnalyse_RouteAnalyse::AddPassNode(CPoint ptPoint)
{
	double	dX,dY;

	dX	= (ptPoint.x - m_dMapXB)/m_dMapXA;
	dY	= (ptPoint.y - m_dMapYB)/m_dMapYA;

	return	AddPassNode(dX,dY);
}

//增加必经结点
bool CAnalyse_RouteAnalyse::AddPassNode(double dX, double dY)
{
	long	nPointNo;

	nPointNo	= GetPointNo(dX,dY);

	for(int i=0;i<m_pPassNodes.GetSize();i++)
	{
		if(m_pPassNodes[i].nPointNo == nPointNo)
		{
			return	false;
		}
	}

	SRoute_Nodes	pNodes;

	pNodes.nPointNo	= nPointNo;
	pNodes.dCoordX	= dX;
	pNodes.dCoordY	= dY;

	m_pPassNodes.Add(pNodes);

	return	true;
}

//绘制必经结点
void CAnalyse_RouteAnalyse::DrawPassNode(CDC *pDC)
{
	if(m_pPassNodes.GetSize() == 0)
	{
		//TRACE("\n没有[必经结点]可供绘制!\n");

		return;
	}

	HINSTANCE hOld	= ::AfxGetResourceHandle();

	#ifdef _DEBUG
		HINSTANCE hin	= ::GetModuleHandle("VR_RouteAnalyseD.dll");
	#else
		HINSTANCE hin	= ::GetModuleHandle("VR_RouteAnalyse.dll");
	#endif

	::AfxSetResourceHandle(hin);
	
	HPEN	hOldPen,hNewPen;
	HBRUSH	hOldBrush,hNewBrush;

	hNewPen		= CreatePen(PS_SOLID,1,RGB(192,192,192));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);
	
	hNewBrush	= CreateSolidBrush(RGB(0,255,255));
	hOldBrush	= (HBRUSH)SelectObject(pDC->m_hDC,hNewBrush);

	//
	for(int i=0;i<m_pPassNodes.GetSize();i++)
	{
		long	iCX,iCY;

		iCX	= (long)(m_pPassNodes[i].dCoordX * m_dMapXA + m_dMapXB + 0.5);
		iCY	= (long)(m_pPassNodes[i].dCoordY * m_dMapYA + m_dMapYB + 0.5);
		
// 		if(i==0)
// 			DrawBitmapPoint(pDC,iCX,iCY,IDR_ROBOTITYPE);
// 		else	if(i==m_pPassNodes.GetSize()-1)
// 			DrawBitmapPoint(pDC,iCX,iCY,IDR_ROBOTITYPE);
// 		else
// 			DrawBitmapPoint(pDC,iCX,iCY,IDR_ROBOTITYPE);
	}

	SelectObject(pDC->m_hDC,hOldBrush);	
	DeleteObject(hNewBrush);	

	SelectObject(pDC->m_hDC,hOldPen);
	DeleteObject(hNewPen);
	
	::AfxSetResourceHandle(hOld);
}

//释放必经结点
void CAnalyse_RouteAnalyse::ReleasePassNode()
{
	m_pPassNodes.RemoveAll();
}

// 增加避开结点
bool CAnalyse_RouteAnalyse::AddDisNode(CPoint ptPoint)
{
	double	dX,dY;

	dX	= (ptPoint.x - m_dMapXB)/m_dMapXA;
	dY	= (ptPoint.y - m_dMapYB)/m_dMapYA;

	return	AddDisNode(dX,dY);
}

// 增加避开结点
bool CAnalyse_RouteAnalyse::AddDisNode(double dX,double dY)
{
	long	nPointNo;

	nPointNo	= GetPointNo(dX,dY);

	for(int i=0;i<m_pDisNodes.GetSize();i++)
	{
		if(m_pDisNodes[i].nPointNo == nPointNo)
		{
			//提示信息：存在结点
			return	false;
		}
	}

	for(int i=0;i<m_pPassNodes.GetSize();i++)
	{
		if(m_pPassNodes[i].nPointNo == nPointNo)
		{
			//提示信息：存在结点
			return	false;
		}
	}

	SRoute_Nodes	pNodes;

	pNodes.nPointNo	= nPointNo;
	pNodes.dCoordX	= dX;
	pNodes.dCoordY	= dY;

	m_pDisNodes.Add(pNodes);

	//////////////////////////////////////////////
	//修改数据中的拓扑关系
	if(m_pWorkSpace)
		m_pWorkSpace->DisNode(nPointNo);
	//////////////////////////////////////////////

	return	true;	
}

// 绘制避开结点
void CAnalyse_RouteAnalyse::DrawDisNode(CDC *pDC)
{
	if(m_pDisNodes.GetSize() == 0)	return;

	HINSTANCE hOld	= ::AfxGetResourceHandle();

	#ifdef _DEBUG
		HINSTANCE hin	= ::GetModuleHandle("VR_RouteAnalyseD.dll");
	#else
		HINSTANCE hin	= ::GetModuleHandle("VR_RouteAnalyse.dll");
	#endif

	::AfxSetResourceHandle(hin);
	
	HPEN	hOldPen,hNewPen;
	HBRUSH	hOldBrush,hNewBrush;

	hNewPen		= CreatePen(PS_SOLID,1,RGB(192,192,192));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);
	
	hNewBrush	= CreateSolidBrush(RGB(0,255,255));
	hOldBrush	= (HBRUSH)SelectObject(pDC->m_hDC,hNewBrush);

	//
	for(int i=0;i<m_pDisNodes.GetSize();i++)
	{
		long	iCX,iCY;

		iCX	= (long)(m_pDisNodes[i].dCoordX * m_dMapXA + m_dMapXB + 0.5);
		iCY	= (long)(m_pDisNodes[i].dCoordY * m_dMapYA + m_dMapYB + 0.5);
		
		//DrawBitmapPoint(pDC,iCX,iCY,IDB_UNPASSPOINT);
	}

	SelectObject(pDC->m_hDC,hOldBrush);	
	DeleteObject(hNewBrush);	

	SelectObject(pDC->m_hDC,hOldPen);
	DeleteObject(hNewPen);
	
	::AfxSetResourceHandle(hOld);	
}

// 删除避开结点
void CAnalyse_RouteAnalyse::ReleaseDisNode()
{
	for(int i=0;i<m_pDisNodes.GetSize();i++)
	{
		m_pWorkSpace->UnDisNode(m_pDisNodes[i].nPointNo);
	}

	m_pDisNodes.RemoveAll();
}

// 增加断开路段
bool CAnalyse_RouteAnalyse::AddDisWay(CPoint ptPoint)
{
	double	dX,dY;

	dX	= (ptPoint.x - m_dMapXB)/m_dMapXA;
	dY	= (ptPoint.y - m_dMapYB)/m_dMapYA;

	return	AddDisWay(dX,dY);
}

// 增加断开路段
bool CAnalyse_RouteAnalyse::AddDisWay(double dX,double dY)
{
	for(int i=0;i<m_pWayList.GetSize();i++)
	{
		if(m_pWayList[i]->GetLine(dX,dY,m_dMapXA))
		{
			CAnalyse_Way	*pWay;
			
			pWay	= new	CAnalyse_Way;
			pWay->Clone(m_pWayList[i]);
			
			//////////////////////////////////////////////
			//增加断开的道路
			m_pDisWayList.Add(pWay);
			//////////////////////////////////////////////

			//////////////////////////////////////////////
			//断路
			if(m_pWorkSpace)
				m_pWorkSpace->DisWay(pWay->m_nFirstNode,pWay->m_nLastNode);
			//////////////////////////////////////////////

			break;
		}
	}

	return	true;
}

// 绘制断开路段
void CAnalyse_RouteAnalyse::DrawDisWay(CDC *pDC)
{
	if(m_pDisWayList.GetSize() == NULL)	return;

	HPEN	hOldPen,hNewPen;

	hNewPen		= CreatePen(PS_SOLID,2,RGB(255,0,0));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);

	POINT		*pPoints;
	int			nPointNum;
	
	//////////////////////////////////////////////////////////
	//绘制线
	for(int j=0;j<m_pDisWayList.GetSize();j++)
	{
		nPointNum	= m_pDisWayList[j]->m_nPointNum;
		pPoints		= new	POINT[nPointNum];
		
		for(int i=0;i<nPointNum;i++)
		{
			pPoints[i].x	= (long)(m_pDisWayList[j]->m_pPointCoord[i].x * m_dMapXA + m_dMapXB + 0.5);
			pPoints[i].y	= (long)(m_pDisWayList[j]->m_pPointCoord[i].y * m_dMapYA + m_dMapYB + 0.5);
		}
		
		pDC->Polyline(pPoints,nPointNum);

		delete	[]pPoints;
	}

	SelectObject(pDC->m_hDC,hOldPen);
	DeleteObject(hNewPen);
	//////////////////////////////////////////////////////////
}

//删除断开路段数据
void CAnalyse_RouteAnalyse::ReleaseDisWay()
{
	if(m_pDisWayList.GetSize() != 0)
	{
		for(int i=0;i<m_pDisWayList.GetSize();i++)
		{
			CAnalyse_Way	*pWay;
		
			pWay	= m_pDisWayList[i];

			m_pWorkSpace->UnDisWay(pWay->m_nFirstNode,pWay->m_nLastNode);

			delete	pWay;
		}

		m_pDisWayList.RemoveAll();
	}
}

//最短路径
bool CAnalyse_RouteAnalyse::BestRoute(int iMode)
{
	if(m_pPassNodes.GetSize()<=1)	
	{
		//提示信息:参数不足
		return false;
	}
	
	m_nMaxLinkLineNum	= m_pWorkSpace->m_nMaxLinkLineNum;

	ReleaseWay();
	
	for(int i=0;i<m_pPassNodes.GetSize()-1;i++)
	{
		long	nSP,nEP;
		nSP	= m_pPassNodes[i].nPointNo;
		nEP	= m_pPassNodes[i+1].nPointNo;

		if(!BestRoute(iMode,nSP,nEP))
			return	false;
	}

	return	true;
}

//绘制
void CAnalyse_RouteAnalyse::DrawBitmapPoint(CDC *pDC,long iCX,long iCY,UINT nIDResource)
{
	CDC			*pMemDC;
	CBitmap		*pBitmap;
	CBitmap		*pOldBitmap;
	BITMAP		bm;

	pMemDC		= new	CDC;
	pBitmap		= new	CBitmap;

	pMemDC->CreateCompatibleDC(pDC);
	pBitmap->LoadBitmap(nIDResource);
	pBitmap->GetBitmap(&bm);
	
	long	nBmpWidth,nBmpHeight;

	nBmpWidth	= bm.bmWidth;
	nBmpHeight	= bm.bmHeight;

	pOldBitmap	= pMemDC->SelectObject(pBitmap);
	
	pDC->StretchBlt(iCX,iCY-nBmpHeight,nBmpWidth,nBmpHeight,pMemDC,0,0,nBmpWidth,nBmpHeight,SRCAND);

	pMemDC->SelectObject(pOldBitmap);
	delete	pBitmap;
	delete	pMemDC;
}

//获取道路拓扑数据
void CAnalyse_RouteAnalyse::SetWorkSpace(CAnalyse_WorkSpace *pWorkSpace)
{
	m_pWorkSpace	= pWorkSpace;
}

void CAnalyse_RouteAnalyse::SetShowExt(double dLeft, double dRight, double dBottom, double dTop)
{
	m_dShowLeft		= dLeft;
	m_dShowRight	= dRight;
	m_dShowBottom	= dBottom;
	m_dShowTop		= dTop;
}

//获取最短路径的数据
// 获取某一道路是有多少条路组成的？
int CAnalyse_RouteAnalyse::GetWayCount()
{
	return	m_pWayList.GetSize();
}

// 获取某一道路的信息
// int iRouteID:			道路编号；
// char* chRouteType：		道路类型；
// char* chRouteName：		道路名称；
// int& iPointNum：			点数
bool CAnalyse_RouteAnalyse::GetWayInformation(int iRouteID, char* chRouteType, char* chRouteName, int& iPointNum)
{
	for (int i=0;i<m_pWayList.GetSize();i++)
	{
		if (iRouteID == i)
		{
			sprintf(chRouteType,"%ld",m_pWayList[i]->m_nRouteType);

			strcpy(chRouteName,m_pWayList[i]->m_chName);
			iPointNum	= m_pWayList[i]->m_nPointNum;

			return	true;
		}
	}
	
	return	false;
}

//获取具体的道路坐标
// int iRouteID:			道路编号；
// double* dX, double* dY	道路坐标
bool CAnalyse_RouteAnalyse::GetWayCoord(int iRouteID, double* dX, double* dY)
{
	for (int i=0;i<m_pWayList.GetSize();i++)
	{
		if (iRouteID == i)
		{
			for (int j=0;j<m_pWayList[i]->m_nPointNum;j++)
			{
				dX[j]	= m_pWayList[i]->m_pPointCoord[j].x;
				dY[j]	= m_pWayList[i]->m_pPointCoord[j].y;
			}
			
			return	true;
		}
	}
	
	return	false;	
}
