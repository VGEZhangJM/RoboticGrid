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

	//ɾ���ܿ�·��
	void			ReleaseDisWay();
	// ���Ʊܿ�·��
	void			DrawDisWay(CDC *pDC);
	// ���ӱܿ�·��
	bool			AddDisWay(CPoint ptPoint);
	// ���ӱܿ�·��
	bool			AddDisWay(double dX,double dY);

	// ɾ���ܿ����
	void			ReleaseDisNode();
	// ���Ʊܿ����
	void			DrawDisNode(CDC *pDC);
	// ���ӱܿ����
	bool			AddDisNode(CPoint ptPoint);
	// ���ӱܿ����
	bool			AddDisNode(double dX,double dY);

	// ɾ���ؾ����
	void			ReleasePassNode();
	// ���Ʊؾ����
	void			DrawPassNode(CDC *pDC);
	// ���ӱؾ����
	bool			AddPassNode(CPoint ptPoint);
	// ���ӱؾ����
	bool			AddPassNode(double dX,double dY);

	//
	void			ReleaseWayInfo();

	// ɾ�����·��
	void			ReleaseWay();

	//�������·��
	void			DrawBestRoute(CDC *pDC);
	//���Ƶ�·����
	void			DrawNetwork(CDC* pDC);

	//����ӳ��
	void			SetCoordMapping(double dMapXA,double dMapXB,double dMapYA,double dMapYB);
	long			GetPointNo(double &xx, double &yy);
	double			GetDistance();

	bool			BestRoute(int iMode);
	bool			BestRoute(int iMode,long nSP, long nEP);

	//��ȡ���·��������
	// ��ȡĳһ��·���ж�����·��ɵģ�
	int				GetWayCount();
	
	// ��ȡĳһ��·����Ϣ
	// int iRouteID:			��·��ţ�
	// char* chRouteType��		��·���ͣ�
	// char* chRouteName��		��·���ƣ�
	// int& iPointNum��			����
	bool			GetWayInformation(int iRouteID, char* chRouteType, char* chRouteName, int& iPointNum);
	
	//��ȡ����ĵ�·����
	// int iRouteID:			��·��ţ�
	// double* dX, double* dY	��·����
	bool			GetWayCoord(int iRouteID, double* dX, double* dY);
	
	CAnalyse_RouteAnalyse();
	virtual ~CAnalyse_RouteAnalyse();

protected:
	void				GetWay(long &nWayNum,long nSP,long nEP,long *pCode);

	void				ReleaseRoute();
	
	//����Ȩֵ����
	void				CreateArray(int iMode);

	double				SearchMinFromRow(long &di,long &dj,long *p);

	double				SearchMinFromRow(long &di,long &dj,long *q,long iNum);

	double				SearchMinFromRow(long &di,long &dj);

	void				DrawBitmapPoint(CDC *pDC,long iCX,long iCY,UINT nIDResource);

	SMap_DPointCoord*	GetLineFeature(long nFirstNode, long nLastNode, long& nRuteType, long& nPointNum,long &nWeight,char *chName);

public:

	//��·�����������ܵĽ����
	long								m_nMaxNodeNum;
	//��·����������������ػ�����
	long								m_nMaxLinkLineNum;

	//��·��������
	CAnalyse_WorkSpace					*m_pWorkSpace;
		
	//���·��	
	CArray<CAnalyse_Way*,CAnalyse_Way*>	m_pWayList;

	//�Ͽ���·��
	CArray<CAnalyse_Way*,CAnalyse_Way*>	m_pDisWayList;

	//
	CArray<CString,CString>				m_pWaysInfo;

	//�жϾ���ָ��
	double								*m_pDJ;		
	//�ڽӽ�����ָ��	
	long								*m_pJ;		
	
	//���·���ϵĽ���
	long								*m_pNodesInWay;	
	//���·���ϵĽ����
	long								m_nNodesNumInWay;

	//���·��
	double								m_dDistanceMin;

	//��ʾϵ��
	double								m_dMapXA,m_dMapXB;
	double								m_dMapYA,m_dMapYB;
	
	//
	double								m_dShowLeft,m_dShowRight;
	double								m_dShowBottom,m_dShowTop;
		
	//�ؾ����
	CArray<SRoute_Nodes,SRoute_Nodes>	m_pPassNodes;
	//�ܿ����
	CArray<SRoute_Nodes,SRoute_Nodes>	m_pDisNodes;
	//
	CPublicFunction						m_pFunc;
	
	//���õĽڵ㣬��Ҫ����ѡ����̵Ľڵ��
	CArray<long,long>					m_pUnUsedNode;

	//�Ѿ����õĽڵ㣬����Ҫ��m_pUnUsedNode��ɾ����
	CArray<long,long>					m_pUsedNode;
};

#endif // !defined(AFX_ANALYSE_ROUTEANALYSE_H__B355AF94_878F_453E_8D67_E1D52575A14F__INCLUDED_)
