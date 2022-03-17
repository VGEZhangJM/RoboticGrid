// Map_Hex.h: interface for the CMap_Hex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_HEX_H__61AAFD85_7D3D_49C9_8978_9D71B90C5346__INCLUDED_)
#define AFX_MAP_HEX_H__61AAFD85_7D3D_49C9_8978_9D71B90C5346__INCLUDED_

#include "Map_HexObj.h"
#include "Analyse_WorkSpace.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_Hex  
{
public:
	CMap_Hex();
	virtual ~CMap_Hex();
public:
	//
	CMap_HexObj* m_pObjList;

protected:

	//
	int		m_iFullJ;
	int		m_iFullI;

	//������Ҫ�ܿ�������
	int		m_iNullI;
	int		m_iNullJ;

	//�����ĳһ�����ܴﵽ��һ������
	int		m_iFromI, m_iFromJ;
	int		m_iToI, m_iToJ;

	int	m_iNumX;
	int	m_iNumY;
	
	//�������Ǳ߳�
	double	m_dSize;
	
	//
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
	bool	CreateGrid(double dSize, double dLeft,double dRight,double dBottom,double dTop);
	void	CreateSide();
	bool	CreateNetwork(CAnalyse_WorkSpace *pWorkspace,int iTerrainType);

	void	SetCoordMapping(double dXA,double dXB,double dYA,double dYB);

	void	Draw(CDC* pDC);
	void	SetShowExt(double dLeft,double dRight,double dBottom, double dTop);

	int		GetNumX();
	int		GetNumY();

	//
	int		CalcGrid(int iTerrainType, double& dArea);
	void	CalcGrid();
	void	SetNullTerrain(int iFullI, int iFullJ, int iNullI, int iNullJ, int iFromI, int iFromJ, int iToI, int iToJ);
};

#endif // !defined(AFX_MAP_HEX_H__61AAFD85_7D3D_49C9_8978_9D71B90C5346__INCLUDED_)
