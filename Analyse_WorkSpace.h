// Analyse_WorkSpace.h: interface for the CAnalyse_WorkSpace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSE_WORKSPACE_H__9028BF7A_58E1_4878_A909_0DAF3F5A4EF1__INCLUDED_)
#define AFX_ANALYSE_WORKSPACE_H__9028BF7A_58E1_4878_A909_0DAF3F5A4EF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Analyse_RouteNode.h"

//道路数据工作区
class CAnalyse_WorkSpace
{
public:
	CAnalyse_WorkSpace();
	virtual ~CAnalyse_WorkSpace();

public:
	//断路
	void					DisWay(long nFirstNode,long nLastNode);
	//恢复断路
	void					UnDisWay(long nFirstNode,long nLastNode);

	//避开结点
	void					DisNode(long nNode);
	//恢复避开结点
	void					UnDisNode(long nNode);

	//
	void					SetShowExt(double dLeft,double dRight,double dBottom,double dTop);
	//
	void					SetMapExt(double dLeft,double dRight,double dBottom,double dTop);
	//
	void					SetCoordMapping(double dXA,double dXB,double dYA,double dYB);
	//
	void					OnDraw(CDC *pDC);
	//	
	long					GetPointNo(double &xx, double &yy);
	//获取结点数目
	long					GetNodeNum();

	//释放道路拓扑数据
	void					Release();

	//加载道路拓扑数据
	bool					Load(CString szPathName);

	//
	void					SetNodesNum(int iNodeNum);

	SMap_DPointCoord*		GetLineFeature(long nFirstNode, long nLastNode, long& nRuteType, long& nPointNum,long &nWeight,char *chName);

public:
	//道路结点数据
	CAnalyse_RouteNode		*m_pRouteNodeHead;
	CAnalyse_RouteNode		*m_pRouteNodeLast;

	CString					m_szRutPathName;

	//结点数目
	long					m_nNodesNum;

	//最大链接弧段数目
	long					m_nMaxLinkLineNum;
	
	//
	double					m_dMapLeft,m_dMapRight;
	double					m_dMapBottom,m_dMapTop;

	//
	double					m_dShowLeft,m_dShowRight;
	double					m_dShowBottom,m_dShowTop;
	
	//
	double					m_dMapXA,m_dMapXB,m_dMapYA,m_dMapYB;
};

#endif // !defined(AFX_ANALYSE_WORKSPACE_H__9028BF7A_58E1_4878_A909_0DAF3F5A4EF1__INCLUDED_)
