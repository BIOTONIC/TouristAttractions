#include "stdafx.h"
#include "Graph.h"
#include <fstream>
using namespace std;

void Graph::Init()
{
	fstream vexReader;                                                         //读入顶点信息到m_aVexs中
	vexReader.open("D:\\Data Structure\\TouristAttractions\\Graph\\Vex.txt", ios::in);
	vexReader >> m_nVexNum;
	for (int i = 0; i < m_nVexNum; i++)
	{
		vexReader >> m_aVexs[i].num;
		vexReader >> m_aVexs[i].name;
		vexReader >> m_aVexs[i].desc;
		m_aVexs[i].parent = -1;
	}
	vexReader.close();

	Edge edge;                                                                 //读入边信息到邻接矩阵m_aAdjMatrix中
	fstream edgeReader;
	edgeReader.open("D:\\Data Structure\\TouristAttractions\\Graph\\Edge.txt", ios::in);
	while (!edgeReader.eof())
	{
		if (edgeReader.fail())
			break;
		edgeReader >> edge.vex1;
		edgeReader >> edge.vex2;
		edgeReader >> edge.weight;
		m_aAdjMatrix[edge.vex1][edge.vex2] = edge.weight;                      //这个邻接矩阵是对称的 存储的是两点的距离
		m_aAdjMatrix[edge.vex2][edge.vex1] = edge.weight;
	}
	edgeReader.close();
}

CString Graph::QueryVexInfo(int nVex)
{
	CString info;
	CString temp;
	temp = m_aVexs[nVex].name;                                                 //顶点名
	info = temp + _T("\r\n");
	temp = m_aVexs[nVex].desc;                                                 //票价描述
	info += temp + _T("\r\n附近的景点有:\r\n");                                 //附近景点
	for (int i = 0; i < 7; i++)
	{
		if (m_aAdjMatrix[nVex][i] != 0)
		{
			temp = m_aVexs[i].name;                                            //附近景点名
			info += temp + _T(" 距离 ");
			temp.Format(_T("%d"), m_aAdjMatrix[nVex][i]);                      //到附近景点的距离
			info += temp + _T("m\r\n");
		}
	}
	return info;
}

CString Graph::DFSTranverse(int nVex)
{
	for (int i = 0; i < 7; i++)
	{
		m_aVexs[i].parent = -1;
		m_aVisited[i] = 0;
	}

	CString info;
	CString temp;
	temp = m_aVexs[nVex].name;
	info = _T("从") + temp + _T("开始的所有汉密尔顿道路有:\r\n");
	m_aVexs[nVex].parent = 7;                                                  //根的parent设为7
	Graph::DFS(nVex, 1, info);
	return info;
}

void Graph::DFS(int nVex, int nDepth, CString &info)
{
	if (nDepth == 7)                                                           //深度为7 这是一个汉密尔顿道路
	{
		while (!m_stack.empty())                                               //先清空栈
			m_stack.pop();

		while (m_aVexs[nVex].parent != 7 && m_aVexs[nVex].parent != -1)        //都填到堆栈中
		{
			m_stack.push(nVex);
			nVex = m_aVexs[nVex].parent;
		}
		m_stack.push(nVex);

		int num;
		CString temp;
		while (!m_stack.empty())
		{
			num = m_stack.top();
			temp = m_aVexs[num].name;
			info += _T(" - ") + temp;
			m_stack.pop();
		}
		info += _T("\r\n");
		return;
	}

	//-----------------------------------------------------------------------------------------------------------------

	for (int i = 0; i < 7; i++)
	{
		for (int i = 0; i < 7; i++)                                            //当前结点和它的父辈 爷爷辈等visited改为1
		{
			m_aVisited[i] = 0;
		}
		int num = nVex;
		while (m_aVexs[num].parent != 7)
		{
			num = m_aVexs[num].parent;
			m_aVisited[num] = 1;
		}
		m_aVisited[nVex] = 1;                                                  //其他的visited还是0
		for (int i = 0; i < 7; i++)
		{
			if (m_aVisited[i] == 0)
				m_aVexs[i].parent = -1;                                        //且他们的parent也都变为-1
		}

		//-------------------------------------------------------------------------------------------------------------

		if (m_aAdjMatrix[nVex][i] != 0 && m_aVisited[i] == 0)
		{
			m_aVexs[i].parent = nVex;
			Graph::DFS(i, nDepth + 1, info);                                     //递归
		}
	}
	return;
}

CString Graph::FindMinTree(int nVex)                                           //用的是Prim算法
{
	for (int i = 0; i < 7; i++)
		m_aVisited[i] = 0;

	CString info;
	CString temp;
	info = _T("最小生成树可以是:\r\n");

	int a = -1, b = -1, sum = 0;
	m_aVisited[nVex] = 1;
	for (int i = 0; i < 6; i++)
	{
		Graph::MinRoad(a, b);
		m_aVisited[b] = 1;
		temp = m_aVexs[a].name;
		info += temp + _T(" - ");
		temp = m_aVexs[b].name;
		info += temp + _T(" ");
		temp.Format(_T("%d"), m_aAdjMatrix[a][b]);
		info += temp + _T("m\r\n");
		sum += m_aAdjMatrix[a][b];
	}
	temp.Format(_T("%d"), sum);
	info += _T("总长度为") + temp + _T("m\r\n");
	return info;
}

