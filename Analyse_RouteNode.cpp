// Analyse_RouteNode.cpp: implementation of the CAnalyse_RouteNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Analyse_RouteNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnalyse_RouteNode::CAnalyse_RouteNode()
{
	m_nPointNo			= 0;		//序号
	m_dCoordX			= 0;		//坐标
	m_dCoordY			= 0;

	m_nLinkLineNum		= 0;		//相关边数
	//
	m_pNodeLink			= NULL;

	//m_pLinkLineNo.RemoveAll();
	//m_pLinkFirstNode.RemoveAll();
	//m_pLinkLastNode.RemoveAll();
	//m_pLinkFileAddress.RemoveAll();
	//m_pLinkWeight.RemoveAll();
	//m_pLinkTime.RemoveAll();
	

	m_pNext				= NULL;
}

CAnalyse_RouteNode::~CAnalyse_RouteNode()
{
	Release();
}

bool CAnalyse_RouteNode::Load(FILE *fp)
{
	if(fp == NULL)	return	false;

	//点号
	fread(&m_nPointNo,sizeof(long),1,fp);

	m_nPointNo	= m_nPointNo;
		
	//坐标
	//long	nX,nY;
// 	long	nCoord[2];
// 	fread(nCoord,sizeof(long),2,fp);

	fread(&m_dCoordX,sizeof(double),1,fp);
	fread(&m_dCoordY,sizeof(double),1,fp);

// 	m_dCoordX	= nCoord[0]/360000.0 + m_dMapLeft;
// 	m_dCoordY	= nCoord[1]/360000.0 + m_dMapBottom;
	
	//相关弧段数目
	//fread(&m_nLinkLineNum,sizeof(long),1,fp);
	fread(&m_nLinkLineNum,sizeof(BYTE),1,fp);

	if(m_nLinkLineNum > 0)
	{
		m_pNodeLink	= new	SRoute_NodeLink[m_nLinkLineNum];

		fread(m_pNodeLink,sizeof(SRoute_NodeLink),m_nLinkLineNum,fp);

		for(int i=0;i<m_nLinkLineNum;i++)
		{
			m_pNodeLink[i].m_pLinkFirstNode	= m_pNodeLink[i].m_pLinkFirstNode;
			m_pNodeLink[i].m_pLinkLastNode	= m_pNodeLink[i].m_pLinkLastNode;
		}
		
		/*
		long	*nValue;
		nValue	= new	long[5*m_nLinkLineNum];

		fread(nValue,sizeof(long),5*m_nLinkLineNum,fp);

		for(int i=0;i<m_nLinkLineNum;i++)
		{
			//long	nLinkLineNo;
			long	nLinkFirstNode,nLinkLastNode,nLinkFileAddress;
			long	nLinkWeight,nLinkTime;

			nLinkFirstNode		= nValue[i*5+0] + m_nMaxNodeNum;
			nLinkLastNode		= nValue[i*5+1] + m_nMaxNodeNum;
			nLinkFileAddress	= nValue[i*5+2];
			nLinkWeight			= nValue[i*5+3];
			nLinkTime			= nValue[i*5+4];
			
			//邻接线号
			//fread(&nLinkLineNo,sizeof(long),1,fp);

			//邻接线首结点
			//fread(&nLinkFirstNode,sizeof(long),1,fp);
			//nLinkFirstNode	= nLinkFirstNode + m_nMaxNodeNum;

			//邻接线末结点
			//fread(&nLinkLastNode,sizeof(long),1,fp);
			//nLinkLastNode	= nLinkLastNode + m_nMaxNodeNum;

			//邻接线在文件中的地址
			//fread(&nLinkFileAddress,sizeof(long),1,fp);
			//距离权重
			//fread(&nLinkWeight,sizeof(long),1,fp);
			//时间权重
			//fread(&nLinkTime,sizeof(long),1,fp);

			//m_pLinkLineNo.Add(nLinkLineNo);
			m_pLinkFirstNode.Add(nLinkFirstNode);
			m_pLinkLastNode.Add(nLinkLastNode);
			m_pLinkFileAddress.Add(nLinkFileAddress);
			m_pLinkWeight.Add(nLinkWeight);
			m_pLinkTime.Add(nLinkTime);
		}

		delete	[]nValue;
		*/
	}

	return	true;
}

void CAnalyse_RouteNode::Release()
{
	//m_pLinkLineNo.RemoveAll();
	//m_pLinkFirstNode.RemoveAll();
	//m_pLinkLastNode.RemoveAll();
	//m_pLinkFileAddress.RemoveAll();
	//m_pLinkWeight.RemoveAll();
	//m_pLinkTime.RemoveAll();

	m_nPointNo			= 0;		//序号
	m_dCoordX			= 0;		//坐标
	m_dCoordY			= 0;

	m_nLinkLineNum		= 0;		//相关边数
	if(m_pNodeLink != NULL)
	{
		delete	[]m_pNodeLink;
		m_pNodeLink		= NULL;
	}
}

