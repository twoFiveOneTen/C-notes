//推荐使用VS 2012

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 400

typedef struct
{
	int i,j,e;
}Triple;
typedef struct
{
	Triple data[MAXSIZE + 1];
	int mu,nu,tu;                 //矩阵的行数、列数和非零元数
}TSMatrix;

void Transpose(TSMatrix M,TSMatrix &T)
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	int col,num[20],cpot[20],t,p,q;
	if(T.tu)                //如果存在有效元
	{
		for(col = 0; col < M.nu; ++col) num[col] = 0;            //每列初始个数为0
		for(t = 0; t < M.tu; ++t) ++num[M.data[t].j];               //每遇到第j列的就计数器加1
		cpot[0] = 0;                                              //初始位置为0
		for(col = 1; col < M.nu; ++col) cpot[col] = cpot[col - 1] + num[col - 1];               //找到每一列的初始位置
		for(p = 0; p < M.tu; ++p)
		{
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			++cpot[col];           //起始位置后移一位
		}
		printf("转置成功\n");
	}
	else
	{
		printf("空矩阵\n");
		return;
	}
}

void ShowT(TSMatrix M)               //展示矩阵
{
	printf("矩阵为:\n");
	int i,j,n = 0;
	if(M.tu)
	{
		for(i = 0; i < M.mu; ++i)
		{
			for(j = 0; j < M.nu; ++j)
			{
				if(i == M.data[n].i && j == M.data[n].j)           //如果为非零元则输出值
				{
					printf("%3d",M.data[n].e);
					++n;
				}
				else printf("%3d",0);                //如果不为非零元则输出0
			}
			printf("\n");
		}
	}
}

int main()
{
	int n,m;
	while(1)
	{
		printf("请输入矩阵的行数和列数（以空格间隔,最大20):\n");
		scanf("%d %d",&m,&n);
		if(n < 1 || n > 20 || m < 1 || m > 20)
		{
			printf("输入有误\n");
			continue;
		}
		else break;
	}
	int p[20][20];
	printf("请按照矩阵行列格式在下面输入此矩阵:\n");
	int i,j,k = 0;
	TSMatrix T;
	T.mu = m;
	T.nu = n;
	T.tu = 0;
	for(i = 0; i < m; ++i)
		for(j = 0; j < n; ++j)
		{
			scanf("%d",&p[i][j]);
			if(p[i][j] != 0)
			{
				++T.tu;
				T.data[k].i = i;
				T.data[k].j = j;
				T.data[k].e = p[i][j];
				++k;
			}
		}
	TSMatrix M;
	Transpose(T,M);              //进行转置操作
	ShowT(M);
	system("pause");
	return 0;
}
