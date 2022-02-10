#include "pch.h"
#include "CGameLogic.h"
#include"global.h"
#include<cstdlib>
#include<ctime>
#include"Graph.h"

CGameLogic::CGameLogic()
{

	m_nVexNum = 0;     //数组中实际元素的个数
	m_nCorner = 0;     //路径中的拐点个数
}


CGameLogic::~CGameLogic()
{
}

// 初始化游戏地图
void CGameLogic::InitMap(CGraph& graph)
{
	//游戏地图数组初始化
	srand((int)time(NULL));//设置种子
	
	//生成16种花色的地图
	int anTemp[MRow][MCol];
	int a = 0;//初始的第一张图片序号
	for (int j = 0; j < MCol; j++) {
		for (int i = 0; i < MRow; i++) {
			anTemp[i][j] = j;
		}
	}
	//打乱地图花色顺序
	for (int i = 0; i < MRow ; i++) {
		for (int j = 0; j < MCol; j++) {
			int i1 = rand() % MRow;
			int j1= rand() % MCol;
			//交换两个点的花色
			int t = anTemp[i][j];
			anTemp[i][j] = anTemp[i1][j1];
			anTemp[i1][j1] = t;
		}
	}
	
	//初始化顶点
	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {
			graph.AddVertex(anTemp[i][j]); 
		}
	}

	//初始化边
	for (int i = 0; i < MRow; i++) {
		for (int j = 0; j < MCol; j++) {
			UpdateArc(graph, i, j);
		}
	}

}

//生成图边数组
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nV1Index = nRow * MCol + nCol;

	if (nCol > 0) {//与左边的相连通
		int nV2Index = nV1Index - 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK) {
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nCol < MCol-1) {//与右边的相连通
		int nV2Index = nV1Index + 1;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK){
			graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow > 0) {//与正上方的相连通
		int nV2Index = nV1Index - MCol;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index) || graph.GetVertex(nV2Index) == BLANK || graph.GetVertex(nV1Index) == BLANK)
		{	graph.AddArc(nV1Index, nV2Index);
		}
	}

	if (nRow < MRow-1) {//与正下方的相连通
		int nV2Index = nV1Index + MCol;
		if (graph.GetVertex(nV2Index) == graph.GetVertex(nV1Index)|| graph.GetVertex(nV2Index)==BLANK|| graph.GetVertex(nV1Index) == BLANK)
		{graph.AddArc(nV1Index, nV2Index);
		}
	}
}
//向数组中添加一个元素
void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}


//向数组中删除一个元素
void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}

//消子
void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{
	//获得顶点索引号
	int nV1Index = v1.row * MCol + v1.col;
	int nV2Index = v2.row * MCol+ v2.col;
	//更新顶点
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);
	//更新边信息
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}

//获取连接路径
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

//连通判断
bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
	//获得顶点索引号
	int nV1Index = v1.row * MCol + v1.col;
	int nV2Index = v2.row * MCol+ v2.col;

	 //压入第一个点
	PushVertex(nV1Index); 

	//搜寻两点之间的连通路径
	if (SearchPath(graph, nV1Index, nV2Index) == true)
	{
		return true;
	}
	//取出压入的顶点
	PopVertex();
	return false;
}

//根据深度优先搜索算法判断是否连通
bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	//获取顶点数
	int nVexnum = graph.GetVexnum();

	//遍历图中nV0行，从0列到nVexnum列，值为true的点
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		if (graph.GetArc(nV0, nVi) && !IsExsit(nVi))
		{
			//压入当前顶点，假设为路径的一个有效顶点
			PushVertex(nVi);
			//当拐点数大于2 时
			if (m_nCorner > 2)
			{
				//取出压入的顶点
				PopVertex();          
				continue;
			}
			//当中间顶点不是nVi时，继续搜寻下一个相邻且相连通的顶点
			if (nVi != nV1)
			{
				//当中间顶点不为空时，表示该条路径不通
				if (graph.GetVertex(nVi) != BLANK)
				{	
					//取出压入的顶点
					PopVertex();      
					continue;
				}
				//如果nVi是一个已消除的点，则判断（nVi，nV1）是否连通
				if (SearchPath(graph, nVi, nV1))
				{
					return true;
				}
			}
			else//表示已经找到一条连通路径，则返回true
			{
				return true;
			}

			PopVertex();     //取出压入的顶点，与PushWertex()对应
		}
	}
	return false;
}

//判断该顶点保存到路径数组中
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi) return true;
	}
	return false;
}

//判断拐点的有效性
bool CGameLogic::IsCornor(void)
{
	//判断m_anPath数组中连续的3个顶点是否有一个拐点
	if (m_nVexNum >= 3)
	{
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2])
		{
			return true;
		}
	}
	return false;
}

//添加一个路径顶点
void CGameLogic::PushVertex(int nV)
{
	//将顶点压栈
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;

	//判断是否形成一个拐点
	if (IsCornor())
	{
		m_nCorner++;
	}
}

//取出一个路径顶点
void CGameLogic::PopVertex()
{
	//判断是否是拐点，如果是，则减少拐点数
	if (IsCornor())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}

//判断图中的所有的顶点是否为空，如果都为空，则返回true；否则，返回false
bool CGameLogic::IsBlank(CGraph& graph)
{
	int nVexnum = graph.GetVexnum();//获取顶点数组中的顶点数
	for (int i = 0; i < nVexnum; i++) {
		if (graph.GetVertex(i) != BLANK) return false;//获取顶点数组中索引为nIndex的顶点
	}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph& graph)
{
	//得到顶点数
	int nVexnum = graph.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//得到第一个非空顶点
		if (graph.GetVertex(i) == BLANK)continue;
		//得到第二个非同一个顶点
		for (int j = 0; j < nVexnum; j++)
		{
			if (i != j)
			{
				if (graph.GetVertex(i) == graph.GetVertex(j))//第i个点和第j个点同色
				{
					//压入第一个点
					PushVertex(i);
					if (SearchPath(graph, i, j) == true)//能够连通
					{
						return true;
					}
					//取出压入的顶点时，与PushVertex(i)对应
					PopVertex();
				}

			}
		}
	}
	return false;
}

//随机任选地图中两个顶点，将元素进行交换，这样进行100次
void CGameLogic::ResetGraph(CGraph& graph)
{
	//设置种子
	srand((int)time(NULL));
	//随机交换两个顶点的值
	for (int i = 0; i < 100; i++)
	{
		//随机得到两个坐标
		int n1 = rand() % MAX_VERTEX_NUM;
		int n2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		graph.Change(n1, n2);
	}

	//更新弧信息
	for (int i = 0; i < MRow; i++)
	{
		for (int j = 0; j < MCol; j++)
		{
			UpdateArc(graph, i, j);
		}
	}

}