//断路
void CAnalyse_RouteNode::DisWay(long nFirstNode,long nLastNode)
{
	for(int i=0;i<m_nLinkLineNum;i++)
	{
		if((m_pNodeLink[i].m_pLinkFirstNode==nFirstNode && m_pNodeLink[i].m_pLinkLastNode==nLastNode) || 
			(m_pNodeLink[i].m_pLinkFirstNode==nLastNode && m_pNodeLink[i].m_pLinkLastNode==nFirstNode))
		{
			if(m_pNodeLink[i].m_pLinkWeight!=-1 && m_pNodeLink[i].m_pLinkWeight>0)
			{
				m_pNodeLink[i].m_pLinkWeight	= -m_pNodeLink[i].m_pLinkWeight;
			}
		}
		
		/*
		if((m_pLinkFirstNode[i]==nFirstNode&&m_pLinkLastNode[i]==nLastNode) || (m_pLinkFirstNode[i]==nLastNode&&m_pLinkLastNode[i]==nFirstNode))
		{
			if(m_pLinkWeight[i]!=-1 && m_pLinkWeight[i]>0)
			{
				m_pLinkWeight[i]	= -m_pLinkWeight[i];
			}

			if(m_pLinkTime[i]!=-1 && m_pLinkTime[i]>0)
			{
				m_pLinkTime[i]		= -m_pLinkTime[i];
			}
		}
		*/
	}
}

//恢复断路
void CAnalyse_RouteNode::UnDisWay(long nFirstNode,long nLastNode)
{
	for(int i=0;i<m_nLinkLineNum;i++)
	{
		if((m_pNodeLink[i].m_pLinkFirstNode==nFirstNode && m_pNodeLink[i].m_pLinkLastNode==nLastNode) || 
			(m_pNodeLink[i].m_pLinkFirstNode==nLastNode && m_pNodeLink[i].m_pLinkLastNode==nFirstNode))
		{
			if(m_pNodeLink[i].m_pLinkWeight!=-1 && m_pNodeLink[i].m_pLinkWeight<0)
			{
				m_pNodeLink[i].m_pLinkWeight	= -m_pNodeLink[i].m_pLinkWeight;
			}
		}

		/*
		if((m_pLinkFirstNode[i]==nFirstNode&&m_pLinkLastNode[i]==nLastNode) || (m_pLinkFirstNode[i]==nLastNode&&m_pLinkLastNode[i]==nFirstNode))
		{
			if(m_pLinkWeight[i]!=-1 && m_pLinkWeight[i]<0)
			{
				m_pLinkWeight[i]	= -m_pLinkWeight[i];
			}

			if(m_pLinkTime[i]!=-1 && m_pLinkTime[i]<0)
			{
				m_pLinkTime[i]		= -m_pLinkTime[i];
			}
		}
		*/
	}
}

//断接点
void CAnalyse_RouteNode::DisNode(long nNode)
{
	for(int i=0;i<m_nLinkLineNum;i++)
	{
		if(m_pNodeLink[i].m_pLinkFirstNode==nNode || m_pNodeLink[i].m_pLinkLastNode==nNode)
		{
			if(m_pNodeLink[i].m_pLinkWeight!=-1 && m_pNodeLink[i].m_pLinkWeight>0)
			{
				m_pNodeLink[i].m_pLinkWeight	= -m_pNodeLink[i].m_pLinkWeight;
			}
		}

		/*
		if(m_pLinkFirstNode[i]==nNode || m_pLinkLastNode[i]==nNode)
		{
			if(m_pLinkWeight[i]!=-1 && m_pLinkWeight[i]>0)
			{
				m_pLinkWeight[i]	= -m_pLinkWeight[i];
			}

			if(m_pLinkTime[i]!=-1 && m_pLinkTime[i]>0)
			{
				m_pLinkTime[i]		= -m_pLinkTime[i];
			}
		}
		*/
	}
}

//恢复断接点
void CAnalyse_RouteNode::UnDisNode(long nNode)
{
	for(int i=0;i<m_nLinkLineNum;i++)
	{
		if(m_pNodeLink[i].m_pLinkFirstNode==nNode || m_pNodeLink[i].m_pLinkLastNode==nNode)
		{
			if(m_pNodeLink[i].m_pLinkWeight!=-1 && m_pNodeLink[i].m_pLinkWeight<0)
			{
				m_pNodeLink[i].m_pLinkWeight	= -m_pNodeLink[i].m_pLinkWeight;
			}
		}

		/*
		if(m_pLinkFirstNode[i]==nNode || m_pLinkLastNode[i]==nNode)
		{
			if(m_pLinkWeight[i]!=-1 && m_pLinkWeight[i]<0)
			{
				m_pLinkWeight[i]	= -m_pLinkWeight[i];
			}

			if(m_pLinkTime[i]!=-1 && m_pLinkTime[i]<0)
			{
				m_pLinkTime[i]		= -m_pLinkTime[i];
			}
		}
		*/
	}
}

