// Analyse_RouteNode.h: interface for the CAnalyse_RouteNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALYSE_ROUTENODE_H__7E5DDC66_8660_4A4B_9705_0CA267F0609A__INCLUDED_)
#define AFX_ANALYSE_ROUTENODE_H__7E5DDC66_8660_4A4B_9705_0CA267F0609A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//�������
class CAnalyse_RouteNode
{
public:
	CAnalyse_RouteNode();
	virtual ~CAnalyse_RouteNode();
	
public:
	//
	void					Release();
	//
	bool					Load(FILE *fp);

	//��·
	void					DisWay(long nFirstNode,long nLastNode);
	//�ָ���·
	void					UnDisWay(long nFirstNode,long nLastNode);
	
	//�ܿ����
	void					DisNode(long nNode);
	//�ָ��ܿ����
	void					UnDisNode(long nNode);

public:
	//���
	long					m_nPointNo;
	//����
	double					m_dMapLeft;
	double					m_dMapBottom;

	double					m_dCoordX;			
	double					m_dCoordY;
	//��ر���
	BYTE					m_nLinkLineNum;	
	
	//��رߵ��ߺ�
	//CArray<long,long>		m_pLinkLineNo;		

	//��رߵ��׽��š��׽���ĩ���֮һӦ�����һ�¡�

	//CArray<long,long>		m_pLinkFirstNode;		
	//��رߵ�ĩ����
	//CArray<long,long>		m_pLinkLastNode;

	//�ļ��еĵ�ַ
	//CArray<long,long>		m_pLinkFileAddress;	

	//�����Ȩֵ
	//CArray<long,long>		m_pLinkWeight;		

	//ʱ���Ȩֵ
	//CArray<long,long>		m_pLinkTime;

	//��ر���Ϣ��������ĩ�ڵ㡢�ļ���ַ������Ȩֵ��ʱ��Ȩֵ
	SRoute_NodeLink			*m_pNodeLink;
	
	//
	CAnalyse_RouteNode		*m_pNext;
};

#endif // !defined(AFX_ANALYSE_ROUTENODE_H__7E5DDC66_8660_4A4B_9705_0CA267F0609A__INCLUDED_)
