// Map_PolygonElement.h: interface for the CMap_PolygonElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_POLYGONELEMENT_H__29819F9A_1634_49D2_9C74_FD15F92E7073__INCLUDED_)
#define AFX_MAP_POLYGONELEMENT_H__29819F9A_1634_49D2_9C74_FD15F92E7073__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_PolygonElement  
{
public:
	//
	bool	Read(FILE *fp);
	void	Draw(CDC* pDC);

	
	//
	void	SetID(int iID);
	int		GetID();

	void	SetMainType(int iMainType);
	int		GetMainType();

	void	SetSubType(int iSubType);
	int		GetSubType();

	void	SetPointNum(int iPointNum);
	int		GetPointNum();

	SMap_DPointCoord*	GetPointList();
	
	void	GetElementExt(double& dLeft, double& dRight, double& dBottom,double& dTop);
	//
	void	SetCoordMapping(double dXA,double dXB,double dYA,double dYB);

	double	GetArea();

	CMap_PolygonElement();
	virtual ~CMap_PolygonElement();

protected:
	int m_iID;
	//子类
	int m_iSubType;
	//主类
	int m_iMainType;
	
	//
	int						m_iPointNum;
	SMap_DPointCoord*		m_pPointList;

	double	m_dLeft,m_dRight;
	double	m_dBottom,m_dTop;

	//缩放系数
	double				m_dMapXA,m_dMapXB;
	double				m_dMapYA,m_dMapYB;


public:
	//下一要素
	CMap_PolygonElement*	m_pNext;
};

#endif // !defined(AFX_MAP_POLYGONELEMENT_H__29819F9A_1634_49D2_9C74_FD15F92E7073__INCLUDED_)
