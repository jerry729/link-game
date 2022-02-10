#include "pch.h"
#include "CGameLogic.h"
#include"global.h"
#include<cstdlib>
#include<ctime>
#include"Graph.h"

CGameLogic::CGameLogic()
{

	m_nVexNum = 0;     //������ʵ��Ԫ�صĸ���
	m_nCorner = 0;     //·���еĹյ����
}


CGameLogic::~CGameLogic()
{
}

// ��ʼ����Ϸ��ͼ
void CGameLogic::InitMap(CGraph& graph)
{
	//��Ϸ��ͼ�����ʼ��
	srand((int)time(NULL));//��������
	
	//����16�ֻ�ɫ�ĵ�ͼ
	int anTemp[MRow][MCol];
	int a = 0;//��ʼ�ĵ�һ��ͼƬ���
	for (int j = 0; j < MCol; j++) {
		for (int i = 0; i < MRow; i++) {
			anTemp[i][j] = j;
		}
	}
	//���ҵ�ͼ��ɫ˳��
	for (int i = 0; i < MRow ; i++) {
		for (int j = 0; j < MCol; j++) {
			int i1 = rand() % MRow;
			int j1= rand() % MCol;
			//����������Ļ�ɫ
			int t = anTemp[i][j];
			anTemp[i][j] = anTemp[i1][j1];
			anTemp[i1][j1] = t;
		}
	}
	
	//��ʼ������
	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {
			graph.AddVertex(anTemp[i][j]); 
		}
	}

	//��ʼ����
	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {
			UpdateArc(graph, i, j);
		}
	}

}

//����ͼ������
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nV1Index = nRow * MCol + nCol;

	if (nCol > 0) {//����ߵ�����ͨ
		int nV2Index = nV1Index - 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nCol < MCol-1) {//���ұߵ�����ͨ
		int nV2Index = nV1Index + 1;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK){
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow > 0) {//�����Ϸ�������ͨ
		int nV2Index = nV1Index - MCol;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK)
		{	graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow < MRow-1) {//�����·�������ͨ
		int nV2Index = nV1Index + MCol;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index)|| graph.GetVertex(nV2Index)==BLANK|| graph.GetVertex(nV1Index) == BLANK)
		{graph.AddArc(nV1Index, nV2Index);
		}
	}
}
//�����������һ��Ԫ��
void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}


//��������ɾ��һ��Ԫ��
void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}

//����
void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{
	//��ö���������
	int nV1Index = v1.row * MCol + v1.col;
	int nV2Index = v2.row * MCol+ v2.col;
	//���¶���
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);
	//���±���Ϣ
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}

//��ȡ����·��
int CGameLogic::GetVexPath(Vertex avPath[MRow * MCol])
{
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < MCol; point.col++)
		{
			for (point.row = 0; point.row < MRow; point.row++)
			{
				if (point.row * MCol + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}

	return m_nVexNum;
}

//��ͨ�ж�
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
	//��ö���������
	int nV1Index = v1.row * MCol + v1.col;
	int nV2Index = v2.row * MCol+ v2.col;

	 //ѹ���һ����
	PushVertex(nV1Index); 

	//��Ѱ����֮�����ͨ·��
	if (SearchPath(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}
	//ȡ��ѹ��Ķ���
	PopVertex();
	return false;
}

//����������������㷨�ж��Ƿ���ͨ
bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	//��ȡ������
	int nVexnum = graph.GetVexnum();

	//����ͼ��nV0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			//ѹ�뵱ǰ���㣬����Ϊ·����һ����Ч����
			PushVertex(nVi);
			//���յ�������2 ʱ
			if (m_nCorner > 2)
			{
				//ȡ��ѹ��Ķ���
				PopVertex();          
				continue;
			}
			//���м䶥�㲻��nViʱ��������Ѱ��һ������������ͨ�Ķ���
			if (nVi != nV1)
			{
				//���м䶥�㲻Ϊ��ʱ����ʾ����·����ͨ
				if (graph.GetVertex(nVi) != BLANK)
				{	
					//ȡ��ѹ��Ķ���
					PopVertex();      
					continue;
				}
				//���nVi��һ���������ĵ㣬���жϣ�nVi��nV1���Ƿ���ͨ
				if (SearchPath(graph, nVi, nV1))
				{
					return true;
				}
			}
			else//��ʾ�Ѿ��ҵ�һ����ͨ·�����򷵻�true
			{
				return true;
			}

			PopVertex();     //ȡ��ѹ��Ķ��㣬��PushWertex()��Ӧ
		}
	}
	return false;
}

//�жϸö��㱣�浽·��������
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi) return true;
	}
	return false;
}

//�жϹյ����Ч��
bool CGameLogic::IsCornor(void)
{
	//�ж�m_anPath������������3�������Ƿ���һ���յ�
	if (m_nVexNum >= 3)
	{
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}

//���һ��·������
void CGameLogic::PushVertex(int nV)
{
	//������ѹջ
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;

	//�ж��Ƿ��γ�һ���յ�
	if (IsCornor())
	{
		m_nCorner++;
	}
}

//ȡ��һ��·������
void CGameLogic::PopVertex()
{
	//�ж��Ƿ��ǹյ㣬����ǣ�����ٹյ���
	if (IsCornor())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}

//�ж�ͼ�е����еĶ����Ƿ�Ϊ�գ������Ϊ�գ��򷵻�true�����򣬷���false
bool CGameLogic::IsBlank(CGraph& graph)
{
	int nVexnum = graph.GetVexnum();//��ȡ���������еĶ�����
	for (int i = 0; i < nVexnum; i++) {
		if (graph.GetVertex(i) != BLANK) return false;//��ȡ��������������ΪnIndex�Ķ���
	}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph& graph)
{
	//�õ�������
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//�õ���һ���ǿն���
		if (graph.GetVertex(i) == BLANK)continue;
		//�õ��ڶ�����ͬһ������
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				if (graph.GetVertex(i) == graph.GetVertex(j))//��i����͵�j����ͬɫ
				{
					//ѹ���һ����
					PushVertex(i);
					if (SearchPath(graph, i, j) == true)//�ܹ���ͨ
					{
						return true;
					}
					//ȡ��ѹ��Ķ���ʱ����PushVertex(i)��Ӧ
					PopVertex();
				}

			}
		}
	}
	return false;
}

//�����ѡ��ͼ���������㣬��Ԫ�ؽ��н�������������100��
void CGameLogic::ResetGraph(CGraph& graph)
{
	//��������
	srand((int)time(NULL));
	//����������������ֵ
	for (int i = 0; i < 100; i++)
	{
		//����õ���������
		int n1 = rand() % MAX_VERTEX_NUM;
		int n2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		graph.Change(n1, n2);
	}

	//���»���Ϣ
	for (int i = 0; i < MRow; i++)
	{
		for (int j = 0; j < MCol; j++)
		{
			UpdateArc(graph, i, j);
		}
	}

}