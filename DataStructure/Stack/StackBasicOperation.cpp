#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 20;
#define INCREMENT 5;

typedef struct
{
	int *base;
	int *top;
	int stacksize;
}SqStack;

void InitStack(SqStack &S)            //初始化栈
{
	S.base = (int *)malloc(sizeof(int) * 20);
	if(!S.base)
	{
		printf("内存开辟失败！！！\n");
		return;
	}
	S.top = S.base;
	S.stacksize = INITSIZE;
}

void DestroyStack(SqStack &S)              //销毁
{
	free(S.base);
	S.base = NULL;
}

void ClearStack(SqStack &S)              //清空
{
	S.top = S.base;
}

int StackEmpty(SqStack S)                  //检查是否为空
{
	if(S.top == S.base) return 1;
	else return 0;
}

int StackLength(SqStack S)               //获取长度
{
	return S.top - S.base;
}

int GetTop(SqStack S,int &e)                   //取出栈顶元素
{
	if(S.base == S.top)
	{
		printf("空栈！！！\n");
		return -1;
	}
	e = *(S.top - 1);
	return e;
}

void Push(SqStack &S,int e)                  //入栈
{
	if(S.top - S.base >= S.stacksize)
	{
		S.base = (int *)realloc(S.base,(S.stacksize + 5) * sizeof(int));
		if(!S.base)
		{
			printf("空间再开辟失败！！！\n");
			return;
		}
		S.top = S.base + S.stacksize;
		S.stacksize += 5;
	}
	*S.top++ = e;
}

int Pop(SqStack &S,int &e)                     //删除栈顶
{
	if(S.top == S.base)
	{
		printf("无法删除空栈!!!\n");
		return -1;
	}
	e = *--S.top;
	return e;
}

int visit(SqStack S,int i)
{
	printf("%d ",*(S.base + i));
	return 1;
}

void StackTraverse(SqStack S,int (* visit)(SqStack S,int i))
{
	if(S.top == S.base)
	{
		printf("空栈无法遍历！！！\n");
		return;
	}
	int j;
	int k = S.top - S.base;
	for(j = 0;j < k;j++) visit(S,j);
	printf("\n");
}

int main()
{
	SqStack S;
	int e;
	InitStack(S);
	Push(S,7);
	Push(S,8);
	printf("长度为：%d\n",StackLength(S));
	StackTraverse(S,visit);
	printf("删除元素：%d\n",Pop(S,e));
	printf("长度为：%d\n",StackLength(S));
	StackTraverse(S,visit);
	system("pause");
	ClearStack(S);
	DestroyStack(S);
	return 0;
}
