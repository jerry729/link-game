#pragma once
//保存游戏地图中的点
typedef struct tagVertex
{
	int row;     //行
	int col;     //列
	int info;    //信息类
}Vertex;

#define BLANK -1
const int  MRow = 10;//初始行数10行
const int  MCol = 16;//初始行数16列
const int  Mpic = 20;//初始花色20种