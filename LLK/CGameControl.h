#pragma once
#include"global.h"
#include"Graph.h"
class CGameControl
{
private:
	CGraph m_graph;				//初始游戏地图

	Vertex m_ptSelFirst;	//第一次选中的点
	Vertex m_ptSelSec;		//第二次选中的点

public:
	void StartGame(void);								//开始游戏函数
	int GetElement(int nRow, int nCol);					//获得某行某列的图片编号函数
	bool Link(Vertex avPath[MRow * MCol], int& nVexnum); //先判断所选择的图片是否是同一张图片，然后判断是否是同一种图片(消子判断)
	void SetFirstPoint(int nRow, int nCol);//设置第一个点
	void SetSecPoint(int nRow, int nCol);//设置第二个点
	bool IsWin();//判断是否获胜
	bool Help(Vertex avPath[MRow * MCol], int& nVexnum);
	void Reset();
};

