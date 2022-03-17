// Map_Grid.cpp: implementation of the CMap_Grid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboticGrid.h"
#include "Map_Grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap_Grid::CMap_Grid()
{
	m_iNumX		= 0;
	m_iNumY		= 0;
	
	//这是需要避开的网格
	m_iNullI	= -1;
	m_iNullJ	= -1;

	//如果从某一网格不能达到另一个网格
	m_iFromI = -1;
	m_iFromJ = -1;
	m_iToI = -1;
	m_iToJ = -1;

	//正方形是边长
	m_dSize	= 0;0;
	
	//
	m_pObjList	= NULL;
		
	//
	m_pTerrainList.RemoveAll();
}

CMap_Grid::~CMap_Grid()
{
	if (m_pObjList != NULL)
	{
		delete	[]m_pObjList;
		m_pObjList	=  NULL;
	}

	//
	m_pTerrainList.RemoveAll();

}

bool CMap_Grid::CreateGrid(double dSize, double dLeft,double dRight,double dBottom,double dTop)
{
	if (m_pObjList != NULL)
	{	
		delete	[]m_pObjList;
		m_pObjList	= NULL;
	}	

	m_dLeft		= dLeft;
	m_dRight	= dRight;
	m_dBottom	= dBottom;
	m_dTop		= dTop;

	m_dSize	= dSize;

	m_iNumX		= (int)((m_dRight-m_dLeft)/m_dSize)+1;
	m_iNumY		= (int)((dTop-dBottom)/m_dSize)+1;

	m_pObjList = new CMap_GridObj[m_iNumX * m_iNumY];

	for (int j=0;j<m_iNumY;j++)
	{
		for(int i=0;i<m_iNumX;i++)
		{
			//初始化
			m_pObjList[j*m_iNumX+i].Init(i,j,dLeft,dBottom,dSize);

			//后面再建模赋值
		}
	}

	return	true;
}


//显示参数
void CMap_Grid::SetCoordMapping(double dXA,double dXB,double dYA,double dYB)
{
	m_dMapXA	= dXA;
	m_dMapXB	= dXB;
	m_dMapYA	= dYA;
	m_dMapYB	= dYB;
}

void CMap_Grid::Draw(CDC* pDC,int iTerrainType)
{
	int	i,j;

	for (j=0;j<m_iNumY;j++)
	{
		for(i=0;i<m_iNumX;i++)
		{
			double	dX,dY;

			m_pObjList[j*m_iNumX+i].GetCenter(dX,dY);

			if ( (dX>m_dShowLeft-m_dSize&&dX<m_dShowRight+m_dSize) && ((dY>m_dShowBottom-m_dSize&&dY<m_dShowTop+m_dSize)))
			{
				m_pObjList[j*m_iNumX+i].SetCoordMapping(m_dMapXA,m_dMapXB,m_dMapYA,m_dMapYB);
				m_pObjList[j*m_iNumX+i].Draw(pDC,iTerrainType);
			}
		}
	}
}

//
int CMap_Grid::GetNumX()
{
	return	m_iNumX;
}
int CMap_Grid::GetNumY()
{
	return	m_iNumY;	
}

//
int CMap_Grid::CalcGrid(int iTerrainType, double& dArea)
{
	int		iCount;
	
	iCount	= 0;
	if (m_pObjList != NULL)
	{		
		for (int j=0;j<m_iNumY;j++)
		{
			for(int i=0;i<m_iNumX;i++)
			{
				if (m_pObjList[j*m_iNumX + i].GetTerrainType() == iTerrainType)
				{
					iCount++;
				}
			}
		}
	}
	
	dArea = m_dSize * m_dSize * iCount;

	return	iCount;
}

