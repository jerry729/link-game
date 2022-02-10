#pragma once
#include"global.h"
#include"Graph.h"
class CGameLogic
{
protected:
	Vertex m_avPath[MRow*MCol];    //ʹ��ջ��������ͨ·���еĹؼ��㣺��ʼ��v0���յ�v1���յ�v2
	void AddVertex(Vertex v);        //�����������һ��Ԫ��
	int m_nVexNum;         //��ʾ������
	void DeleteVertex();             //��������ɾ��һ��Ԫ��

	int m_nCorner;//��ʾ����·���еĹյ���

	int m_anPath[MRow * MCol];      //�����ڽ��������ж�ʱ�������Ķ���


public:
	CGameLogic();
	~CGameLogic();
	void InitMap(CGraph& graph);//��ʼ����Ϸ��ͼ
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);//�ж��Ƿ���ͨ
	void Clear(CGraph& graph, Vertex v1, Vertex v2);//�������

	void UpdateArc(CGraph& graph, int nRow, int nCol);//�ж���Ϸ��ͼ�е�nRow�У�nCol�еĶ��������������ҵĶ����Ƿ��бߣ�����бߣ������ͼ�ṹ��������

	//�õ�·�������ض�����
	int GetVexPath(Vertex avPath[MRow * MCol]);

	//���һ��·������
	void PushVertex(int nV);
	//ȡ��һ������
	void PopVertex();
	//��Ѱ·��
	bool SearchPath(CGraph& graph, int nV0, int nV1);
	//�ж϶����Ƿ�����·���д���
	bool IsExsit(int nVi);
	//�жϹյ����Ч��
	bool IsCornor();
	//�ж�ͼ�е����еĶ����Ƿ�Ϊ�գ������Ϊ�գ��򷵻�true�����򣬷���false
	bool IsBlank(CGraph& graph);
	//��Ѱ�����ӵ���Ч·���������жϵ�ͼ��ͬɫԪ���Ƿ������ͨ
	bool SearchValidPath(CGraph& graph);
	//�����ѡ��ͼ���������㣬��Ԫ�ؽ��н�������������100��
	void ResetGraph(CGraph& graph);

};
