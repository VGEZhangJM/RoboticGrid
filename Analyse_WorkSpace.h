// Analyse_WorkSpace.h: interface for the CAnalyse_WorkSpace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSE_WORKSPACE_H__9028BF7A_58E1_4878_A909_0DAF3F5A4EF1__INCLUDED_)
#define AFX_ANALYSE_WORKSPACE_H__9028BF7A_58E1_4878_A909_0DAF3F5A4EF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Analyse_RouteNode.h"

//��·���ݹ�����
class CAnalyse_WorkSpace
{
public:
	CAnalyse_WorkSpace();
	virtual ~CAnalyse_WorkSpace();

public:
	//��·
	void					DisWay(long nFirstNode,long nLastNode);
	//�ָ���·
	void					UnDisWay(long nFirstNode,long nLastNode);

	//�ܿ����
	void					DisNode(long nNode);
	//�ָ��ܿ����
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
	//��ȡ�����Ŀ
	long					GetNodeNum();

	//�ͷŵ�·��������
	void					Release();

	//���ص�·��������
	bool					Load(CString szPathName);

	//
	void					SetNodesNum(int iNodeNum);

	SMap_DPointCoord*		GetLineFeature(long nFirstNode, long nLastNode, long& nRuteType, long& nPointNum,long &nWeight,char *chName);

public:
	//��·�������
	CAnalyse_RouteNode		*m_pRouteNodeHead;
	CAnalyse_RouteNode		*m_pRouteNodeLast;

	CString					m_szRutPathName;

	//�����Ŀ
	long					m_nNodesNum;

	//������ӻ�����Ŀ
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