//计算所有的
void CMap_Grid::CalcGrid()
{
	m_pTerrainList.RemoveAll();

	if (m_pObjList != NULL)
	{		
		for (int j=0;j<m_iNumY;j++)
		{
			for(int i=0;i<m_iNumX;i++)
			{
				int		iTerrainType;
				iTerrainType	= m_pObjList[j*m_iNumX + i].GetTerrainType();
				
				bool	bExist;
				bExist	= false;

				for (int k=0;k<m_pTerrainList.GetSize();k++)
				{
					if (iTerrainType == m_pTerrainList[k].iTerrainType)
					{	
						bExist	= true;
						break;
					}
				}

				if (!bExist)
				{
					SGrid_Info	pInfo;
					pInfo.iTerrainType	= iTerrainType;
					pInfo.dArea			= 0;
					pInfo.iCount		= 0;

					m_pTerrainList.Add(pInfo);
				}
			}
		}
	}
	
	//
	for (int k=0;k<m_pTerrainList.GetSize();k++)
	{
		int		iCount;
		double	dArea;
		
		iCount	= 0;
		dArea	= 0;
		iCount	= CalcGrid(m_pTerrainList[k].iTerrainType, dArea);
	
		m_pTerrainList[k].iCount	= iCount;
		m_pTerrainList[k].dArea		= dArea;
	}
	
	//
	{
		FILE	*fp;
		
		CString	szInfo;
		szInfo.Format("D:\\grid_area_[%.2lf].txt",m_dSize);

		fp	= fopen(szInfo,"w");

		if (fp != NULL)
		{
			//
			for (int k=0;k<m_pTerrainList.GetSize();k++)
			{

				fprintf(fp,"%6ld %6ld %.6lf\n",m_pTerrainList[k].iTerrainType,m_pTerrainList[k].iCount,m_pTerrainList[k].dArea);
			}			

			fclose(fp);
		}
	}
}

bool CMap_Grid::Save(CString szPathName)
{	
	FILE	*fp;
	fp	= fopen(szPathName,"w");

	if (fp != NULL)
	{
		//头文件信息

		fprintf(fp,"%.6lf %.6lf %.6lf %.6lf %6ld %6ld %.6lf\n", m_dLeft,m_dRight,m_dBottom,m_dTop,m_iNumX,m_iNumY,m_dSize);

		for (int j=0;j<m_iNumY;j++)
		{
			for (int i=0;i<m_iNumX;i++)
			{
				int	iID;
				iID	= j*m_iNumX+i;

				int	iType;
				iType	= m_pObjList[iID].GetTerrainType();

				double	dx,dy;
				m_pObjList[iID].GetCenter(dx,dy);
				
				fprintf(fp,"%6ld %6ld %6ld %6ld %.6lf %.6lf\n", iID,i,j,iType,dx,dy);
			}
		}

		fclose(fp);
	}

	return	false;
}

bool CMap_Grid::SaveNetwork(CString szPathName)
{
	FILE	*fp;
	fp	= fopen(szPathName,"w");
	
	if (fp != NULL)
	{
		//地图区域
		fprintf(fp,"%.6lf %.6lf %.6lf %.6lf\n", m_dLeft,m_dRight,m_dBottom,m_dTop);

// 		fread(&m_dLeft,sizeof(double),1,fp);
// 		fread(&m_dRight,sizeof(double),1,fp);
// 		fread(&m_dBottom,sizeof(double),1,fp);
// 		fread(&m_dTop,sizeof(double),1,fp);
		
		//搜索点数
		int	i,j;
		int	iNodeNum	= 0;
		for (j=0;j<m_iNumY;j++)
		{
			for (i=0;i<m_iNumX;i++)
			{
				int	iID;
				iID	= j*m_iNumX+i;
				if (m_pObjList[iID].GetTerrainType() == 10001)
				{
					iNodeNum++;
				}
			}
		}

		//节点数
		fprintf(fp,"%6ld\n", iNodeNum);

		for (j=0;j<m_iNumY;j++)
		{
			for (i=0;i<m_iNumX;i++)
			{
				int	iID;
				iID	= j*m_iNumX+i;
				
				int	iType;
				iType	= m_pObjList[iID].GetTerrainType();

				//这样的网格才有作用
				if (iType == 10001)
				{
					//获取周围四个方向的网格，查看是否可以通行
					SRoute_NodeLink	pNodeLink[4];						
					int				iNodeLinkNum	= 0;

					int	iTopi,iTopj;
					
					for (int k=0;k<4;k++)
					{
						if (k==0)
						{
							//上方
							iTopi	= i;	iTopj	= j+1;
						}
						if (k==1)
						{
							//上方
							iTopi	= i;	iTopj	= j-1;
						}
						if (k==2)
						{
							//左方
							iTopi	= i-1;	iTopj	= j;
						}
						if (k==3)
						{
							//右方
							iTopi	= i+1;	iTopj	= j;
						}

						if( (iTopi>=0&&iTopi<m_iNumX) && (iTopj>=0&&iTopj<m_iNumY) )
						{
							if ( m_pObjList[iTopj*m_iNumX+iTopi].GetTerrainType() == 10001)
							{
								//才有用处
								pNodeLink[iNodeLinkNum].m_pLinkFirstNode	= iID;
								pNodeLink[iNodeLinkNum].m_pLinkLastNode		= iTopj*m_iNumX+iTopi;
								pNodeLink[iNodeLinkNum].m_pLinkWeight		= m_dSize;

								iNodeLinkNum++;
							}
						}							
					}					

					//
					fprintf(fp,"%6ld\n", iNodeLinkNum);

					for (int k=0;k<iNodeLinkNum;k++)
					{
						fprintf(fp,"%6ld %6ld %.6lf\n", pNodeLink[k].m_pLinkFirstNode,pNodeLink[k].m_pLinkLastNode,pNodeLink[k].m_pLinkWeight);
					}
				}
			}
		}
		
		fclose(fp);
	}

	return	false;
}

