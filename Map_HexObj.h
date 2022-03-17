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
	
	// ���Ǹ���к�
	int						m_iJ;
	// ���Ǹ���к�
	int						m_iI;

	// ���Ǹ���гߴ�
	double					m_dSize;

	// ϵͳ��ʼ�㣬ȱʡΪ(0,0)
	double					m_dInitiativeX;
	double					m_dInitiativeY;
	
	// ��������½ǵ�
	double					m_dMapLeft;
	double					m_dMapBottom;
	
	// ���Ǹ�ĵ�������
	int						m_iTerrainType;
	
	
	// ���Ǹ������λ��
	double					m_dCenterX;
	double					m_dCenterY;
	
	// ���Ǹ����ǵ������
	double					m_dCornerX[6];
	double					m_dCornerY[6];

	//
	POINT					m_ptCornerPoint[7];

	double		m_dMapXA,m_dMapXB;
	double		m_dMapYA,m_dMapYB;

public:
	// ���Ǹ������ߵ�����
	int						m_iSideTypeA;
	int						m_iSideTypeB;
	int						m_iSideTypeC;
	int						m_iSideTypeD;
	int						m_iSideTypeE;
	int						m_iSideTypeF;

public:
	void	DrawLine(CDC* pDC, int iPointNum, POINT* pPoint, COLORREF crLine);

	void	Init(int iI,int iJ, double dOrignX,double dOrignY, double dHeight);
	//��ʾ����
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
