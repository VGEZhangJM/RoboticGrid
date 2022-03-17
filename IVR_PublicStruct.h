#ifndef _IVR_PUBLICSTRUCT_H_
#define _IVR_PUBLICSTRUCT_H_

////////////////////////////////////////////////////
// 常量定义[开始]
////////////////////////////////////////////////////
//{
	//圆周率
	#define	PI							3.14159265357
	//零
	#define	ZERO						1e-10

//}
////////////////////////////////////////////////////
// 常量定义[结束]
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// 消息定义[开始]
////////////////////////////////////////////////////
//{

//}
////////////////////////////////////////////////////
// 消息定义[结束]
////////////////////////////////////////////////////

////////////////////////////////////////////////////
//枚举变量[开始]
////////////////////////////////////////////////////
//{
	//地图相关
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
//枚举变量[结束]
////////////////////////////////////////////////////

////////////////////////////////////////////////////
//结构体定义[开始]
////////////////////////////////////////////////////
//{
	//整型点坐标
	typedef	struct	tagPointCoord
	{
		long			x;
		long			y;
	}SMap_PointCoord;
	
	//浮点型点坐标
	typedef	struct	tagDPointCoord
	{
		double			x;
		double			y;
	}SMap_DPointCoord;

	//六角格信息
	typedef	struct	tagHexagonal
	{
		// 六角格的行号
		int		iHexRow;
		// 六角格的列号
		int		iHexLine;

		// 六角格中心坐标
		double	dHexCenterX;
		double	dHexCenterY;

		// 六角格的高程信息
		int		iHeight;
		// 六角格的深度信息
		int		iDepth;
		// 六角格的地形属性
		int		iHexTerrainType;

		// 六角格六条边的属性
		int		iHexBarrierTypeA;
		int		iHexBarrierTypeB;
		int		iHexBarrierTypeC;
		int		iHexBarrierTypeD;
		int		iHexBarrierTypeE;
		int		iHexBarrierTypeF;
	}Hexagonal;

	//结点
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
	
	//连接节点信息
	typedef	struct	tagRouteNodeLink
	{
		long			m_pLinkFirstNode;
		//相关边的末结点号
		long			m_pLinkLastNode;
		//
		double			m_dX;
		double			m_dY;

		//距离的权值
		double			m_pLinkWeight;
	}SRoute_NodeLink;

	//连接节点信息
	typedef	struct	tagGridOInfo
	{
		int		iTerrainType;
		int		iCount;
		double	dArea;
	}SGrid_Info;
	

//}
////////////////////////////////////////////////////
//结构体定义[结束]
////////////////////////////////////////////////////
#endif