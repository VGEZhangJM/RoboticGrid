// Map_LineElement.h: interface for the CMap_LineElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_LINEELEMENT_H__91B41302_124D_4616_9F8F_5EA2F5E05B2C__INCLUDED_)
#define AFX_MAP_LINEELEMENT_H__91B41302_124D_4616_9F8F_5EA2F5E05B2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMap_LineElement  
{
public:
	//
	bool Read(FILE *fp);

	CMap_LineElement();
	virtual ~CMap_LineElement();

protected:
	int m_iID;
	//子类
	int m_iSubType;
	//主类
	int m_iMainType;

	//
	int					m_iPointNum;
	SMap_DPointCoord*	m_pPointList;

	//下一要素
	CMap_LineElement*	m_pNext;
};

#endif // !defined(AFX_MAP_LINEELEMENT_H__91B41302_124D_4616_9F8F_5EA2F5E05B2C__INCLUDED_)
