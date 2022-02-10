#pragma once
#include"global.h"
#include"Graph.h"
class CGameLogic
{
protected:
	Vertex m_avPath[MRow*MCol];    //使用栈来保存连通路径中的关键点：起始点v0、拐点v1和终点v2
	void AddVertex(Vertex v);        //向数组中添加一个元素
	int m_nVexNum;         //表示顶点数
	void DeleteVertex();             //向数组中删除一个元素

	int m_nCorner;//表示连接路径中的拐点数

	int m_anPath[MRow * MCol];      //保存在进行连接判断时所经过的顶点


public:
	CGameLogic();
	~CGameLogic();
	void InitMap(CGraph& graph);//初始化游戏地图
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);//判断是否连通
	void Clear(CGraph& graph, Vertex v1, Vertex v2);//清除顶点

	void UpdateArc(CGraph& graph, int nRow, int nCol);//判断游戏地图中第nRow行，nCol列的顶点与它上下左右的顶点是否有边，如果有边，则更新图结构，并返回

	//得到路径，返回顶点数
	int GetVexPath(Vertex avPath[MRow * MCol]);

	//添加一个路径顶点
	void PushVertex(int nV);
	//取出一个顶点
	void PopVertex();
	//搜寻路径
	bool SearchPath(CGraph& graph, int nV0, int nV1);
	//判断顶点是否已在路径中存在
	bool IsExsit(int nVi);
	//判断拐点的有效性
	bool IsCornor();
	//判断图中的所有的顶点是否为空，如果都为空，则返回true；否则，返回false
	bool IsBlank(CGraph& graph);
	//搜寻可消子的有效路径，依次判断地图中同色元素是否可以连通
	bool SearchValidPath(CGraph& graph);
	//随机任选地图中两个顶点，将元素进行交换，这样进行100次
	void ResetGraph(CGraph& graph);

};
