// Map_GridObj.h: interface for the CMap_GridObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_GRIDOBJ_H__5CDFB24D_438E_482E_A467_DE09C0C42940__INCLUDED_)
#define AFX_MAP_GRIDOBJ_H__5CDFB24D_438E_482E_A467_DE09C0C42940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_GridObj  
{
public:
	CMap_GridObj();
	virtual ~CMap_GridObj();

public:
	//ÐòºÅ
	int		m_iI;
	int		m_iJ;
	
	//
	double	m_dSize;
	
	//Ô­µã
	double	m_dOrignX;
	double	m_dOrignY;

	double	m_dCenterX;
	double	m_dCenterY;
	
	//
	int		m_iTerrainType;

	int		m_iSideTypeA;
	int		m_iSideTypeB;
	int		m_iSideTypeC;
	int		m_iSideTypeD;

public:
	void	Init(int iI,int iJ, double dOrignX,double dOrignY, double dHeight);
	void	SetCoordMapping(double dXA,double dXB,double dYA,double dYB);

	void	Draw(CDC* pDC,int iTerrainType);

	void	GetCenter(double& dX,double& dY);
	void	GetExt(double& dLeft,double& dRight,double& dBottom,double& dTop);

	int		GetTerrainType();
	void	SetTerrainType(int iTerrainType);
protected:
	void	DrawRectangle(CDC* pDC, int iLeft, int iRight, int iBottom, int iTop, COLORREF crLine, COLORREF crFull);
	void	DrawLine(CDC* pDC, int iPointNum, POINT* pPoint, COLORREF crLine);

	double	m_dMapXA,m_dMapYA;
	double	m_dMapXB,m_dMapYB;
};

#endif // !defined(AFX_MAP_GRIDOBJ_H__5CDFB24D_438E_482E_A467_DE09C0C42940__INCLUDED_)