bool CMap_Grid::CreateNetwork(CAnalyse_WorkSpace *pWorkspace,int iTerrainType)
{
	if (pWorkspace == NULL)		return	false;
	
	//
	pWorkspace->SetMapExt(m_dLeft,m_dRight,m_dBottom,m_dTop);

	//搜索点数
	int	i,j;
	int	iNodesNum	= 0;
	for (j=0;j<m_iNumY;j++)
	{
		for (i=0;i<m_iNumX;i++)
		{
			int	iID;
			iID	= j*m_iNumX+i;
			if (m_pObjList[iID].GetTerrainType() == iTerrainType)
			{
				iNodesNum++;
			}
		}
	}
	
	//节点数
	//pWorkspace->SetNodesNum(iNodesNum);
	pWorkspace->SetNodesNum(m_iNumY*m_iNumX);
	
	for (j=0;j<m_iNumY;j++)
	{
		for (i=0;i<m_iNumX;i++)
		{
			int	iID;
			iID	= j*m_iNumX+i;
			
			int	iType;
			iType	= m_pObjList[iID].GetTerrainType();

			//如当前网格为无用网格，那么跳过
			if (j == m_iNullJ && i == m_iNullI)
				continue;
			
			//如果阻断网格之间的联系
			int	bExistObstacle	= 0;
			if ((j==m_iFromJ&& i==m_iFromI) || (j == m_iToJ && i == m_iToI))
			{
				bExistObstacle++;
			}
			
			//这样的网格才有作用
			if (iType == iTerrainType)
			{
				//获取周围四个方向的网格，查看是否可以通行
				SRoute_NodeLink	pNodeLink[4];						
				int				iNodeLinkNum	= 0;
				
				int	iTopi,iTopj;
				int	k;
				
				for (k=0;k<4;k++)
				{
					if (k==0)
					{
						//上方
						iTopi	= i;	iTopj	= j+1;
					}
					if (k==1)
					{
						//上方
						iTopi	= i;	iTopj	= j-1;
					}
					if (k==2)
					{
						//左方
						iTopi	= i-1;	iTopj	= j;
					}
					if (k==3)
					{
						//右方
						iTopi	= i+1;	iTopj	= j;
					}
					
					//如果是障碍，也不行
					if (iTopj == m_iNullJ && iTopi == m_iNullI)
					{
						continue;
					}

					if ((iTopj == m_iToJ && iTopi == m_iToI) || (iTopj == m_iFromJ && iTopi == m_iFromI))
					{
						bExistObstacle++;
					}

					if (bExistObstacle!=2)
					{
						if( (iTopi>=0&&iTopi<m_iNumX) && (iTopj>=0&&iTopj<m_iNumY) )
						{
							if ( m_pObjList[iTopj*m_iNumX+iTopi].GetTerrainType() == iTerrainType)
							{
								//才有用处
								pNodeLink[iNodeLinkNum].m_pLinkFirstNode	= iID;
								pNodeLink[iNodeLinkNum].m_pLinkLastNode		= iTopj*m_iNumX+iTopi;

								double	dCX,dCY;
								m_pObjList[iTopj*m_iNumX+iTopi].GetCenter(dCX,dCY);

								pNodeLink[iNodeLinkNum].m_dX				= dCX;
								pNodeLink[iNodeLinkNum].m_dY				= dCY;
								pNodeLink[iNodeLinkNum].m_pLinkWeight		= (int)(m_dSize*10000+0.5);
							
								iNodeLinkNum++;
							}
						}							
					}
				}

				CAnalyse_RouteNode	*pRouteNode;
				
				pRouteNode	= new	CAnalyse_RouteNode;
				pRouteNode->m_pNext			= NULL;
				
				pRouteNode->m_dMapLeft		= m_dLeft;
				pRouteNode->m_dMapBottom	= m_dBottom;
				
				//序号
				pRouteNode->m_nPointNo		= iID;
				//坐标
				double	dX,dY;
				m_pObjList[iID].GetCenter(dX,dY);
				pRouteNode->m_dCoordX		= dX;
				pRouteNode->m_dCoordY		= dY;

				pRouteNode->m_nLinkLineNum	= iNodeLinkNum;

				if (iNodeLinkNum == 0)
				{
					pRouteNode->m_pNodeLink	= NULL;
				}
				else
				{
					pRouteNode->m_pNodeLink	= new SRoute_NodeLink[iNodeLinkNum];

					for (k=0;k<iNodeLinkNum;k++)
					{
						pRouteNode->m_pNodeLink[k].m_pLinkFirstNode	= pNodeLink[k].m_pLinkFirstNode;
						pRouteNode->m_pNodeLink[k].m_pLinkLastNode	= pNodeLink[k].m_pLinkLastNode;
						pRouteNode->m_pNodeLink[k].m_dX				= pNodeLink[k].m_dX;
						pRouteNode->m_pNodeLink[k].m_dY				= pNodeLink[k].m_dY;
						pRouteNode->m_pNodeLink[k].m_pLinkWeight	= pNodeLink[k].m_pLinkWeight;
					}			
				}

				//
				if (pWorkspace->m_pRouteNodeHead == NULL)
				{
					pWorkspace->m_pRouteNodeHead	= pRouteNode;
					pWorkspace->m_pRouteNodeLast	= pRouteNode;
				}
				else
				{
					pWorkspace->m_pRouteNodeLast->m_pNext	= pRouteNode;
					pWorkspace->m_pRouteNodeLast	= pRouteNode;
				}
			}//10001
			else
			{
				CAnalyse_RouteNode	*pRouteNode;
				
				pRouteNode	= new	CAnalyse_RouteNode;
				pRouteNode->m_pNext			= NULL;
				
				pRouteNode->m_dMapLeft		= m_dLeft;
				pRouteNode->m_dMapBottom	= m_dBottom;
				
				//序号
				pRouteNode->m_nPointNo		= iID;
				//坐标
				double	dX,dY;
				m_pObjList[iID].GetCenter(dX,dY);
				pRouteNode->m_dCoordX		= dX;
				pRouteNode->m_dCoordY		= dY;
				
				pRouteNode->m_nLinkLineNum	= 0;
				pRouteNode->m_pNodeLink		= NULL;

				//
				if (pWorkspace->m_pRouteNodeHead == NULL)
				{
					pWorkspace->m_pRouteNodeHead	= pRouteNode;
					pWorkspace->m_pRouteNodeLast	= pRouteNode;
				}
				else
				{
					pWorkspace->m_pRouteNodeLast->m_pNext	= pRouteNode;
					pWorkspace->m_pRouteNodeLast	= pRouteNode;
				}

			}
		}//I
	}//J

	pWorkspace->m_nMaxLinkLineNum	= 4;

	return	true;
}

