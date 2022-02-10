#include "pch.h"
#include "Graph.h"

CGraph::CGraph()
{
	InitGraph();   //初始化图
}


CGraph::~CGraph()
{
}

//初始化图
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;

	//初始化顶点与边信息
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//初始化顶点
		m_Vertices[i] = -1;
	}
	//初始化边
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
	//将顶点数据info添加到顶点数组中
	m_Vertices[m_nVexnum] = info;
	m_nVexnum++;
	return m_nVexnum;//返回顶点数组中顶点个数
}

//生成边 
void CGraph::AddArc(int nV1Index, int nV2Index)
{
	//根据顶点的索引，添加这两个索引的顶点的边
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

//根据索引,从顶点数组中取出相应的顶点
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

//将图顶点数组中索引号为nIndex的顶点的值更新为info
void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//获取图中顶点的个数
int CGraph::GetVexnum()
{
	return m_nVexnum;
}

void CGraph::ClearGraph(void)
{
	InitGraph();//清理图结构
}

void CGraph::Change(int n1, int n2) {
	int t = m_Vertices[n1];
	m_Vertices[n1] = m_Vertices[n2];
	m_Vertices[n2] = t;
}