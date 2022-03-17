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

	//��¡
	bool		Clone(CAnalyse_Way* pWay);
	//
	bool		GetLine(double dX,double dY,double dMapXA);

public:
	//��ĩ���
	long		m_nFirstNode;
	long		m_nLastNode;

	//��������
	long				m_nPointNum;
	SMap_DPointCoord	*m_pPointCoord;
	
	//Ȩֵ
	long		m_nWeight;
	//��·����
	long		m_nRouteType;
	//����
	char		m_chName[30];
	//����һ·�ε�ת���ϵ: 1��ֱ�У�2����ת��3����ת ��0������Ŀ�ĵ�
	int			m_iDirection;
};

#endif // !defined(AFX_ANALYSE_WAY_H__EA786AD8_94FD_44E8_B9C3_FC9259BE7523__INCLUDED_)
