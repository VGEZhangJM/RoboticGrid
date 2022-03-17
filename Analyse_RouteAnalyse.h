// Analyse_RouteAnalyse.h: interface for the CAnalyse_RouteAnalyse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSE_ROUTEANALYSE_H__B355AF94_878F_453E_8D67_E1D52575A14F__INCLUDED_)
#define AFX_ANALYSE_ROUTEANALYSE_H__B355AF94_878F_453E_8D67_E1D52575A14F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Analyse_Way.h"
#include "PublicFunction.h"
#include "Analyse_WorkSpace.h"

class CAnalyse_RouteAnalyse : public CObject  
{
public:
	//
	void			SetShowExt(double dLeft,double dRight,double dBottom,double dTop);
	//
	void			SetWorkSpace(CAnalyse_WorkSpace *pWorkSpace);

	//删除避开路段
	void			ReleaseDisWay();
	// 绘制避开路段
	void			DrawDisWay(CDC *pDC);
	// 增加避开路段
	bool			AddDisWay(CPoint ptPoint);
	// 增加避开路段
	bool			AddDisWay(double dX,double dY);

	// 删除避开结点
	void			ReleaseDisNode();
	// 绘制避开结点
	void			DrawDisNode(CDC *pDC);
	// 增加避开结点
	bool			AddDisNode(CPoint ptPoint);
	// 增加避开结点
	bool			AddDisNode(double dX,double dY);

	// 删除必经结点
	void			ReleasePassNode();
	// 绘制必经结点
	void			DrawPassNode(CDC *pDC);
	// 增加必经结点
	bool			AddPassNode(CPoint ptPoint);
	// 增加必经结点
	bool			AddPassNode(double dX,double dY);

	//
	void			ReleaseWayInfo();

	// 删除最短路径
	void			ReleaseWay();

	//绘制最短路径
	void			DrawBestRoute(CDC *pDC);
	//绘制道路拓扑
	void			DrawNetwork(CDC* pDC);

	//坐标映射
	void			SetCoordMapping(double dMapXA,double dMapXB,double dMapYA,double dMapYB);
	long			GetPointNo(double &xx, double &yy);
	double			GetDistance();

	bool			BestRoute(int iMode);
	bool			BestRoute(int iMode,long nSP, long nEP);

	//获取最短路径的数据
	// 获取某一道路是有多少条路组成的？
	int				GetWayCount();
	
	// 获取某一道路的信息
	// int iRouteID:			道路编号；
	// char* chRouteType：		道路类型；
	// char* chRouteName：		道路名称；
	// int& iPointNum：			点数
	bool			GetWayInformation(int iRouteID, char* chRouteType, char* chRouteName, int& iPointNum);
	
	//获取具体的道路坐标
	// int iRouteID:			道路编号；
	// double* dX, double* dY	道路坐标
	bool			GetWayCoord(int iRouteID, double* dX, double* dY);
	
	CAnalyse_RouteAnalyse();
	virtual ~CAnalyse_RouteAnalyse();

protected:
	void				GetWay(long &nWayNum,long nSP,long nEP,long *pCode);

	void				ReleaseRoute();
	
	//创建权值矩阵
	void				CreateArray(int iMode);

	double				SearchMinFromRow(long &di,long &dj,long *p);

	double				SearchMinFromRow(long &di,long &dj,long *q,long iNum);

	double				SearchMinFromRow(long &di,long &dj);

	void				DrawBitmapPoint(CDC *pDC,long iCX,long iCY,UINT nIDResource);

	SMap_DPointCoord*	GetLineFeature(long nFirstNode, long nLastNode, long& nRuteType, long& nPointNum,long &nWeight,char *chName);

public:

	//道路拓扑数据中总的结点数
	long								m_nMaxNodeNum;
	//道路拓扑数据中最大的相关弧段数
	long								m_nMaxLinkLineNum;

	//道路拓扑数据
	CAnalyse_WorkSpace					*m_pWorkSpace;
		
	//最短路径	
	CArray<CAnalyse_Way*,CAnalyse_Way*>	m_pWayList;

	//断开的路段
	CArray<CAnalyse_Way*,CAnalyse_Way*>	m_pDisWayList;

	//
	CArray<CString,CString>				m_pWaysInfo;

	//判断矩阵指针
	double								*m_pDJ;		
	//邻接结点矩阵指针	
	long								*m_pJ;		
	
	//最短路径上的结点号
	long								*m_pNodesInWay;	
	//最短路径上的结点数
	long								m_nNodesNumInWay;

	//最短路径
	double								m_dDistanceMin;

	//显示系数
	double								m_dMapXA,m_dMapXB;
	double								m_dMapYA,m_dMapYB;
	
	//
	double								m_dShowLeft,m_dShowRight;
	double								m_dShowBottom,m_dShowTop;
		
	//必经结点
	CArray<SRoute_Nodes,SRoute_Nodes>	m_pPassNodes;
	//避开结点
	CArray<SRoute_Nodes,SRoute_Nodes>	m_pDisNodes;
	//
	CPublicFunction						m_pFunc;
	
	//有用的节点，需要从中选择更短的节点的
	CArray<long,long>					m_pUnUsedNode;

	//已经无用的节点，是需要从m_pUnUsedNode中删除的
	CArray<long,long>					m_pUsedNode;
};

#endif // !defined(AFX_ANALYSE_ROUTEANALYSE_H__B355AF94_878F_453E_8D67_E1D52575A14F__INCLUDED_)
