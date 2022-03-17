#ifndef _IVR_PUBLICSTRUCT_H_
#define _IVR_PUBLICSTRUCT_H_

////////////////////////////////////////////////////
// ��������[��ʼ]
////////////////////////////////////////////////////
//{
	//Բ����
	#define	PI							3.14159265357
	//��
	#define	ZERO						1e-10

//}
////////////////////////////////////////////////////
// ��������[����]
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// ��Ϣ����[��ʼ]
////////////////////////////////////////////////////
//{

//}
////////////////////////////////////////////////////
// ��Ϣ����[����]
////////////////////////////////////////////////////

////////////////////////////////////////////////////
//ö�ٱ���[��ʼ]
////////////////////////////////////////////////////
//{
	//��ͼ���
	enum	eMapTool
	{
		giMapNone,

		giMapZoomIn	= 1001,
		giMapZoomOut,
		giMapPan,
		giMapPanMouse,
		giMapPanEx,

		giMapPointSelect	= 1010,
		giMapRectSelect,
		giMapEllipseSelect,
		giMapPolygonSelect,
		giHeightSelect,
	};
//}
////////////////////////////////////////////////////
//ö�ٱ���[����]
////////////////////////////////////////////////////

////////////////////////////////////////////////////
//�ṹ�嶨��[��ʼ]
////////////////////////////////////////////////////
//{
	//���͵�����
	typedef	struct	tagPointCoord
	{
		long			x;
		long			y;
	}SMap_PointCoord;
	
	//�����͵�����
	typedef	struct	tagDPointCoord
	{
		double			x;
		double			y;
	}SMap_DPointCoord;

	//���Ǹ���Ϣ
	typedef	struct	tagHexagonal
	{
		// ���Ǹ���к�
		int		iHexRow;
		// ���Ǹ���к�
		int		iHexLine;

		// ���Ǹ���������
		double	dHexCenterX;
		double	dHexCenterY;

		// ���Ǹ�ĸ߳���Ϣ
		int		iHeight;
		// ���Ǹ�������Ϣ
		int		iDepth;
		// ���Ǹ�ĵ�������
		int		iHexTerrainType;

		// ���Ǹ������ߵ�����
		int		iHexBarrierTypeA;
		int		iHexBarrierTypeB;
		int		iHexBarrierTypeC;
		int		iHexBarrierTypeD;
		int		iHexBarrierTypeE;
		int		iHexBarrierTypeF;
	}Hexagonal;

	//���
	typedef	struct	tagRouteNodes
	{
		long	nPointNo;
		double	dCoordX;
		double	dCoordY;
	}SRoute_Nodes;
	
	//
	typedef	struct	tagRouteWays
	{
		long			m_nPointNum;
		SMap_PointCoord	*m_pPointCoord;
		
		double			m_dWeight;
		char			m_chName[30];
	}SRoute_Ways;
	
	//���ӽڵ���Ϣ
	typedef	struct	tagRouteNodeLink
	{
		long			m_pLinkFirstNode;
		//��رߵ�ĩ����
		long			m_pLinkLastNode;
		//
		double			m_dX;
		double			m_dY;

		//�����Ȩֵ
		double			m_pLinkWeight;
	}SRoute_NodeLink;

	//���ӽڵ���Ϣ
	typedef	struct	tagGridOInfo
	{
		int		iTerrainType;
		int		iCount;
		double	dArea;
	}SGrid_Info;
	

//}
////////////////////////////////////////////////////
//�ṹ�嶨��[����]
////////////////////////////////////////////////////
#endif