int CMap_Grid::Query(double dX,double dY, int& iI,int& iJ)
{
	
	//搜索点数
	int	i,j;
	int	iNodesNum	= 0;
	for (j=0;j<m_iNumY;j++)
	{
		for (i=0;i<m_iNumX;i++)
		{
			int	iID;
			iID	= j*m_iNumX+i;
			
			double	dLeft,dRight,dBottom,dTop;
			m_pObjList[iID].GetExt(dLeft,dRight,dBottom,dTop);

			if ( (dX>dLeft && dX<dRight) && (dY>dBottom && dY<dTop))
			{
				iI	= i;
				iJ	= j;

				//m_pObjList[iID].SetTerrainType(-1);

				return	m_pObjList[iID].GetTerrainType();
			}
		}
	}

	return	-1;
}

void CMap_Grid::SetNullTerrain(int iNullI, int iNullJ, int iFromI, int iFromJ, int iToI, int iToJ)
{
	m_iNullI = iNullI;
	m_iNullJ = iNullJ;

	m_iFromI = iFromI;
	m_iFromJ = iFromJ;

	m_iToI = iToI;
	m_iToJ = iToJ;
}



void CMap_Grid::SetShowExt(double dLeft,double dRight,double dBottom, double dTop)
{
	m_dShowLeft		= dLeft;
	m_dShowRight	= dRight;
	m_dShowBottom	= dBottom;
	m_dShowTop		= dTop;
}

