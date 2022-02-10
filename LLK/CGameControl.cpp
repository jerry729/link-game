#include "pch.h"
#include "CGameControl.h"
#include"CGameLogic.h"

bool CGameControl::Link(Vertex avPath[MRow * MCol], int& nVexnum)
{

	//判断是否为同一个图片
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	int	info1 = m_graph.GetVertex(m_ptSelFirst.row * MCol + m_ptSelFirst.col);
	int	info2 = m_graph.GetVertex(m_ptSelSec.row * MCol + m_ptSelSec.col);

	//判断图片是否相同
	if (info1 != info2 || info1 == BLANK || info2 == BLANK) return false;


	//连通判断
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//消子
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);

		//返回路径顶点
		nVexnum = gameLogic.GetVexPath(avPath);

		return true;
	}

	return false;
}

//设置第一个点函数
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;

}

//设置第二个点函数
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;

}

//开始游戏函数
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);

}

//获得某行某列的图片编号函数
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MCol + nCol);
}

bool CGameControl::IsWin()
{
	CGameLogic logic;
	if (logic.IsBlank(m_graph) == true) {//如果图中的所有的顶点为空
		m_graph.ClearGraph(); //将图中顶点和边还原为初始状态，清理图结构
		return true;
	}
	return false;
}

//实现提示功能
bool CGameControl::Help(Vertex avPath[MRow * MCol], int& nVexnum)
{
	CGameLogic gamelogic;

	//先判断游戏是否为空
	if (gamelogic.IsBlank(m_graph) == true)
	{
		return false;
	}
	//查找可消子的图片对
	if (gamelogic.SearchValidPath(m_graph))
	{
		//返回路径顶点
		nVexnum = gamelogic.GetVexPath(avPath);

		return true;
	}
	return false;

}

//实现重排功能
void CGameControl::Reset()
{
	//对地图数据重排
	CGameLogic gamelogic;
	gamelogic.ResetGraph(m_graph);
}