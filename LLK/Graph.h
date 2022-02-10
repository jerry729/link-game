#pragma once

//ͼ  ���ݽṹ��

class CGraph
{
public:
	CGraph();
	~CGraph();



public:

#define MAX_VERTEX_NUM 160					//���������10��16�У�
	typedef int Vertices[MAX_VERTEX_NUM];	//������������
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//����������  ����

	int AddVertex(int info);//������info��ӵ�����������
	int GetVertex(int nIndex);//��ȡ��������������ΪnIndex�Ķ���
	int GetVexnum();//��ȡ���������еĶ�����
	void AddArc(int nV1Index, int nV2Index);//��ӹ�ϵ�����У�nV1Index�� nV2Index
	bool GetArc(int nV1Index, int nV2Index);//��ȡ��������Ļ���Ϣ
	void UpdateVertex(int nIndex, int info);//��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo
	void ClearGraph();//��ͼ�ж���ͱ߻�ԭΪ��ʼ״̬
	void Change(int n1,int n2);//�������������ֵ
protected:
	  
	AdjMatrix m_AdjMatrix;	//������  
	Vertices m_Vertices;//��������
	int m_nVexnum;		//������
	int m_nArcnum;		//������
	void InitGraph();		//��ʼ��ͼ�ṹ

};