void Graph::MinRoad(int &a, int &b)                                            //a是访问过的 b是没有访问过的
{
	int i, j, min = 2000;
	for (i = 0; i < 7; i++)
	{
		for (j = i + 1; j < 7; j++)                                              //对称矩阵 只遍历上半三角
		{                                                                      //i访问过 j没有 且ij间有道路
			if (m_aVisited[i] == 1 && m_aVisited[j] == 0 && m_aAdjMatrix[i][j] != 0)
			{
				min = m_aAdjMatrix[i][j];
				a = i;
				b = j;
				break;
			}                                                                  //j访问过 i没有 且ij间有道路
			else if (m_aVisited[i] == 0 && m_aVisited[j] == 1 && m_aAdjMatrix[i][j] != 0)
			{
				min = m_aAdjMatrix[i][j];
				a = j;
				b = i;
				break;
			}
		}
		if ((m_aVisited[i] == 1 && m_aVisited[j] == 0 && m_aAdjMatrix[i][j] != 0)
			|| (m_aVisited[i] == 0 && m_aVisited[j] == 1 && m_aAdjMatrix[i][j] != 0))
		{
			break;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------

	for (i = 0; i < 7; i++)
	{
		for (j = i + 1; j < 7; j++)
		{
			if (m_aAdjMatrix[i][j] != 0)
			{
				if (m_aVisited[i] == 1 && m_aVisited[j] == 0)
				{
					if (m_aAdjMatrix[i][j] < min)
					{
						min = m_aAdjMatrix[i][j];
						a = i;                                                     //a表示已经访问过的序号
						b = j;                                                     //b表示正在被访问的序号
					}
				}
				else if (m_aVisited[i] == 0 && m_aVisited[j] == 1)
				{
					if (m_aAdjMatrix[i][j] < min)
					{
						min = m_aAdjMatrix[i][j];
						a = j;
						b = i;
					}
				}
			}
		}
	}
	return;
}

CString Graph::FindShortPath(int nVexStart, int nVexEnd)                       //Floyd算法
{                                                                              //http://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html
	CString info;
	CString temp;
	if (nVexStart == nVexEnd)
	{
		temp = m_aVexs[nVexStart].name;
		info = temp + _T("到自己的最短路径长度当然是0\r\n");
		return info;
	}

	temp = m_aVexs[nVexStart].name;
	info = temp + _T("到");
	temp = m_aVexs[nVexEnd].name;
	info += temp + _T("的最短路径为:\r\n");

	int copy[7][7];
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_aAdjMatrix[i][j] == 0)
			{
				copy[i][j] = 10000;                                            //对这一题来说足够大了
				path[i][j] = -2;                                               //-2表示不直接连通
			}
			else
			{
				copy[i][j] = m_aAdjMatrix[i][j];
				path[i][j] = -1;                                               //-1表示直接连通
			}
		}
	}
	for (int k = 0; k < 7; k++)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (copy[i][j]>(copy[i][k] + copy[k][j]))
				{
					copy[i][j] = copy[i][k] + copy[k][j];
					path[i][j] = k;
				}
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		m_aVexs[i].parent = -1;                                                //看我如何巧妙利用之前题目的parent把几个点连起来
	}

	int min, max, cur, sum = 0;
	if (nVexStart > nVexEnd)
	{
		min = nVexEnd;
		max = nVexStart;
	}
	else
	{
		min = nVexStart;
		max = nVexEnd;
	}
	Graph::InsertVex(min, max);                                                //小的放前面吧
	cur = m_aVexs[min].parent;
	while (cur != -1)
	{
		temp = m_aVexs[min].name;
		info += temp + _T(" - ");
		temp = m_aVexs[cur].name;
		info += temp + _T(" ");
		temp.Format(_T("%d"), m_aAdjMatrix[min][cur]);
		sum += m_aAdjMatrix[min][cur];
		info += temp + _T("m\r\n");
		min = cur;
		cur = m_aVexs[cur].parent;
	}
	temp.Format(_T("%d"), sum);
	info += _T("最短路径长为") + temp + _T("m\r\n");
	return info;
}

void Graph::InsertVex(int a, int b)
{
	int temp = path[a][b];
	if (temp == -1)
	{
		m_aVexs[a].parent = b;
		return;
	}
	else
	{
		m_aVexs[a].parent = temp;
		Graph::InsertVex(a, temp);                                             //递归
		m_aVexs[temp].parent = b;
		Graph::InsertVex(temp, b);
	}
	return;
}
