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
	//��·�������ݵĽ����
	m_nMaxNodeNum		= 0;

	//��·�������ݵĽ���������ֵ
	m_nMaxLinkLineNum	= 0;

	m_pWorkSpace		= NULL;

	//���·��
	m_pWayList.RemoveAll();

	//�жϾ���ָ��
	m_pDJ				= NULL;		
	//�ڽӽ�����ָ��
	m_pJ				= NULL;

	//
	m_pNodesInWay		= NULL;	
	m_nNodesNumInWay	= 0;
	
	//��̾���
	m_dDistanceMin		= 0.0;
	
	//��ʾ����
	m_dMapXA			= 1.0;
	m_dMapXB			= 0.0;
	m_dMapYA			= -1.0;
	m_dMapYB			= 0.0;

	//�ؾ����
	m_pPassNodes.RemoveAll();
	//�ܿ����
	m_pDisNodes.RemoveAll();
}

CAnalyse_RouteAnalyse::~CAnalyse_RouteAnalyse()
{
	//�ؾ��������
	ReleasePassNode();
	
	//���·������
	ReleaseWay();

	//�Ͽ�·������
	ReleaseDisWay();

	//��·��������
	ReleaseRoute();

	//
	ReleaseWayInfo();
}

//������ֵ����
void CAnalyse_RouteAnalyse::CreateArray(int iMode)
{
	if(m_pWorkSpace == NULL)	return;

	//m_pJ : ������
	//m_pDJ: Ȩֵ����

	//����m_pDJ��m_pJ
	if(m_pDJ != NULL)	{	delete	[]m_pDJ;	m_pDJ	= NULL;		}
	if(m_pJ != NULL)	{	delete	[]m_pJ;		m_pJ	= NULL;		}
	
	m_pDJ	= new	double[(m_nMaxNodeNum+1)*(m_nMaxLinkLineNum+1)];
	m_pJ	= new	long[(m_nMaxNodeNum+1)*(m_nMaxLinkLineNum+1)];

	//��ʼ��m_pDJ��m_pJ		
	for(int i=0;i<m_nMaxNodeNum+1;i++)
	{
		for(int j=0;j<m_nMaxLinkLineNum+1;j++)
		{
			m_pJ[i*(m_nMaxLinkLineNum+1)+j]		= 0; 
			m_pDJ[i*(m_nMaxLinkLineNum+1)+j]	= -1;		//��·
		}
	}
	
	//��WorkSpace��ȡ��������ţ��������������ȡ������
	//ͬʱ��m_pDJ��m_pJ��ֵ
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
				
				//���<0,��ʾ�ĵ��Ǳ������ĵ㣬����ʱ����
				if(nPointNo >= 0)
				{
					{
						for(int j=0;j<pRouteNode->m_nLinkLineNum;j++)
						{
							//����Ȩֵ
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

								
								//���Դ����·���
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

//����ֵ�Ǹ����е���Сֵ�Լ���ֵ�����к�
//di,dj:Ϊ����ֵ
//p:�൱����̾���
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
				//�Ľ�����Ȩֵ����
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
	szInfo.Format("���� %6ld ���� %6ld ���� %6ld\n",iS,iFS,iNum);
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
				//�Ľ�����Ȩֵ����
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
				//�Ľ�����Ȩֵ����
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
				//��Ҫɾ����,��¼��m_pUsedNode�У�������Ҫ��������
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

	//����m_pUnUsedNode����֤���еĽڵ���û�б������
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

//Ѱ��·��
void CAnalyse_RouteAnalyse::GetWay(long &nWayNum, long nSP, long nEP, long *pCode)
{
	long	nTheNo;

	if(m_pNodesInWay != NULL)	{	delete	[]m_pNodesInWay;	m_pNodesInWay		= NULL;	}

	m_pNodesInWay	= new	long[m_nMaxNodeNum];

	nWayNum	= 0;
	nTheNo	= nEP;

	//��¼
	m_pNodesInWay[nWayNum]		= nTheNo;

	do
	{
		nTheNo					= pCode[nTheNo];
		nWayNum++;
		m_pNodesInWay[nWayNum]	= nTheNo;
	}while(nTheNo!=nSP);

	//����˳��
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

		//���ϻ��κ�
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

	//����·��˵��	
	m_pWaysInfo.RemoveAll();

	//ֻ��һ���߶�
	if(m_pWayList.GetSize() == 1)
	{
		//���ŵ�·��
		CString	szFollowWayName;
		long	nDistance;

		szFollowWayName	= m_pWayList[0]->m_chName;
		nDistance		= m_pWayList[0]->m_nWeight;
		
		CString	szInfo;

		szInfo.Format("���š�%s��·ǰ��%.2lf�׵���Ŀ�ĵ�\n",szFollowWayName,nDistance);

		TRACE(szInfo);
		
		m_pWaysInfo.Add(szInfo);
	}
	//�����߶�
	else
	{
		long nTotalDistance	= 0;

		for(i=0;i<m_pWayList.GetSize()-1;i++)
		{
			//���ŵ�·��
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
				szInfo.Format("���š�%s��·ǰ��%6ld���� ֱ�� ���%s��·\n",szFollowWayName,nDistance,szArriveWayName);
			if(m_pWayList[i]->m_iDirection == 2)
				szInfo.Format("���š�%s��·ǰ��%6ld���� ��ת ���%s��·\n",szFollowWayName,nDistance,szArriveWayName);
			if(m_pWayList[i]->m_iDirection == 3)
				szInfo.Format("���š�%s��·ǰ��%6ld���� ��ת ���%s��·\n",szFollowWayName,nDistance,szArriveWayName);
			
			m_pWaysInfo.Add(szInfo);
		}
		
		//���ŵ�·��
		CString	szFollowWayName;
		long	nDistance;

		szFollowWayName	= m_pWayList[i]->m_chName;
		nDistance		= m_pWayList[i]->m_nWeight;
		
		CString	szInfo;

		szInfo.Format("���š�%s��·ǰ��%6ld���׵���Ŀ�ĵ�\n",szFollowWayName,nDistance/10);
		TRACE(szInfo);

		m_pWaysInfo.Add(szInfo);

		szInfo.Format("��·�̣�%6ld ����\n", nTotalDistance + nDistance);
		TRACE(szInfo);

		AfxMessageBox(szInfo);
	}
}

//���·�����������1��ʼ�����������⡿
bool CAnalyse_RouteAnalyse::BestRoute(int iMode,long nSP, long nEP)
{
	if(nSP == nEP)
	{
		MessageBox(NULL,_T("ͬһ�ӵ�,��·����û������!!!"), _T("��ʾ��Ϣ"), MB_ICONEXCLAMATION  | MB_OK);
		return	false;
	}

	DWORD dwSearchTime;
	DWORD dwAllSearchTime;
	
	dwSearchTime	= 0;

	DWORD dwAllStartTime = GetTickCount();

	//�������
	CreateArray(iMode);
	
	int i;
	//�������p
	long	*p;
	p	= new	long[m_nMaxNodeNum+1];		
	for(i=0;i<m_nMaxNodeNum+1;i++)
	{
		p[i]	= -1;
	}

	//�ѱ�ǵ���q
	long	*q;
	long	iQNum;
	q	= new	long[m_nMaxNodeNum+1];		
	for(i=0;i<m_nMaxNodeNum+1;i++)
	{
		q[i]	= 0;
	}
	iQNum	= 0;

	//��ʼ��
	double		dmin;
	long		di,dj;
	long		w;
	long		ri,rj;
	long		row;

	//�൱�ڵ�һ����d(s)=0
	p[nSP]			= 0;
	m_dDistanceMin	= 0.0;
	row				= nSP;

	//����1����¼�ѱ�ǵ�����
	//q[iQNum]		= nSP;
	//iQNum++;

	//����2��
	m_pUnUsedNode.Add(nSP);
	
	//���·������������
	do
	{
		DWORD dwStartTime = GetTickCount();

		//���ѱ�ǵ����У�������Ԫ�ص���СֵdMin������¼��СԪ�ص�di��dj
		//dmin	= SearchMinFromRow(di,dj,q,iQNum);
		//dmin	= SearchMinFromRow(di,dj,p);
		dmin	= SearchMinFromRow(di,dj);

		DWORD dwFinishTime = GetTickCount();

		dwSearchTime	= dwSearchTime + (dwFinishTime - dwStartTime);

		if(dmin==-1)
		{
			MessageBox(NULL,_T("���������·��!"), _T("��ʾ��Ϣ"), MB_ICONEXCLAMATION  | MB_OK);
			
			delete	[]p;
			
			ReleaseRoute();

			return	false;	
		}

		m_dDistanceMin	= dmin;
		w				= m_pJ[di*(m_nMaxLinkLineNum+1)+dj];
		
		if(p[w]==-1)
		{
			p[w]= di;	//���������������������һ��

			//����1����¼�ѱ�ǵ�����
			//q[iQNum]		= w;
			//iQNum++;

			//����2��
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

			//��������
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

		m_pDJ[di*(m_nMaxLinkLineNum+1)+dj]	= -1;	//�Ѿ�������
		m_pDJ[ri*(m_nMaxLinkLineNum+1)+rj]	= -1;	//�Ѿ�������
	}while(p[nEP]==-1);

	//
	m_pUnUsedNode.RemoveAll();
	m_pUsedNode.RemoveAll();

	DWORD dwAllFinishTime = GetTickCount();
	dwAllSearchTime		= dwAllFinishTime - dwAllStartTime;

	CString szInfo;
	szInfo.Format(_T("·������ʱ�� ��%d ms %d ms\n"), (int)dwAllSearchTime,(int)dwSearchTime);

	TRACE(szInfo);

	//AfxMessageBox(szInfo);

	//���ݱ��pѰǰ�㣬������·��������
	GetWay(m_nNodesNumInWay,nSP,nEP,p);

	//ɾ���м����
	delete	[]p;

	delete	[]q;
	
	//ɾ��
	ReleaseRoute();

	return	true;
}

//��ȡ����
double CAnalyse_RouteAnalyse::GetDistance()
{
	return	m_dDistanceMin;
}

//�Һ������������Ŀ��㣬���ǿ����ҵ���
long CAnalyse_RouteAnalyse::GetPointNo(double &xx, double &yy)
{
	if(m_pWorkSpace == NULL)		return	-1;

	
	return	m_pWorkSpace->GetPointNo(xx,yy);
}

//�ͷ����·���������м���Ϣ
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

//�ͷ�����
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

//����ӳ��
void CAnalyse_RouteAnalyse::SetCoordMapping(double dMapXA, double dMapXB, double dMapYA, double dMapYB)
{
	m_dMapXA	= dMapXA;
	m_dMapXB	= dMapXB;

	m_dMapYA	= dMapYA;
	m_dMapYB	= dMapYB;
}

//������������
void CAnalyse_RouteAnalyse::DrawNetwork(CDC *pDC)
{
	if(m_pWorkSpace == NULL)	return;
		
	m_pWorkSpace->SetCoordMapping(m_dMapXA,m_dMapXB,m_dMapYA,m_dMapYB);
	m_pWorkSpace->SetShowExt(m_dShowLeft,m_dShowRight,m_dShowBottom,m_dShowTop);

	m_pWorkSpace->OnDraw(pDC);
}

//�������·��
void CAnalyse_RouteAnalyse::DrawBestRoute(CDC *pDC)
{
	if(m_pWayList.GetSize() == NULL)	return;

	HPEN	hOldPen,hNewPen;

	hNewPen		= CreatePen(PS_SOLID,2,RGB(255,0,0));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);

	POINT		*pPoints;
	int			nPointNum;
	
	//////////////////////////////////////////////////////////
	//������
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
	//���ƽڵ�
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


//���ӱؾ����
bool CAnalyse_RouteAnalyse::AddPassNode(CPoint ptPoint)
{
	double	dX,dY;

	dX	= (ptPoint.x - m_dMapXB)/m_dMapXA;
	dY	= (ptPoint.y - m_dMapYB)/m_dMapYA;

	return	AddPassNode(dX,dY);
}

//���ӱؾ����
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

//���Ʊؾ����
void CAnalyse_RouteAnalyse::DrawPassNode(CDC *pDC)
{
	if(m_pPassNodes.GetSize() == 0)
	{
		//TRACE("\nû��[�ؾ����]�ɹ�����!\n");

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

//�ͷűؾ����
void CAnalyse_RouteAnalyse::ReleasePassNode()
{
	m_pPassNodes.RemoveAll();
}

// ���ӱܿ����
bool CAnalyse_RouteAnalyse::AddDisNode(CPoint ptPoint)
{
	double	dX,dY;

	dX	= (ptPoint.x - m_dMapXB)/m_dMapXA;
	dY	= (ptPoint.y - m_dMapYB)/m_dMapYA;

	return	AddDisNode(dX,dY);
}

// ���ӱܿ����
bool CAnalyse_RouteAnalyse::AddDisNode(double dX,double dY)
{
	long	nPointNo;

	nPointNo	= GetPointNo(dX,dY);

	for(int i=0;i<m_pDisNodes.GetSize();i++)
	{
		if(m_pDisNodes[i].nPointNo == nPointNo)
		{
			//��ʾ��Ϣ�����ڽ��
			return	false;
		}
	}

	for(int i=0;i<m_pPassNodes.GetSize();i++)
	{
		if(m_pPassNodes[i].nPointNo == nPointNo)
		{
			//��ʾ��Ϣ�����ڽ��
			return	false;
		}
	}

	SRoute_Nodes	pNodes;

	pNodes.nPointNo	= nPointNo;
	pNodes.dCoordX	= dX;
	pNodes.dCoordY	= dY;

	m_pDisNodes.Add(pNodes);

	//////////////////////////////////////////////
	//�޸������е����˹�ϵ
	if(m_pWorkSpace)
		m_pWorkSpace->DisNode(nPointNo);
	//////////////////////////////////////////////

	return	true;	
}

// ���Ʊܿ����
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

// ɾ���ܿ����
void CAnalyse_RouteAnalyse::ReleaseDisNode()
{
	for(int i=0;i<m_pDisNodes.GetSize();i++)
	{
		m_pWorkSpace->UnDisNode(m_pDisNodes[i].nPointNo);
	}

	m_pDisNodes.RemoveAll();
}

// ���ӶϿ�·��
bool CAnalyse_RouteAnalyse::AddDisWay(CPoint ptPoint)
{
	double	dX,dY;

	dX	= (ptPoint.x - m_dMapXB)/m_dMapXA;
	dY	= (ptPoint.y - m_dMapYB)/m_dMapYA;

	return	AddDisWay(dX,dY);
}

// ���ӶϿ�·��
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
			//���ӶϿ��ĵ�·
			m_pDisWayList.Add(pWay);
			//////////////////////////////////////////////

			//////////////////////////////////////////////
			//��·
			if(m_pWorkSpace)
				m_pWorkSpace->DisWay(pWay->m_nFirstNode,pWay->m_nLastNode);
			//////////////////////////////////////////////

			break;
		}
	}

	return	true;
}

// ���ƶϿ�·��
void CAnalyse_RouteAnalyse::DrawDisWay(CDC *pDC)
{
	if(m_pDisWayList.GetSize() == NULL)	return;

	HPEN	hOldPen,hNewPen;

	hNewPen		= CreatePen(PS_SOLID,2,RGB(255,0,0));
	hOldPen		= (HPEN)SelectObject(pDC->m_hDC,hNewPen);

	POINT		*pPoints;
	int			nPointNum;
	
	//////////////////////////////////////////////////////////
	//������
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

//ɾ���Ͽ�·������
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

//���·��
bool CAnalyse_RouteAnalyse::BestRoute(int iMode)
{
	if(m_pPassNodes.GetSize()<=1)	
	{
		//��ʾ��Ϣ:��������
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

//����
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

//��ȡ��·��������
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

//��ȡ���·��������
// ��ȡĳһ��·���ж�����·��ɵģ�
int CAnalyse_RouteAnalyse::GetWayCount()
{
	return	m_pWayList.GetSize();
}

// ��ȡĳһ��·����Ϣ
// int iRouteID:			��·��ţ�
// char* chRouteType��		��·���ͣ�
// char* chRouteName��		��·���ƣ�
// int& iPointNum��			����
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

//��ȡ����ĵ�·����
// int iRouteID:			��·��ţ�
// double* dX, double* dY	��·����
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
