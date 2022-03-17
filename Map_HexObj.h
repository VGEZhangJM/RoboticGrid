// Map_HexObj.h: interface for the CMap_HexObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_HEXOBJ_H__9C91616D_42FB_45A4_8212_9B653525A265__INCLUDED_)
#define AFX_MAP_HEXOBJ_H__9C91616D_42FB_45A4_8212_9B653525A265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_HexObj  
{
public:
	CMap_HexObj();
	virtual ~CMap_HexObj();

protected:
	
	// 六角格的行号
	int						m_iJ;
	// 六角格的列号
	int						m_iI;

	// 六角格的行尺寸
	double					m_dSize;

	// 系统起始点，缺省为(0,0)
	double					m_dInitiativeX;
	double					m_dInitiativeY;
	
	// 区域的左下角点
	double					m_dMapLeft;
	double					m_dMapBottom;
	
	// 六角格的地形属性
	int						m_iTerrainType;
	
	
	// 六角格的中心位置
	double					m_dCenterX;
	double					m_dCenterY;
	
	// 六角格六角点的坐标
	double					m_dCornerX[6];
	double					m_dCornerY[6];

	//
	POINT					m_ptCornerPoint[7];

	double		m_dMapXA,m_dMapXB;
	double		m_dMapYA,m_dMapYB;

public:
	// 六角格六条边的属性
	int						m_iSideTypeA;
	int						m_iSideTypeB;
	int						m_iSideTypeC;
	int						m_iSideTypeD;
	int						m_iSideTypeE;
	int						m_iSideTypeF;

public:
	void	DrawLine(CDC* pDC, int iPointNum, POINT* pPoint, COLORREF crLine);

	void	Init(int iI,int iJ, double dOrignX,double dOrignY, double dHeight);
	//显示参数
	void	SetCoordMapping(double dXA,double dXB,double dYA,double dYB);
	//
	void	Draw(CDC* pDC);
	void	GetCenter(double& dX,double& dY);
	
	void	SetTerrainType(int iTerrainType);
	int		GetTerrainType();

protected:
	void	DrawPolyon(CDC* pDC, int iPointNum, POINT* pPoint, COLORREF crLine,COLORREF crFull);
};

#endif // !defined(AFX_MAP_HEXOBJ_H__9C91616D_42FB_45A4_8212_9B653525A265__INCLUDED_)
