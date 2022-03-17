// PublicFunction.cpp: implementation of the CPublicFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoboticGrid.h"
#include "PublicFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPublicFunction::CPublicFunction()
{

}

CPublicFunction::~CPublicFunction()
{


}

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
bool CPublicFunction::PointInPolygon(double dXX, double dYY, int iNum, double *dX, double *dY)
{
	int		iInsideFlag,iFlag;
	int		i;
	double	dX0,dY0,dX1,dY1,dX2,dY2;
	
	iInsideFlag	= 0;
	
	for(i=0;i<=iNum-1;i++)
	{
		
		dX1	= dX[i];		dY1	= dY[i];
		if(i==iNum-1)
		{
			dX0	= dX[i];	dY0	= dY[i];
		}
		else
		{
			dX0	= dX[i+1];	dY0	= dY[i+1];
		}
		if(i==0)
		{
			dX2	= dX[i];	dY2	= dY[i];
		}
		else
		{
			dX2	=dX[i-1];	dY2	=dY[i-1];
		}	
		if(dY1!=dYY)
		{
			if(dY0>dYY&&dY1<dYY||dY0<dYY&&dY1>dYY)
			{
				if(dX0<dXX&&dX1<dXX)
				{
					iInsideFlag	=iInsideFlag;
				}
				if(dX0>dXX&&dX1>dXX)
				{
					if(iInsideFlag==0)		iFlag=1;
					if(iInsideFlag==1)		iFlag=0;
					
					iInsideFlag	=iFlag;
				}
				if(dX0>=dXX&&dX1<=dXX||dX0<=dXX&&dX1>=dXX)
				{
					double xp;
					xp=IfLineCut(dX0,dX1,dY0,dY1,dYY);
					if(xp<dXX)
					{
						iInsideFlag	=iInsideFlag;
					}
					if(xp>=dXX)
					{
						if(iInsideFlag==0)		iFlag=1;
						if(iInsideFlag==1)		iFlag=0;
						
						iInsideFlag	=iFlag;
					}
				}
			}
			else
			{
				iInsideFlag	=iInsideFlag;
			}
		}
		else
		{
			if(dX1<dXX)
				iInsideFlag	=iInsideFlag;
			else
			{
				if(dY0>dYY)
				{
					if(iInsideFlag==0)		iFlag=1;
					if(iInsideFlag==1)		iFlag=0;
					iInsideFlag	=iFlag;
					
				}
				if(dY2>dYY)
				{
					if(iInsideFlag==0)		iFlag=1;
					if(iInsideFlag==1)		iFlag=0;
					
					iInsideFlag	=iFlag;
				}
			}
		}
	}
	
	if(iInsideFlag==1)	return	true;
	else				return	false;
}


//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
double CPublicFunction::IfLineCut(double dX0, double dX1, double dY0, double dY1, double dYY)
{
	double	dXX;
	
	if(dX1 == dX0)
	{
		dXX	= dX1;	
	}
	else
	{
		double k;
		k	= (dY1-dY0)/(dX1-dX0);
		
		dXX	= dX0+(dYY-dY0)/k;
	}
	
	return	dXX;
}

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
double CPublicFunction::GetArea(int iNum, double *dXX, double *dYY)
{
	double	s,deltas;
	
	deltas	= 0.0;
	s		= 0.0;
	for(int i=1;i<iNum;i++)
	{
		deltas	= (dYY[i]+dYY[i-1])*(dXX[i]-dXX[i-1])/2.0;
		
		s		= s + deltas;
	}
	
	s	= fabs(s);
	
	return	s;
}

//返回方向
int CPublicFunction::JudgeDirection(double dXIn,double dYIn,double dXOut,double dYOut,double dXO,double dYO)
{
	int		iDirection;
	double	dX,dY;
	double	dAngleIn,dAngleInEx,dAngleOut;
	
	iDirection	= 0;
	
	dX			= dXIn-dXO;
	dY			= dYIn-dYO;
	dAngleIn	= GetAngle(dX,dY);
	
	dX			= dXOut-dXO;
	dY			= dYOut-dYO;
	dAngleOut	= GetAngle(dX,dY);
	
	//进角加上PI，比较和
	dAngleInEx	= dAngleIn + PI;
	
	bool	bChange;
	bChange		= false;
	
	if(dAngleInEx>2*PI)			{	dAngleInEx	= dAngleInEx-2*PI;	bChange	= true;		}
	
	int		iSign,iSignEx;
	
	if(fabs(dAngleIn-dAngleOut) < PI/10)	iSign	= 0;
	else	if(dAngleIn>dAngleOut)			iSign	= 1;
	else									iSign	= -1;
	
	if(fabs(dAngleInEx-dAngleOut) < PI/10)	iSignEx	= 0;
	else	if(dAngleInEx>dAngleOut)		iSignEx	= 1;
	else									iSignEx	= -1;
	
	if(!bChange)
	{
		if(iSign*iSignEx == 0)			iDirection	= 1;	//直行
		if(iSign*iSignEx > 0)			iDirection	= 2;	//左转
		if(iSign*iSignEx < 0)			iDirection	= 3;	//右转
	}
	else
	{
		if(iSign*iSignEx == 0)			iDirection	= 1;	//直行
		if(iSign*iSignEx > 0)			iDirection	= 3;	//右转
		if(iSign*iSignEx < 0)			iDirection	= 2;	//左转
	}
	
	return	iDirection;
}

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
double CPublicFunction::GetAngle(double dX, double dY)
{
	double	dAngle;
	
	if(fabs(dY) < 1e-10)
	{
		if(dX > 0.0)					dAngle	= 0.0;
		else							dAngle	= PI;
	}
	else	if(dY > 1e-10)
	{
		if(dX > 1e-10)					dAngle	= atan2(fabs(dY),fabs(dX));		
		else	if(fabs(dX) < 1e-10)	dAngle	= PI/2;
		else	if(dX < 1e-10)			dAngle	= PI-atan2(fabs(dY),fabs(dX));
	}
	else
	{
		if(dX > 1e-10)					dAngle	= PI*2-atan2(fabs(dY),fabs(dX));
		else	if(fabs(dX) < 1e-10)	dAngle	= PI*3/2;
		else	if(dX < 1e-10)			dAngle	= PI+atan2(fabs(dY),fabs(dX));
	}
	return	dAngle;
}

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
double CPublicFunction::GetAngle(int iX, int iY)
{
	double	dAngle;
	
	if(fabs((double)iY) < ZERO)
	{
		if(iX > 0.0)					dAngle	= 0.0;
		else							dAngle	= PI;
	}
	else	if(iY > ZERO)
	{
		if(iX > ZERO)							dAngle	= atan2(fabs((double)iY),fabs((double)iX));		
		else	if(fabs((double)iX) < ZERO)		dAngle	= PI/2;
		else	if(iX < ZERO)					dAngle	= PI-atan2(fabs((double)iY),fabs((double)iX));
	}
	else
	{
		if(iX > ZERO)							dAngle	= PI*2-atan2(fabs((double)iY),fabs((double)iX));
		else	if(fabs((double)iX) < ZERO)		dAngle	= PI*3/2;
		else	if(iX < ZERO)					dAngle	= PI+atan2(fabs((double)iY),fabs((double)iX));
	}
	return	dAngle;
}
