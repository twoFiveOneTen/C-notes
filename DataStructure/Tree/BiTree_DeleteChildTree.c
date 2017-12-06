//VS 2012 is recommended.

#include <stdio.h>
#include <stdlib.h>
#define INITSIZE 50

typedef struct BiTree
{
	 char data;
	 struct BiTree *lchild,*rchild;
}BiTree;

typedef struct
{
	BiTree *ch;
	int tag;
}node;

typedef struct nod
{
	node *base,*top;
	int Stacksize;
}Stack;

void InitStack(Stack &T)
{
	T.base = (node *)malloc(sizeof(node) * INITSIZE);
	T.Stacksize = INITSIZE;
	T.top = T.base;
}

int StackEmpty(Stack S)          //栈是否为空
{
	if(S.top == S.base) return 1;
	else return 0;
}

void push(Stack &S,BiTree *p,int n)             //入栈
{
	S.top->ch = p;
	++S.top;
}

BiTree *pop(Stack &S)
{
	BiTree *p;
	--S.top;
	p = S.top->ch;
	return p;
}

void DestroyStack(Stack S)
{
	free(S.base);
	S.base = S.top = NULL;
}

void visit(BiTree *p)           //遍历的visit
{
	if(p != NULL) printf("%c",p->data);
}

void InitBiTree(BiTree *T)            //初始化二叉树
{
	T = NULL;
}

BiTree *CreateBiTree(BiTree *T)           //创建二叉树
{
	char ch;
	scanf("%c",&ch);
	if(ch == '#') T = NULL;
	else
	{
		if(!(T = (BiTree *)malloc(sizeof(BiTree)))) printf("内存开辟失败！！！\n");
		T->data = ch;
		T->lchild = CreateBiTree(T->lchild);
		T->rchild = CreateBiTree(T->rchild);
	}
	return T;
}

void DestroyBiTree(BiTree *T)            //销毁二叉树
{
	if(T)
	{
		if(T->lchild) DestroyBiTree(T->lchild);
		if(T->rchild) DestroyBiTree(T->rchild);
		free(T);
		T = NULL;
	}
}
void Delete(BiTree *T, char e)           //删除子树
{
	Stack S;
	InitStack(S);
	BiTree *p,*q;
	p = T;
	int a;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p->data == e)
			{
				if(q->lchild == p) a = 0;
				else a = 1;
				DestroyBiTree(p->lchild);
				p->lchild = NULL;
				DestroyBiTree(p->rchild);
				p->rchild = NULL;
				free(p);
				if(a == 0) q->lchild = NULL;
				else q->rchild = NULL;
				p = q;
			}
			push(S,p,-1);
			q = p;
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S);
			q = p;
			p = p->rchild;
		}//endif
	}//endwhile
	DestroyStack(S);
}

void PreOrderTraverse(BiTree *T, void visit(BiTree *q))         //先序遍历
{
	printf("先序遍历:");
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			visit(p);
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S);
			p = p->rchild;
		}//endif
	}//endwhile
	DestroyStack(S);
	printf("\n");
}//PreOrderTraverse

int main()
{
	BiTree *T,*p;
	T = NULL;
	T = CreateBiTree(T);
	PreOrderTraverse(T,visit);
	Delete(T,'b');
	PreOrderTraverse(T,visit);
	system("pause");
	DestroyBiTree(T);
	//测试输入：abd##eg#h###c#f##
	//完全测试输入2:abdh##i##ej##k##cfl##m##gn##o##
	//测试输入:abdj#l###egh##i###c#bk###
	return 0;
}
