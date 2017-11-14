//推荐使用VS 2012

#include <stdio.h>
#include <stdlib.h>

typedef struct Qnode
{
	int data;
	struct Qnode *next;
}Qnode;

typedef struct
{
	Qnode *front;
	Qnode *rear;
}LinkQueue;

void InitQueue(LinkQueue &Q)               //初始化队列
{
	Q.front = Q.rear = (Qnode *)malloc(sizeof(Qnode));
	if(!Q.front)
	{
		printf("空间开辟失败！！！\n");
		return;
	}
	Q.front->next = NULL;
}

void DestroyQueue(LinkQueue &Q)              //销毁队列
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

void ClearQueue(LinkQueue &Q)                //清空队列
{
	Q.rear = Q.front->next;
	while(Q.rear)
	{
		Q.front->next = Q.rear->next;
		free(Q.rear);
		Q.rear = Q.front->next;
	}
	Q.rear = Q.front;
}

int QueueEmpty(LinkQueue Q)            //展示是否为空
{
	if(Q.front == Q.rear) return 1;
	else return 0;
}

int QueueLength(LinkQueue Q)            //获取长度
{
	int i = 0;
	Q.rear = Q.front->next;
	while(Q.rear)
	{
		++i;
		Q.rear = Q.rear->next;
	}
	return i;
}

int GetHead(LinkQueue Q,int &e)            //获取头
{
	if(Q.front->next)
	{
		e = Q.front->next->data;
		return e;
	}
	else
	{
		printf("空队列，无头!!!\n");
		return -1;
	}
}

void EnQueue(LinkQueue &Q,int e)            //插入
{
	Qnode *p;
	p = (Qnode *)malloc(sizeof(Qnode));
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

int DeQueue(LinkQueue &Q,int &e)              //删除队列头
{
	if(Q.front == Q.rear)
	{
		printf("空队列无法删除！！！\n");
		return -1;
	}
	Qnode *p;
	p = Q.front->next;
	e = p->data;
	if(p == Q.rear) Q.rear = Q.front;
	Q.front->next = p->next;
	free(p);
	return e;
}
 int QueueTraverse(LinkQueue Q)                        //遍历
{
	int j = 0;
	Qnode *p;
	p = Q.front->next;
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int main()
{
	int e,i;
	LinkQueue Q;
	InitQueue(Q);
	for(i = 0;i < 10;++i)
	{
		EnQueue(Q,2 * i);
	}
	EnQueue(Q,100);
	GetHead(Q,e);
	printf("头是:%d\n",e);
	printf("删除:%d\n",DeQueue(Q,e));
	QueueTraverse(Q);
	system("pause");
	ClearQueue(Q);
	DestroyQueue(Q);
	return 0;
}
