// Analyse_RouteNode.h: interface for the CAnalyse_RouteNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSE_ROUTENODE_H__7E5DDC66_8660_4A4B_9705_0CA267F0609A__INCLUDED_)
#define AFX_ANALYSE_ROUTENODE_H__7E5DDC66_8660_4A4B_9705_0CA267F0609A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//结点数据
class CAnalyse_RouteNode
{
public:
	CAnalyse_RouteNode();
	virtual ~CAnalyse_RouteNode();
	
public:
	//
	void					Release();
	//
	bool					Load(FILE *fp);

	//断路
	void					DisWay(long nFirstNode,long nLastNode);
	//恢复断路
	void					UnDisWay(long nFirstNode,long nLastNode);
	
	//避开结点
	void					DisNode(long nNode);
	//恢复避开结点
	void					UnDisNode(long nNode);

public:
	//序号
	long					m_nPointNo;
	//坐标
	double					m_dMapLeft;
	double					m_dMapBottom;

	double					m_dCoordX;			
	double					m_dCoordY;
	//相关边数
	BYTE					m_nLinkLineNum;	
	
	//相关边的线号
	//CArray<long,long>		m_pLinkLineNo;		

	//相关边的首结点号【首结点和末结点之一应和序号一致】

	//CArray<long,long>		m_pLinkFirstNode;		
	//相关边的末结点号
	//CArray<long,long>		m_pLinkLastNode;

	//文件中的地址
	//CArray<long,long>		m_pLinkFileAddress;	

	//距离的权值
	//CArray<long,long>		m_pLinkWeight;		

	//时间的权值
	//CArray<long,long>		m_pLinkTime;

	//相关边信息，包括首末节点、文件地址、距离权值、时间权值
	SRoute_NodeLink			*m_pNodeLink;
	
	//
	CAnalyse_RouteNode		*m_pNext;
};

#endif // !defined(AFX_ANALYSE_ROUTENODE_H__7E5DDC66_8660_4A4B_9705_0CA267F0609A__INCLUDED_)
