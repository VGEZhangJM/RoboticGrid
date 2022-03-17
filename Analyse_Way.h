// Analyse_Way.h: interface for the CAnalyse_Way class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSE_WAY_H__EA786AD8_94FD_44E8_B9C3_FC9259BE7523__INCLUDED_)
#define AFX_ANALYSE_WAY_H__EA786AD8_94FD_44E8_B9C3_FC9259BE7523__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAnalyse_Way : public CObject  
{
public:
	CAnalyse_Way();
	virtual ~CAnalyse_Way();

	//克隆
	bool		Clone(CAnalyse_Way* pWay);
	//
	bool		GetLine(double dX,double dY,double dMapXA);

public:
	//首末结点
	long		m_nFirstNode;
	long		m_nLastNode;

	//具体坐标
	long				m_nPointNum;
	SMap_DPointCoord	*m_pPointCoord;
	
	//权值
	long		m_nWeight;
	//道路类型
	long		m_nRouteType;
	//名称
	char		m_chName[30];
	//和下一路段的转向关系: 1：直行；2：左转；3：右转 ；0：到达目的地
	int			m_iDirection;
};

#endif // !defined(AFX_ANALYSE_WAY_H__EA786AD8_94FD_44E8_B9C3_FC9259BE7523__INCLUDED_)
