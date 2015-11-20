#include "stdafx.h"
#include "Graph.h"
#include <fstream>
using namespace std;

void Graph::Init()
{
	fstream vexReader;                                                         //���붥����Ϣ��m_aVexs��
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

	Edge edge;                                                                 //�������Ϣ���ڽӾ���m_aAdjMatrix��
	fstream edgeReader;
	edgeReader.open("D:\\Data Structure\\TouristAttractions\\Graph\\Edge.txt", ios::in);
	while (!edgeReader.eof())
	{
		if (edgeReader.fail())
			break;
		edgeReader >> edge.vex1;
		edgeReader >> edge.vex2;
		edgeReader >> edge.weight;
		m_aAdjMatrix[edge.vex1][edge.vex2] = edge.weight;                      //����ڽӾ����ǶԳƵ� �洢��������ľ���
		m_aAdjMatrix[edge.vex2][edge.vex1] = edge.weight;
	}
	edgeReader.close();
}

CString Graph::QueryVexInfo(int nVex)
{
	CString info;
	CString temp;
	temp = m_aVexs[nVex].name;                                                 //������
	info = temp + _T("\r\n");
	temp = m_aVexs[nVex].desc;                                                 //Ʊ������
	info += temp + _T("\r\n�����ľ�����:\r\n");                                 //��������
	for (int i = 0; i < 7; i++)
	{
		if (m_aAdjMatrix[nVex][i] != 0)
		{
			temp = m_aVexs[i].name;                                            //����������
			info += temp + _T(" ���� ");
			temp.Format(_T("%d"), m_aAdjMatrix[nVex][i]);                      //����������ľ���
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
	info = _T("��") + temp + _T("��ʼ�����к��ܶ��ٵ�·��:\r\n");
	m_aVexs[nVex].parent = 7;                                                  //����parent��Ϊ7
	Graph::DFS(nVex, 1, info);
	return info;
}

void Graph::DFS(int nVex, int nDepth, CString &info)
{
	if (nDepth == 7)                                                           //���Ϊ7 ����һ�����ܶ��ٵ�·
	{
		while (!m_stack.empty())                                               //�����ջ
			m_stack.pop();

		while (m_aVexs[nVex].parent != 7 && m_aVexs[nVex].parent != -1)        //�����ջ��
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
		for (int i = 0; i < 7; i++)                                            //��ǰ�������ĸ��� үү����visited��Ϊ1
		{
			m_aVisited[i] = 0;
		}
		int num = nVex;
		while (m_aVexs[num].parent != 7)
		{
			num = m_aVexs[num].parent;
			m_aVisited[num] = 1;
		}
		m_aVisited[nVex] = 1;                                                  //������visited����0
		for (int i = 0; i < 7; i++)
		{
			if (m_aVisited[i] == 0)
				m_aVexs[i].parent = -1;                                        //�����ǵ�parentҲ����Ϊ-1
		}

		//-------------------------------------------------------------------------------------------------------------

		if (m_aAdjMatrix[nVex][i] != 0 && m_aVisited[i] == 0)
		{
			m_aVexs[i].parent = nVex;
			Graph::DFS(i, nDepth + 1, info);                                     //�ݹ�
		}
	}
	return;
}

CString Graph::FindMinTree(int nVex)                                           //�õ���Prim�㷨
{
	for (int i = 0; i < 7; i++)
		m_aVisited[i] = 0;

	CString info;
	CString temp;
	info = _T("��С������������:\r\n");

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
	info += _T("�ܳ���Ϊ") + temp + _T("m\r\n");
	return info;
}

void Graph::MinRoad(int &a, int &b)                                            //a�Ƿ��ʹ��� b��û�з��ʹ���
{
	int i, j, min = 2000;
	for (i = 0; i < 7; i++)
	{
		for (j = i + 1; j < 7; j++)                                              //�Գƾ��� ֻ�����ϰ�����
		{                                                                      //i���ʹ� jû�� ��ij���е�·
			if (m_aVisited[i] == 1 && m_aVisited[j] == 0 && m_aAdjMatrix[i][j] != 0)
			{
				min = m_aAdjMatrix[i][j];
				a = i;
				b = j;
				break;
			}                                                                  //j���ʹ� iû�� ��ij���е�·
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
						a = i;                                                     //a��ʾ�Ѿ����ʹ������
						b = j;                                                     //b��ʾ���ڱ����ʵ����
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

CString Graph::FindShortPath(int nVexStart, int nVexEnd)                       //Floyd�㷨
{                                                                              //http://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html
	CString info;
	CString temp;
	if (nVexStart == nVexEnd)
	{
		temp = m_aVexs[nVexStart].name;
		info = temp + _T("���Լ������·�����ȵ�Ȼ��0\r\n");
		return info;
	}

	temp = m_aVexs[nVexStart].name;
	info = temp + _T("��");
	temp = m_aVexs[nVexEnd].name;
	info += temp + _T("�����·��Ϊ:\r\n");

	int copy[7][7];
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_aAdjMatrix[i][j] == 0)
			{
				copy[i][j] = 10000;                                            //����һ����˵�㹻����
				path[i][j] = -2;                                               //-2��ʾ��ֱ����ͨ
			}
			else
			{
				copy[i][j] = m_aAdjMatrix[i][j];
				path[i][j] = -1;                                               //-1��ʾֱ����ͨ
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
		m_aVexs[i].parent = -1;                                                //���������������֮ǰ��Ŀ��parent�Ѽ�����������
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
	Graph::InsertVex(min, max);                                                //С�ķ�ǰ���
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
	info += _T("���·����Ϊ") + temp + _T("m\r\n");
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
		Graph::InsertVex(a, temp);                                             //�ݹ�
		m_aVexs[temp].parent = b;
		Graph::InsertVex(temp, b);
	}
	return;
}
