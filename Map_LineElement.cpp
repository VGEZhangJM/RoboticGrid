// Map_LineElement.cpp: implementation of the CMap_LineElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboticGrid.h"
#include "Map_LineElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap_LineElement::CMap_LineElement()
{
	m_iID			= 0;
	//子类
	m_iSubType		= 0;
	//主类
	m_iMainType		= 0;

	m_iPointNum		= 0;	
	m_pPointList	= NULL;

	m_pNext			= NULL;
}

CMap_LineElement::~CMap_LineElement()
{

}

//读取文件
bool CMap_LineElement::Read(FILE *fp)
{
	if (fp == NULL)
	{
		return	false;
	}

	int	iID;
	int	iMainType;
	int iSubType;
	int iPointNum;

	fscanf(fp,"%ld%ld%ld%ld",&iID,&iMainType,&iSubType,&iPointNum);
	
	m_iID = iID;
	m_iMainType = iMainType;
	m_iSubType = iSubType;
	m_iPointNum = iPointNum;

	m_pPointList = new SMap_DPointCoord[iPointNum];
	for (int i=0;i<iPointNum;i++)
	{
		double dx,dy;

		fscanf(fp,"%lf%lf",&dx,&dy);

		m_pPointList[i].x = dx;
		m_pPointList[i].y = dy;
	}
	
	return	true;
}
