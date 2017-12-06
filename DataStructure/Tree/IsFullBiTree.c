//VS 2012 is recommended.

#include <stdio.h>
#include <stdlib.h>
#define INITSIZE 50
typedef struct BiTree
{
	 char data;
	 struct BiTree *lchild,*rchild;
}BiTree;
typedef struct nodd
{
	BiTree *t;
	struct nodd *next;
}Queuenode;

typedef struct nn
{
	Queuenode *front,*rear;
}Queue;

void InitQueue(Queue &Q)
{
	Q.front = (Queuenode *)malloc(sizeof(Queuenode));
	Q.rear = Q.front;
	Q.rear->next = NULL;
}

void InsertQueue(Queue &Q, BiTree *o)
{
	if(o)
	{
		Queuenode *q;
		q = (Queuenode *)malloc(sizeof(Queuenode));
		q->t = o;
		q->next = NULL;
		Q.rear->next = q;
		Q.rear = q;
	}
	else return;
}
BiTree *DeQueue(Queue &Q)
{
	BiTree *m;
	Queuenode *n;
	n = Q.front->next;
	m = Q.front->next->t;
	if(Q.front->next == Q.rear) Q.front = Q.rear;
	else Q.front->next = n->next;
	//free(n);
	return m;
	n = NULL;
}

void DestroyQueue(Queue &Q)              //销毁队列
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

int QueueEmpty(Queue &Q)
{
	if(Q.front == Q.rear) return 1;
	else return 0;
}

typedef struct
{
	BiTree *ch;
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

BiTree *DestroyBiTree(BiTree *T)            //销毁二叉树
{
	if(T)
	{
		if(T->lchild) DestroyBiTree(T->lchild);
		if(T->rchild) DestroyBiTree(T->rchild);
		free(T);
		T = NULL;
	}
	return T;
}

int Judge(BiTree *T)
{
	int j = 0;
	Queue Q;
	BiTree *p;
	InitQueue(Q);
	p = T;
	if(T)
	{
		InsertQueue(Q,p);
		while(!QueueEmpty(Q))
		{
			p = DeQueue(Q);
			InsertQueue(Q,p->lchild);
			InsertQueue(Q,p->rchild);
			if(j != 1)
			{
				if(p->lchild == NULL && p->rchild != NULL) return 0;
				if(p->rchild == NULL) j = 1;
			}
			else
			{
				if(p->lchild == NULL && p->rchild == NULL) continue;
				else return 0;
			}
		}
	}
	DestroyQueue(Q);
	return 1;
}
int main()
{
	BiTree *T;
	T = NULL;
	int j;
	T = CreateBiTree(T);
	j = Judge(T);
	if(j == 0) printf("非完全二叉树!\n");
	else printf("是完全二叉树！\n");
	system("pause");
	DestroyBiTree(T);
	return 0;
	//非完全测试输入：abdj#l###egh##i###c#fk###
	//完全测试输入2:abdh##i##ej##k##cfl##m##g##
}
