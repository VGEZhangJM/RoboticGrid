// Map_Map.h: interface for the CMap_Map class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_MAP_H__E0EDC009_7178_431D_8151_DA1D12FF09F5__INCLUDED_)
#define AFX_MAP_MAP_H__E0EDC009_7178_431D_8151_DA1D12FF09F5__INCLUDED_

#include <MATH.H>
#include "Map_PointElement.h"
#include "Map_LineElement.h"
#include "Map_PolygonElement.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_Map  
{
public:
	//
	bool Read(char* chPathName);
	
	//
	void Draw(CDC* pDC);

	//
	void SetCoordMapping(double dXA,double dXB,double dYA,double dYB);
	void GetCoordMapping(double& dXA,double& dXB,double& dYA,double& dYB);
	void ScreenToMap(int cx, int cy, double &xx, double &yy);
	//地图到屏幕的转换
	void MapToScreen(double xx, double yy, int &cx, int &cy);

	//
	void GetMapExt(double& dLeft, double& dRight,double& dBottom, double& dTop);
	void SetMapExt(double dLeft, double dRight,double dBottom, double dTop);
	void GetShowExt(double& dLeft, double& dRight,double& dBottom, double& dTop);
	void SetShowExt(double dLeft, double dRight,double dBottom, double dTop);
	void GetOldShowExt(double& dLeft, double& dRight,double& dBottom, double& dTop);
	void SetOldShowExt(double dLeft, double dRight,double dBottom, double dTop);

	void GetScreentPoint(int iX,int iY,double& dX,double& dY);
	
	bool IsOpened();

	bool	InitShow(CRect rRect, double dLeft, double dRight, double dBottom, double dTop);
	//
	int		Calculate(int iTerrainType, double& dArea);
	//
	void	Calculate();
	//
	CMap_PolygonElement* GetPolygonElement();

	CMap_Map();
	virtual ~CMap_Map();

protected:
	//
	CMap_PointElement* m_pPointListHead;
	CMap_PointElement* m_pPointListLast;

	//
	CMap_LineElement* m_pLineListHead;
	CMap_LineElement* m_pLineListLast;

	//
	CMap_PolygonElement* m_pPolygonListHead;
	CMap_PolygonElement* m_pPolygonListLast;
	
	//
	//视口的区域大小
	int					m_nWinMinX,m_nWinMaxX;
	int					m_nWinMinY,m_nWinMaxY;

	//缩放系数
	double				m_dMapXA,m_dMapXB;
	double				m_dMapYA,m_dMapYB;

	//显示区域
	double				m_dShowTop;
	double				m_dShowBottom;
	double				m_dShowRight;
	double				m_dShowLeft;
	
	//显示区域
	double				m_dOldShowTop;
	double				m_dOldShowBottom;
	double				m_dOldShowRight;
	double				m_dOldShowLeft;
	//地图区域
	double				m_dMapTop;
	double				m_dMapBottom;
	double				m_dMapRight;
	double				m_dMapLeft;
};

#endif // !defined(AFX_MAP_MAP_H__E0EDC009_7178_431D_8151_DA1D12FF09F5__INCLUDED_)
