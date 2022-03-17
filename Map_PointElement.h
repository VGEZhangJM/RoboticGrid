// Map_PointElement.h: interface for the CMap_PointElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_POINTELEMENT_H__138C370E_6B94_4798_A5B7_A9C26E45681B__INCLUDED_)
#define AFX_MAP_POINTELEMENT_H__138C370E_6B94_4798_A5B7_A9C26E45681B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_PointElement  
{
public:
	CMap_PointElement();
	virtual ~CMap_PointElement();

protected:
	int m_iID;
	//����
	int m_iSubType;
	//����
	int m_iMainType;
	
	//
	int						m_iPointNum;
	SMap_DPointCoord*		m_pPointList;
	
	//��һҪ��
	CMap_PointElement*		m_pNext;
};

#endif // !defined(AFX_MAP_POINTELEMENT_H__138C370E_6B94_4798_A5B7_A9C26E45681B__INCLUDED_)
