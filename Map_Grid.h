// Map_Grid.h: interface for the CMap_Grid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_GRID_H__4D96DCCA_3D4C_4AF5_8B2C_9D5822F2DDE8__INCLUDED_)
#define AFX_MAP_GRID_H__4D96DCCA_3D4C_4AF5_8B2C_9D5822F2DDE8__INCLUDED_

#include "Map_GridObj.h"
#include "Analyse_WorkSpace.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_Grid  
{
public:
	CMap_Grid();
	virtual ~CMap_Grid();

	
public:
	//
	CMap_GridObj* m_pObjList;

protected:
	int		m_iNumX;
	int		m_iNumY;

	//这是需要避开的网格
	int		m_iNullI;
	int		m_iNullJ;

	//如果从某一网格不能达到另一个网格
	int		m_iFromI, m_iFromJ;
	int		m_iToI, m_iToJ;
	
	//正方形是边长
	double	m_dSize;

	double	m_dLeft;
	double	m_dRight;
	double	m_dBottom;
	double	m_dTop;

	//
	double	m_dMapXA,m_dMapXB;
	double	m_dMapYA,m_dMapYB;

	//
	double	m_dShowLeft,m_dShowRight;
	double	m_dShowBottom,m_dShowTop;

	//
	CArray<SGrid_Info,SGrid_Info>	m_pTerrainList;
public:
	bool	CreateNetwork(CAnalyse_WorkSpace *pWorkspace,int iTerrainType);

	bool	CreateGrid(double dSize, double dLeft,double dRight,double dBottom,double dTop);

	void	Draw(CDC* pDC,int iTerrainType);
	void	SetCoordMapping(double dXA,double dXB,double dYA,double dYB);
	
	//
	int		CalcGrid(int iTerrainType, double& dArea);
	void	CalcGrid();

	bool	Save(CString szPathName);
	bool	SaveNetwork(CString szPathName);

	//
	int		GetNumX();
	int		GetNumY();

	int		Query(double dX,double dY, int& iI,int& iJ);

	void	SetShowExt(double dLeft,double dRight,double dBottom, double dTop);

	void	CreateSide();

	void	SetNullTerrain(int iNullI, int iNullJ, int iFromI, int iFromJ, int iToI, int iToJ);
};

#endif // !defined(AFX_MAP_GRID_H__4D96DCCA_3D4C_4AF5_8B2C_9D5822F2DDE8__INCLUDED_)
