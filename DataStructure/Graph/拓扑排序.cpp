//以邻接矩阵表示的有向图
//在有向图中进行拓扑排序

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define VertexType char
#define VRType int
typedef struct ArcCell
{
	VRType adj;             //顶点关系
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	char vexs[MAX_VERTEX_NUM];        //顶点数组
	AdjMatrix arcs;                    //矩阵
	int vexnum,arcnum;           //顶点数和弧数
}MGraph;

typedef struct nn
{
	int* base,* top;
}Stack;

void InitStack(Stack &S)
{
	S.base = (int *)malloc(20 * sizeof(int));
	S.top = S.base;
}

void push(Stack &S, int i)
{
	*S.top = i;
	++S.top;
}
int pop(Stack &S)
{
	int temp;
	--S.top;
	temp = *S.top;
	return temp;
}

int StackEmpty(Stack S)
{
	if(S.top != S.base) return 1;
	else return 0;
}

int LocateVex(MGraph G, VertexType c)           //定位顶点
{
	int i;
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.vexs[i] == c) return i;
		else continue;
	}
}

void CreateDG(MGraph &G)          //创建有向图
{
	int IncInfo,i = 0,j,k;
	VertexType v1,v2;
	printf("请输入有向图信息(顶点数、边数):");
	scanf_s("%d%d",&G.vexnum,&G.arcnum);
//	printf("请输入各点信息:");
	getchar();
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf_s("%c",&G.vexs[i]);
	}
	for(i = 0; i < G.vexnum; ++i)
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;
		}
//	printf("请输入有关系的两点:");
	getchar();
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%c%c",&v1,&v2);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = 1;
	}
}

int Come(MGraph G, int k)     //算入度
{
	int i,j = 0;
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.arcs[i][k].adj != 0) ++j;
	}
	return j;
}

int FirstAdjVex(MGraph G, int v)        //寻找第一邻接点
{
	if(v < 0 || v > G.vexnum)
	{
		printf("输入数据错误!\n");
		system("pause");
		return 0;
	}
	int i;
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.arcs[v][i].adj != 0) return i;
	}
	return 0;
}

void TopoLogic(MGraph &G)    //拓扑排序
{
	Stack S;
	InitStack(S);
	int i,j = 0,k,temp = 0;
	int cc[20];
	for(i = 0; i < G.vexnum; ++i)          //首先寻找一轮入度为0的点
	{
		if(Come(G,i) == 0) push(S,i);       //入度为0压栈
		cc[i] = Come(G,i);              //存入入度
	}
	while(StackEmpty(S) == 1)      //栈非空
	{
		j = pop(S);              //出栈一个点
		++temp;              //已出栈点数自增1
		printf("%c",G.vexs[j]);           //输出点
		for(k = 0; k < G.vexnum; ++k)         //看由j点出发的点的临接情况
		{
			if(G.arcs[j][k].adj != 0)         //如果某点与之邻接
			{
				--cc[k];           //则其入度减1
				if(cc[k] == 0) push(S,k);             //减1后，如果入度为0则压栈
			}
		}
	}
	if(temp != G.vexnum) printf("\n图中存在环\n");        //如果栈空且还有点没有排序
}

void Show(MGraph G)         //展示邻接矩阵
{
	printf("\n");
	int i,j;
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			printf("%3d",G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

int main()
{
	MGraph G;
	CreateDG(G);
	Show(G);
	TopoLogic(G);
	system("pause");
	return 0;
	// 8 10 abcdefgh acagcddgdebgbhgfhffe
}
