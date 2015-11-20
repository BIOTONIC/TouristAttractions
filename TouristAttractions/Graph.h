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
		//��Ҳ��֪��������ʲô
	};
	int m_aAdjMatrix[7][7] = { 0 };                                            //�������� m��ʾ��Ա���� a��ʾ����
	Vex m_aVexs[7] = { 0 };                                                    //���������ֱ������ȫ����ʼ��Ϊ0
	int m_nVexNum;                                                             //n��ʾint
	stack<int> m_stack;                                                        //��¼���ܶ��ٵ�·��ջ
	int path[7][7];                                                            //��¼����֮��Ӧ��ͨ��˭��������� ֱ�����������Ϊ-1
	int m_aVisited[7] = { 0 };                                                 //���ʹ� ��Ϊ1 ����Ϊ0
	void DFS(int nVex, int nDepth, CString &);
	void MinRoad(int &a, int &b);                                              //��һ�˷��ʹ� һ��û�з��ʵĵ�·��ѡȡ��̵���һ�� ���������˵�
	void InsertVex(int a, int b);

public:
	void Init();
	CString QueryVexInfo(int nVex);
	CString DFSTranverse(int nVex);
	CString FindMinTree(int nVex);
	CString FindShortPath(int nVexStart, int nVexEnd);
};
