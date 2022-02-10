#include "pch.h"
#include "Graph.h"

CGraph::CGraph()
{
	InitGraph();   //��ʼ��ͼ
}


CGraph::~CGraph()
{
}

//��ʼ��ͼ
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;

	//��ʼ�����������Ϣ
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//��ʼ������
		m_Vertices[i] = -1;
	}
	//��ʼ����
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			m_AdjMatrix[i][j] = false;
		}
	}

}


int CGraph::AddVertex(int info)
{
	if (m_nVexnum >= MAX_VERTEX_NUM) {
		return 0;
	}
	//����������info��ӵ�����������
	m_Vertices[m_nVexnum] = info;
	m_nVexnum++;
	return m_nVexnum;//���ض��������ж������
}

//���ɱ� 
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	//���ݶ������������������������Ķ���ı�
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

//��������,�Ӷ���������ȡ����Ӧ�Ķ���
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

//��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo
void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//��ȡͼ�ж���ĸ���
int CGraph::GetVexnum()
{
	return m_nVexnum;
}

void CGraph::ClearGraph(void)
{
	InitGraph();//����ͼ�ṹ
}

void CGraph::Change(int n1, int n2) {
	int t = m_Vertices[n1];
	m_Vertices[n1] = m_Vertices[n2];
	m_Vertices[n2] = t;
}