void CMap_Grid::CreateSide()
{
	if (m_pObjList == NULL)	return;

	int	i,j;

	for (j=0;j<m_iNumY-0;j++)
	{
		for(i=0;i<m_iNumX-0;i++)
		{
			//
			int		iType;
			int		iID;
			iID		= j*m_iNumX + i;
			iType	= m_pObjList[iID].GetTerrainType();
			
			int		iNextType;
			int		iNI,iNJ;

			if (iType != -1)
			{
				//A
				iNI	= i;	iNJ		= j+1;	
				
				if (iNI<0 || iNI>=m_iNumX || iNJ<0 || iNJ>=m_iNumY)
				{
					m_pObjList[iID].m_iSideTypeA	= 2;	//不可通行						
				}
				else
				{
					iNextType	= m_pObjList[iNJ*m_iNumX + iNI].GetTerrainType();
					if (iNextType == -1)
					{
						m_pObjList[iID].m_iSideTypeA	= 2;	//可通行
					}
					else
					{
						if (iNextType == iType)
						{
							m_pObjList[iID].m_iSideTypeA	= 0;	//可通行
						}
						if (iNextType != iType)
						{
							m_pObjList[iID].m_iSideTypeA	= 1;	//不可通行
						}				
					}
				}



				//B
				iNI	= i+1;	iNJ		= j;	
				
				if (iNI<0 || iNI>=m_iNumX || iNJ<0 || iNJ>=m_iNumY)
				{
					m_pObjList[iID].m_iSideTypeB	= 2;	//不可通行						
				}
				else
				{
					iNextType	= m_pObjList[iNJ*m_iNumX + iNI].GetTerrainType();

					if (iNextType == -1)
					{
						m_pObjList[iID].m_iSideTypeB	= 2;	//可通行
					}
					else
					{
						if (iNextType == iType)
						{
							m_pObjList[iID].m_iSideTypeB	= 0;	//可通行
						}
						if (iNextType != iType)
						{
							m_pObjList[iID].m_iSideTypeB	= 1;	//不可通行
						}
					}
				}

				//C
				iNI	= i;	iNJ		= j-1;	
				
				if (iNI<0 || iNI>=m_iNumX || iNJ<0 || iNJ>=m_iNumY)
				{
					m_pObjList[iID].m_iSideTypeC	= 2;	//不可通行						
				}
				else
				{
					iNextType	= m_pObjList[iNJ*m_iNumX + iNI].GetTerrainType();
					if (iNextType == -1)
					{
						m_pObjList[iID].m_iSideTypeC	= 2;	//可通行
					}
					else
					{
						if (iNextType == iType)
						{
							m_pObjList[iID].m_iSideTypeC	= 0;	//可通行
						}
						if (iNextType != iType)
						{
							m_pObjList[iID].m_iSideTypeC	= 1;	//不可通行
						}
					}
				}					


				//D
				iNI	= i-1;	iNJ		= j;	
				
				if (iNI<0 || iNI>=m_iNumX || iNJ<0 || iNJ>=m_iNumY)
				{
					m_pObjList[iID].m_iSideTypeD	= 2;	//不可通行						
				}
				else
				{
					iNextType	= m_pObjList[iNJ*m_iNumX + iNI].GetTerrainType();
					if (iNextType == -1)
					{
						m_pObjList[iID].m_iSideTypeD	= 2;	//可通行
					}
					else
					{
						if (iNextType == iType)
						{
							m_pObjList[iID].m_iSideTypeD	= 0;	//可通行
						}
						if (iNextType != iType)
						{
							m_pObjList[iID].m_iSideTypeD	= 1;	//不可通行
						}
					}
				}
			}
		}
	}
}