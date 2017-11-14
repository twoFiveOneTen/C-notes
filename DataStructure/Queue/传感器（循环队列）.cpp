//推荐使用VS 2012

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

typedef struct
{
	int *base;
	int front;
	int rear;
}SqQueue;

void InitQueue(SqQueue &Q)
{
	Q.base = (int *)malloc(10 * sizeof(int));
	if(!Q.base)
	{
		printf("空间开辟失败!!!\n");
		return;
	}
	Q.front = Q.rear = 0;
	int i = 0;
	for(i = 0;i < 10;i++) Q.base[i] = 0;
}

int Find(SqQueue Q)
{
	int e,i;
	e = Q.base[0];
	for(i = 0;i < 10;i++)
	{
		if(Q.base[i] > e) e = Q.base[i];
	}
	return e;
}

void Show(SqQueue Q)
{
	int i = 0;
	printf("获取元素为：");
	for(i = 0;i < 10;i++) printf("%d ",Q.base[i]);
	printf("\n");
}

void Change(SqQueue &Q)
{
	int i;
	for(i = 9;i > 0;i--) Q.base[i] = Q.base[i - 1];
}

int main()
{
	time_t timep;
	int m,n;
	struct tm *q;
	time(&timep);
	q = localtime(&timep);
	n = q->tm_sec;
	SqQueue Q;
	InitQueue(Q);
	while(1)
	{
		Change(Q);
		Q.base[0] = rand()%1000;
		time(&timep);
		q = localtime(&timep);
		if(q->tm_sec - n == 1 || q->tm_sec - n == -59)
		{
			Show(Q);
			printf("最大值是:%d\n",Find(Q));
			n = q->tm_sec;
		}
		//system("cls");
	}
	system("pause");
	return 0;
}
