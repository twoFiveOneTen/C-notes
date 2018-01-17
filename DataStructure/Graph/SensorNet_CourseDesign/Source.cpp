/*
在一个直角坐标（设为100*100）平面中，随机分布n无线传感器结点，汇聚点为原点（0，0），要求将每个无线传感器结点的信息传输到汇聚点，传输可以通过多跳方式实现，设无线传感器结点最大无线通信距离为10，传输能耗与距离平方成正比，传输时间与距离成正比。
问题一：建立每个结点传输到汇聚点的最短时间通道，并给无法实现传输的结点，将其排除。
问题二：建立整个网络传输到汇聚点的平均能耗最小网络结构。
[基本要求]
输入格式： 输入的第一行包含一个正整数n，表示无线传感器结点数量。结点使用1, 2, 3, ……n依次标号。  接下来n行，每行包含三个整数ni, xi, yi，其中xi, yi表示第ni个结点的坐标，要求从文本文件中输入。
输出格式：
问题一：输出每个结点到汇聚点的最短时间通道，包括最短时间和经过结点。  
问题二：输出整个网络到汇聚点的平均能耗最小网络结构，包括平均最小能耗和连接方式。
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAPSIZE 100
#define Vertex double
#define VERNUM 22
#define ∞ 999999
#define FALSE 0
#define TRUE 1

typedef struct
{
	int code;
	int x, y;
}VertexType;

typedef struct ArcCell
{
	Vertex adj;             //顶点关系
}ArcCell, AdjMatrix[VERNUM+1][VERNUM+1];


typedef struct
{
	VertexType vexs[VERNUM+1];        //顶点数组
	AdjMatrix arcs;                    //矩阵
	int vexnum,arcnum;           //顶点数和弧数
}MGraph;

void CreateUDN(MGraph &G)        //创建无向网
{
	int i,j;
	FILE* fp;
	fp = fopen("data.txt","r");
	fscanf(fp,"%d",&G.vexnum);
	++G.vexnum;
	G.vexs[0].code = 0;
	G.vexs[0].x = 0;
	G.vexs[0].y = 0;
	int x = 0,y = 0,tag = 0,num = 1;
	for(i = 0; i < G.vexnum; ++i)
		for(j = 0; j < G.vexnum; ++j)
			G.arcs[i][j].adj = ∞;
	fscanf(fp,"%d%d%d",&tag, &x, &y);
	while(!feof(fp))
	{
		G.vexs[num].code = tag;
		G.vexs[num].x = x;
		G.vexs[num].y = y;
		++num;
		fscanf(fp,"%d%d%d",&tag, &x, &y);
		while(x + y == 0)
		{
			fscanf(fp,"%d%d%d",&tag, &x, &y);
		}
	}
	double temp;
	for(i = 0; i < G.vexnum; ++i)
		for(j = 0; j < G.vexnum; ++j)
		{
			if(i == j)
			{
				G.arcs[i][j].adj = ∞;
				continue;
			}
			temp = (double)sqrt(pow(((double)G.vexs[i].x - (double)G.vexs[j].x),2) + 
				pow(((double)G.vexs[i].y - (double)G.vexs[j].y),2));
			if(temp <= 10)
			{
				G.arcs[i][j].adj = temp;
				G.arcs[j][i].adj = temp;
			}
		}
	fclose(fp);
}

void Show(MGraph G)
{
	printf("\n");
	int i,j;
	for(i = 0; i <= G.vexnum; ++i)
	{
		printf("%2d:",G.vexs[i].code);
		for(j = 0; j <= G.vexnum; ++j)
		{
			if(G.arcs[i][j].adj == ∞) printf("  ∞  ");
			else printf("[i][j]%4.2f",G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

void writeFile()
{
	FILE* fp;
	fp = fopen("data.txt","w");
	int i,l,m,j,k;
	fprintf(fp,"%d\n",VERNUM);
	for(i = 0; i < VERNUM; ++i)
	{
		j = rand()%(MAPSIZE-2) + 2;
		k = rand()%(MAPSIZE-3) + 3;
		l = rand()%j;
		m = rand()%k;
		fprintf(fp,"%d %d %d\n",i + 1,l,m);
	}
	fclose(fp);
	
}

int MiniCost(MGraph G, int i, int visited3[], int m)       //最小花费
{
	int j, l = 11;
	double k = 100 ;
	for(j = 0; j < G.vexnum; ++j)
	{
		if(G.arcs[i][j].adj != ∞)       //如果与此点邻接
			if(visited3[j] == m)          //如果此点已/未（1/0）处理
				if(G.arcs[i][j].adj < k)      //寻找最短邻接点
				{
					
					k = G.arcs[i][j].adj;
					l = j;
				}
				else continue;
			else continue;
		else continue;
	}
	if(k == 100) return -1;         //如果没有未处理的邻接点
	else return l;       //否则返回最短临界点值
}

int MiniCost2(MGraph G, int visited[], int visited3[])
{
	double record[VERNUM+1], temp = 100;
	int i, l = -1;
	for(i = 0; visited[i] != -1; ++i)
	{
		if(MiniCost(G, visited[i], visited3, 0) != -1)
			record[i] = G.arcs[visited[i]][MiniCost(G, visited[i], visited3, 0)].adj;
		else record[i] = -1;
	}
	for(i = 0; visited[i] != -1; ++i)
	{
		if(record[i] != -1 && record[i] < temp)
		{
			temp = record[i];
			l = visited[i];
		}
	}
	return l;
}

void Print(MGraph G, int visited[], int visited2[])
{
	printf("下面是最小生成树\n");
	int i;
	double temp;
	for(i = 0; visited[i] != -1; ++i)
	{
		printf("  %3d  -->  %3d",visited[i], visited2[i]);
		printf("     花费：%5.2f  \n",G.arcs[visited[i]][visited2[i]].adj);
	}
	printf("共有 %2d 个节点，已连接 %2d 个传感器节点,有 %2d 个被舍弃!!!\n",G.vexnum-1, i, G.vexnum-i-1);
}

void Route(MGraph &G)
{
	int i, j, tag = 0, temp = 0, k = 0, visited3[VERNUM+1];
	int visited[VERNUM+1], visited2[VERNUM+1];
	double lowcost = 0;
	for(i = 0; i < G.vexnum; ++i)
		for(j = 0; j < G.vexnum; ++j)
		{
			if(i == j || G.arcs[i][j].adj == ∞)
				continue;
			else G.arcs[i][j].adj = pow(G.arcs[i][j].adj, 2);
		}
	for(i = 0; i < VERNUM+1; ++i)
	{
		visited[i] = -1;
		visited2[i] = -1;
		visited3[i] = 0;
	}
	visited[k] = 0;
	visited3[0] = 1;
	temp = MiniCost(G, temp, visited3, 0);
	while(1)
	{
		while(temp != -1)
		{
			visited2[k] = temp;
			visited3[temp] = 1;
			lowcost = lowcost + G.arcs[visited[k]][visited2[k]].adj;
			++k;
			visited[k] = temp;
			temp = MiniCost(G, temp, visited3, 0);
		}
		visited[k] = -1;
		while(temp == -1)		//如果没有点可连
		{
			temp = MiniCost2(G, visited, visited3);		//从已连接点开始找寻新点
			if(temp == -1)
			{
				visited[k] = -1;
				Print(G, visited, visited2);
				printf("         总花费:%5.2f\n",lowcost);
				return;
			}
			visited[k] = temp;
			visited2[k] = MiniCost(G, temp, visited3,0);
			lowcost = lowcost + G.arcs[visited[k]][visited2[k]].adj;
			temp = visited2[k];
			visited3[temp] = 1;
			++k;
			visited[k] = temp;
			temp = MiniCost(G, temp, visited3,0);
		}
	}
}

void ShortPath(MGraph G)
{
	int p[VERNUM+1][VERNUM+1];
	int v, final[VERNUM+1], w;
	int i,j,num = 1;
	double D[VERNUM+1];
	for(v = 0; v < G.vexnum; ++v)
	{
		final[v] = FALSE;
		D[v] = G.arcs[0][v].adj;
		for(w = 0; w < G.vexnum; ++w) p[v][w] = FALSE;
		if(D[v] < ∞)
		{
			p[v][0] = TRUE;
			p[v][v] = TRUE;
		}
	}
	D[0] = 0;
	final[0] = TRUE;		//原点初始化为TRUE
	double min;
	for(i = 1; i < G.vexnum; ++i)		//主循环
	{
		min = ∞;
		for(w = 0; w < G.vexnum; ++w)		//寻找到原点最近的未记录的点
			if(!final[w])
				if(D[w] < min)
				{
					v = w;
					min = D[w];
				}
		if(v == G.vexnum)		//由于执行完上上个循环v为G.vexnum,且v值未改变，则不连通
		{
			printf("  无路径连通!!!\n");
			return;
		}
		final[v] = TRUE;
		++num;
		for(w = 0; w < G.vexnum; ++w)
			if(!final[w] && (min + G.arcs[v][w].adj < D[w]))
			{
				D[w] = min + G.arcs[v][w].adj;
				for(j = 0; j < G.vexnum; ++j)
					p[w][j] = p[v][j];
				p[w][w] = TRUE;
			}
	}
	printf("\n 点    时间       途经\n");
	for(v = 1; v < G.vexnum; ++v)
	{
		if(final[v] != TRUE) continue; 
		printf("%3d :  %5.2f   ", v, D[v]);
		for(i = 0; i < G.vexnum; ++i)
		{
			if(v == i) continue;
			if(p[v][i]) printf("%2d,",i);
		}
		printf("%2d\n",v);
	}
}

int main()
{
	writeFile();
	MGraph G;
	CreateUDN(G);
//	Show(G);
	ShortPath(G);
	printf("------******------\n");
	Route(G);
	system("pause");
	return 0;
}
