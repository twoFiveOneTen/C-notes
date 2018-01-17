//包含以邻接矩阵存储形式的图的13种基本操作
//程序末尾包含四种输入
#include <stdio.h>
#include <stdlib.h>

#define INFINITY INT_MAX         //最大值∞
#define ∞ 0
#define VRType int
#define InfoType char
#define VertexType char
#define MAX_VERTEX_NUM 20         //最大顶点个数
#define FALSE 0
#define TRUE 1
typedef enum{DG,DN,UDG,UDN} GraphKind;

typedef struct node
{
	int i;
	struct node *next;
}node;

typedef struct qnode
{
	int i;
	struct qnode *next;
}qnode;
typedef struct StackNode
{
	node *base,*top;
}Stack;

void InitStack(Stack &S)
{
	S.base = (node *)malloc(20 * sizeof(node));
	S.top = S.base;
}

void push(Stack &S, VertexType v, int i)
{
	S.top->i = i;
}
node pop(Stack &S)
{
	node temp;
	--S.top;
	temp.i = S.top->i;
	return temp;
}

int StackEmpty(Stack S)
{
	if(S.top != S.base) return 1;
	else return 0;
}

typedef struct
{
	qnode *front;
	qnode *rear;
}Queue;

void InitQueue(Queue &Q)
{
	Q.rear = Q.front = (qnode *)malloc(sizeof(qnode));
	Q.front->next = NULL;
}

int QueueEmpty(Queue Q)
{
	if(Q.rear == Q.front) return 1;
	else return 0;
}

void EnQueue(Queue &Q, int v)
{
//	printf("准备队列插入%d\n",v);
	qnode *q;
	q = (qnode *)malloc(sizeof(qnode));
	q->i = v;
	q->next = NULL;
	Q.rear->next = q;
	Q.rear = q;
//	printf("队列插入%d成功\n",v);
}

int DeQueue(Queue &Q, int &u)
{
	if(Q.front == Q.rear)
	{
		printf("空队列无法删除！！！\n");
		return -1;
	}
	qnode *p;
	p = Q.front->next;
	u = p->i;
	if(p == Q.rear) Q.rear = Q.front;
	Q.front->next = p->next;
	free(p);
	return u;
}

void ShowQueue(Queue Q)
{
	if(Q.front == Q.rear)
	{
		printf("空对列不可\n");
		return;
	}
	printf("队列内容是:");
	qnode *p;
	p = Q.front->next;
	while(p != NULL)
	{
		printf("%d ",p->i);
		p = p->next;
	}
	printf("\n");
}

typedef struct ArcCell
{
	VRType adj;             //顶点关系
	InfoType *info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	char vexs[MAX_VERTEX_NUM];        //顶点数组
	AdjMatrix arcs;                    //矩阵
	int vexnum,arcnum;           //顶点数和弧数
	GraphKind kind;            //图的种类
}MGraph;

int LocateVex(MGraph G, VertexType c)           //定位顶点
{
	int i;
	for(i = 0; i < G.vexnum; ++i)
	{
		if(G.vexs[i] == c) return i;
		else continue;
	}
}

void Input(InfoType *info, int i, int j)
{
	char ch[100],c = 'a';
	int k;
	printf("请输入%d-%d边信息('#'终止)：",i,j);
	for(k = 0; k < 100; ++k) 
	{
		scanf("%c",&c);
		if(c == '#') break;
		ch[k] = c;
	}
	info = ch;
}

void CreateDG(MGraph &G)          //创建有向图
{
	int IncInfo,i = 0,j,k;
	VertexType v1,v2;
//	printf("请输入有向图信息(顶点数、边数、边有无信息):");
	scanf_s("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
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
			G.arcs[i][j].info = NULL;
		}
//	printf("请输入有关系的两点:");
	getchar();
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%c%c",&v1,&v2);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = 1;
		if(IncInfo) Input(G.arcs[i][j].info,i,j);
	}
}

void CreateDN(MGraph &G)         //创建有向网
{
	int IncInfo,i,j,k,w;
	VertexType v1,v2;
//	printf("请输入有向网信息(顶点数、边数、边有无信息):");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
//	printf("请输入各点信息:");
	getchar();
	for(i = 0; i < G.vexnum; ++i) scanf("%c",&G.vexs[i]);
	for(i = 0; i < G.vexnum; ++i)
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
//	printf("请输入有关系的两点及其关系:");
	getchar();
	for(k = 0; k < G.arcnum; ++k)
	{
		
		scanf("%c%c%d",&v1,&v2,&w);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = w;
		if(IncInfo) Input(G.arcs[i][j].info,i,j);
	}
}

void CreateUDG(MGraph &G)              //创建无向图
{
	int IncInfo,i,j,k;
	VertexType v1,v2;
//	printf("请输入无向图信息(顶点数、边数、边有无信息):");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
//	printf("请输入各点信息:");
	getchar();
	for(i = 0; i < G.vexnum; ++i) scanf("%c",&G.vexs[i]);
	for(i = 0; i < G.vexnum; ++i)
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
//	printf("请输入有关系的两点:");
	getchar();
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%c%c",&v1,&v2);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;
		if(IncInfo) Input(G.arcs[i][j].info,i,j);
	}
}

