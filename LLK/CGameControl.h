#pragma once
#include"global.h"
#include"Graph.h"
class CGameControl
{
private:
	CGraph m_graph;				//��ʼ��Ϸ��ͼ

	Vertex m_ptSelFirst;	//��һ��ѡ�еĵ�
	Vertex m_ptSelSec;		//�ڶ���ѡ�еĵ�

public:
	void StartGame(void);								//��ʼ��Ϸ����
	int GetElement(int nRow, int nCol);					//���ĳ��ĳ�е�ͼƬ��ź���
	bool Link(Vertex avPath[MRow * MCol], int& nVexnum); //���ж���ѡ���ͼƬ�Ƿ���ͬһ��ͼƬ��Ȼ���ж��Ƿ���ͬһ��ͼƬ(�����ж�)
	void SetFirstPoint(int nRow, int nCol);//���õ�һ����
	void SetSecPoint(int nRow, int nCol);//���õڶ�����
	bool IsWin();//�ж��Ƿ��ʤ
	bool Help(Vertex avPath[MRow * MCol], int& nVexnum);
	void Reset();
};

