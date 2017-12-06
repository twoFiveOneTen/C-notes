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
	if(n != -1) S.top->tag = n;
	++S.top;
}

BiTree *pop(Stack &S,node &a)
{
	BiTree *p;
	--S.top;
	p = S.top->ch;
	a.ch = p;
	a.tag = S.top->tag;
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
	else return;
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
			p = pop(S,a);
			p = p->rchild;
		}//endif
	}//endwhile
	DestroyStack(S);
	printf("\n");
}//PreOrderTraverse

void InOrderTraverse(BiTree *T, void visit(BiTree *p))         //中序遍历
{
	printf("中序遍历:");
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p != NULL)
		{
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			visit(p);
			p = p->rchild;
		}//endif
	}//endwhile
	DestroyStack(S);
	printf("\n");
}//InorderTraverse

void PostOrderTraverse(BiTree *T, void visit(BiTree *p))         //后序遍历
{
	printf("后序遍历:");
	Stack S;
	node a;
	InitStack(S);
	push(S,T,0);
	while(!StackEmpty(S))
	{
		pop(S,a);
		switch(a.tag)
		{
		case 0:
			push(S,a.ch,1);
			if(a.ch->lchild) push(S,a.ch->lchild,0);
			break;
		case 1:
			push(S,a.ch,2);
			if(a.ch->rchild) push(S,a.ch->rchild,0);
			break;
		case 2:
			visit(a.ch);
			break;
		}
	}//while
	DestroyStack(S);
	printf("\n");
}

void LevelTraverse(BiTree *T,void visit(BiTree *p))
{
	printf("层次遍历:");
	Queue Q;
	BiTree *p;
	InitQueue(Q);
	p = T;
	if(T)
	{
		visit(T);
		InsertQueue(Q,p);
		while(!QueueEmpty(Q))
		{
			p = DeQueue(Q);
			visit(p->lchild);
			InsertQueue(Q,p->lchild);
			visit(p->rchild);
			InsertQueue(Q,p->rchild);
		}
	}
	DestroyQueue(Q);
	printf("\n");
}

int main()
{
	BiTree *T;
	T = NULL;
	T = CreateBiTree(T);
	PreOrderTraverse(T,visit);
	InOrderTraverse(T,visit);
	PostOrderTraverse(T,visit);
	LevelTraverse(T,visit);
	system("pause");
	DestroyBiTree(T);
	return 0;
	//测试输入：abd##eg#h###c#f##
	//完全测试输入2:abdh##i##ej##k##cfl##m##gn##o##
	//测试输入2:abdj#l###egh##i###c#fk###
}
