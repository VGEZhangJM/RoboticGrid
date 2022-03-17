// PublicFunction.h: interface for the CPublicFunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICFUNCTION_H__CC940963_71FF_47B4_9945_F71E476D2A7A__INCLUDED_)
#define AFX_PUBLICFUNCTION_H__CC940963_71FF_47B4_9945_F71E476D2A7A__INCLUDED_

#include <math.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPublicFunction  
{
public:
	CPublicFunction();
	virtual ~CPublicFunction();

	//
	bool	PointInPolygon(double dXX, double dYY, int iNum, double *dX, double *dY);
	double	IfLineCut(double dX0, double dX1, double dY0, double dY1, double dYY);
	double	GetArea(int iNum, double *dXX, double *dYY);
	int		JudgeDirection(double dXIn,double dYIn,double dXOut,double dYOut,double dXO,double dYO);
	double	GetAngle(int iX, int iY);
	double	GetAngle(double dX, double dY);

};

#endif // !defined(AFX_PUBLICFUNCTION_H__CC940963_71FF_47B4_9945_F71E476D2A7A__INCLUDED_)
