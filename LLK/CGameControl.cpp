#include "pch.h"
#include "CGameControl.h"
#include"CGameLogic.h"

bool CGameControl::Link(Vertex avPath[MRow * MCol], int& nVexnum)
{

	//�ж��Ƿ�Ϊͬһ��ͼƬ
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	int	info1 = m_graph.GetVertex(m_ptSelFirst.row * MCol + m_ptSelFirst.col);
	int	info2 = m_graph.GetVertex(m_ptSelSec.row * MCol + m_ptSelSec.col);

	//�ж�ͼƬ�Ƿ���ͬ
	if (info1 != info2 || info1 == BLANK || info2 == BLANK) return false;


	//��ͨ�ж�
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);

		//����·������
		nVexnum = gameLogic.GetVexPath(avPath);

		return true;
	}

	return false;
}

//���õ�һ���㺯��
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;

}

//���õڶ����㺯��
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;

}

//��ʼ��Ϸ����
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);

}

//���ĳ��ĳ�е�ͼƬ��ź���
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MCol + nCol);
}

bool CGameControl::IsWin()
{
	CGameLogic logic;
	if (logic.IsBlank(m_graph) == true) {//���ͼ�е����еĶ���Ϊ��
		m_graph.ClearGraph(); //��ͼ�ж���ͱ߻�ԭΪ��ʼ״̬������ͼ�ṹ
		return true;
	}
	return false;
}

//ʵ����ʾ����
bool CGameControl::Help(Vertex avPath[MRow * MCol], int& nVexnum)
{
	CGameLogic gamelogic;

	//���ж���Ϸ�Ƿ�Ϊ��
	if (gamelogic.IsBlank(m_graph) == true)
	{
		return false;
	}
	//���ҿ����ӵ�ͼƬ��
	if (gamelogic.SearchValidPath(m_graph))
	{
		//����·������
		nVexnum = gamelogic.GetVexPath(avPath);

		return true;
	}
	return false;

}

//ʵ�����Ź���
void CGameControl::Reset()
{
	//�Ե�ͼ��������
	CGameLogic gamelogic;
	gamelogic.ResetGraph(m_graph);
}