void CreateUDN(MGraph &G)        //创建无向网
{
	int IncInfo,i,j,k,w;
	VertexType v1,v2;
//	printf("请输入无向网信息(顶点数、边数、边有无信息):");
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
//	printf("请输入各点信息:");
	getchar();
	for(i = 0; i < G.vexnum; ++i) scanf("%c",&G.vexs[i]);
	for(i = 0; i < G.vexnum; ++i)
		for(j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
//	printf("请输入有关系的两点及其关系:");
	getchar();
	for(k = 0; k < G.arcnum; ++k)
	{
		scanf("%c%c%d",&v1,&v2,&w);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		G.arcs[i][j].adj = G.arcs[j][i].adj = w;
		if(IncInfo) Input(G.arcs[i][j].info,i,j);
	}
}

void CreateGraph(MGraph &G)            //创建图或网
{
	printf("请输入创建图类型:");
	scanf("%d",&G.kind);
	switch(G.kind)
	{
		case DG:
			CreateDG(G);
			break;
		case DN:
			CreateDN(G);
			break;
		case UDG:
			CreateUDG(G);
			break;
		case UDN:
			CreateUDN(G);
			break;
		default:
			break;
	}
}

void DestroyGraph(MGraph &G)          //销毁图
{
//	free(G.arcs);
//	free(G.vexs);
}

VertexType GetVex(MGraph G, int v)             //返回指定顶点值
{
	if(v <= 0 || v > G.vexnum)
	{
		printf("输入数据错误!\n");
		return 0;
	}
	return G.vexs[v - 1];
}

void PutVex(MGraph &G, int v, VertexType value)           //给指定顶点赋值
{
	if(v <= 0 || v > G.vexnum)
	{
		printf("输入数据错误!\n");
		return;
	}
	G.vexs[v - 1] = value;
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

int NextAdjVex(MGraph G, int v, int w)        //寻找下一邻接点
{
	if(v < 0 || v > G.vexnum)
	{
		printf("输入数据错误!\n");
		return -1;
	}
	int i,j = 0;
	for(i = w + 1; i < G.vexnum; ++i)
	{
		if(G.arcs[v][i].adj != 0) return i;
	}
	return -1;
}

void Show(MGraph G)
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

void ShowVex(MGraph G)
{
	printf("点是：");
	int i = G.vexnum,j;
	for(j = 0; j < G.vexnum; ++j)
	{
		printf("%c",G.vexs[j]);
	}
}

void visit(VertexType ch)
{
	printf("%c",ch);
}

int Find(int a[], int x)
{
	int i;
	for(i = 0; i < 20; ++i)
	{
		if(a[i] == x) return 1;
	}
	return 0;
}

void DFSTraverse(MGraph G, void visit(VertexType c))
{
	printf("深度优先遍历:");
	int i = 0,j,record[20],k = 0;
	for(j = 0; j < 20; ++j) record[j] = -1;
	Stack S;
	node n;
	InitStack(S);
	while(k < G.vexnum)
	{
		for(i = 0; i < G.vexnum; ++i)
		{
			if(Find(record,i) == 1) continue;         //如果已遍历
			else
			{
				visit(G.vexs[i]);
				record[k] = i;
				push(S,G.vexs[i],i);
				++k;
				break;
			}
		}
		while(1)
		{
			j = 0;
			while(j != G.vexnum)
			{
				for(j = 0; j < G.vexnum; ++j)     //看本顶点所邻接的点
				{
					if(G.arcs[i][j].adj != 0 && Find(record,j) == 0)    //如果邻接且未遍历
					{
						visit(G.vexs[j]);       //遍历
						push(S,G.vexs[j],j);     //入栈
						record[k] = j;        //记录
						++k;
						i = j;              //变换
						break;
					}
				}
			}
			if(j == G.vexnum)         //如果某次j循环到了最后一个顶点
			{
				if(StackEmpty(S) == 0) break;
				n = pop(S);           //看上一个点
				i = n.i;         //变换
			}
		}
	}
	printf("\n");
}

void BFSTraverse(MGraph G, void visit(VertexType c))
{
	printf("广度优先遍历:");
	int visited[20],v,u,w;
	Queue Q;
	InitQueue(Q);
	for(v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;
	for(v = 0; v < G.vexnum; ++v)
		if(!visited[v])
		{
			visited[v] = TRUE;
			visit(G.vexs[v]);
			EnQueue(Q,v);
			while(!QueueEmpty(Q))
			{
				DeQueue(Q,u);
				for(w = FirstAdjVex(G,u); w >= 0; w = NextAdjVex(G,u,w))
					if(!visited[w])
					{
						visited[w] = TRUE;
						visit(G.vexs[w]);
						EnQueue(Q,w);
					}
			}
		}
		printf("\n");
}

int main()
{
	MGraph G;
	CreateGraph(G);
	Show(G);
	DFSTraverse(G,visit);
	BFSTraverse(G,visit);
	system("pause");
	return 0;
	//0：有向图：0 5 10 0 abcde abadbccadadcdeebeced
	//1:有向网：1 6 10 0 abcdef ab5ad7bc4ca8cf9dc5df6ed5fa3fe1
	//2:无向图：2 8 9 0 abcdefgh abacbdbecfcgfgdheh
	//3:无向网：3 6 7 0 abcdef ab5bc4ca8cf9dc5ed5fe1
}
