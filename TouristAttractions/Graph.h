#pragma once
#include <stack>
using namespace std;

class Graph
{
private:
	struct Vex
	{
		int num;
		int parent;
		char name[10];
		char desc[20];
	};
	struct Edge
	{
		int vex1;
		int vex2;
		int weight;
	};
	struct PathList
	{
		//我也不知道里面填什么
	};
	int m_aAdjMatrix[7][7] = { 0 };                                            //命名规则 m表示成员变量 a表示数组
	Vex m_aVexs[7] = { 0 };                                                    //声明后可以直接这样全部初始化为0
	int m_nVexNum;                                                             //n表示int
	stack<int> m_stack;                                                        //记录汉密尔顿道路的栈
	int path[7][7];                                                            //记录两点之间应该通过谁相连会最短 直接相连最短则为-1
	int m_aVisited[7] = { 0 };                                                 //访问过 记为1 否则为0
	void DFS(int nVex, int nDepth, CString &);
	void MinRoad(int &a, int &b);                                              //在一端访问过 一端没有访问的道路里选取最短的那一条 返回两个端点
	void InsertVex(int a, int b);

public:
	void Init();
	CString QueryVexInfo(int nVex);
	CString DFSTranverse(int nVex);
	CString FindMinTree(int nVex);
	CString FindShortPath(int nVexStart, int nVexEnd);
};
