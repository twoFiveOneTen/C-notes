//推荐使用VS 2012

#include <stdio.h>
#include <stdlib.h>

typedef struct shape
{
	int x1,y1,x2,y2;
	int code;
	struct shape *next;
}Link;

Link *InitLink(Link *L, int N)              //形成菜单链表
{
	L = (Link *)malloc(sizeof(Link));
	L->next = NULL;
	int a, b, c, d;
	Link *p;
	int i;
	for(i = 1;i <= N;i++)
	{
		scanf("%d %d %d %d", &a, &b, &c, &d);                         //录入菜单坐标信息
		if (a > 2559 || a < 0 || b >2559 || b < 0 || c > 2559 || c < 0 || d >2559 || d < 0 || a >= c || b >= d)               //有效性检验
		{
			i--;
			printf("无效坐标，重新输入\n");
			continue;
		}
		p = (Link *)malloc(sizeof(Link));
		p->x1 = a;
		p->y1 = b;
		p->x2 = c;
		p->y2 = d;
		p->next = L->next;
		p->code = i;
		L->next = p;
	}
	return L;
}

void DestroyLink(Link *L)            //销毁链表
{
	Link *p;
	p = L;
	while(L != NULL)
	{
		p = p->next;
		free(L);
		L = p;
	}
}

void Compare(Link *L,int x,int y)             //找出合适界面并输出正确结果
{
	Link *p,*q;
	p = L->next;
	q = L;
	while(p != NULL)
	{
		if(p->x1 <= x && p->x2 >= x && p->y1 <= y && p->y2 >= y)
		{
			printf("%d\n",p->code);
			q->next = p->next;
			p->next = L->next;
			L->next = p;
			return;
		}
		else
		{
			p = p->next;
			q = q->next;
		}
	}
	printf("IGNORED\n");
}

int main()
{
	int j;
	int N = 0, M = 0;
	while(N<=0 || M<=0)
	{
		scanf("%d %d", &N, &M);
		if(N<=0 || M<=0) printf("输入格式有误，重新输入\n");
	}
	Link *L = NULL;
	L = InitLink(L,N);
	int *a = (int *)malloc(M * sizeof(int));
	int *b = (int *)malloc(M * sizeof(int));
	for(j = 0;j < M;j++) scanf("%d %d", &a[j], &b[j]);
	for(j = 0;j < M;j++) Compare(L, a[j], b[j]);
	DestroyLink(L);
	system("pause");
	return 0;
}
