/*
编程实现二叉树的建立，先序、中序、后序（递归和非递归方法）、层序遍历。求二叉树的高度、宽度，结点数。判断是否为二叉排序树。
[基本要求]
（1） 从文件中读入建树信息，树的节点数目不小于20个，树的高度不小于4。
（2） 采用二叉链表结构。
（3） 至少2组输入数据，分别是二叉排序树和不是二叉排序树，
*/
#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 60
typedef struct CSNode
{
	char data;
	struct CSNode* firstchild,* nextsibling,* parent;
}CSNode;

typedef struct qnode
{
	CSNode* C;
	qnode* next;
}qnode;

typedef struct Queue
{
	qnode* front,* rear;
}Queue;

typedef struct
{
	CSNode* ch;
	int tag;
}node;

typedef struct Stacknode
{
	node* base,* top;
	int Stacksize;
}Stack;

void InitQueue(Queue &Q)            //初始化队列
{
	Q.front = (qnode *)malloc(sizeof(qnode));
	Q.rear = Q.front;
	Q.rear->next = NULL;
}

void Enqueue(Queue &Q, CSNode* S)
{
	qnode* p;
	p = (qnode *)malloc(sizeof(qnode));
	p->C = S;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

CSNode* DeQueue(Queue &Q)
{
	CSNode* m;
	qnode* n;
	n = Q.front->next;
	m = Q.front->next->C;
	if(Q.front->next == Q.rear) Q.rear = Q.front;
	else Q.front->next = n->next;
	return m;
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

int QueueEmpty(Queue Q)
{
	if(Q.front == Q.rear) return 1;
	else return 0;
}

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

void push(Stack &S, CSNode* p, int n)             //入栈
{
	S.top->ch = p;
	if(n != -1) S.top->tag = n;
	++S.top;
}

CSNode* pop(Stack &S, node &a)
{
	CSNode* p;
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
CSNode* CreateCSNode(CSNode* C, FILE* fp)      //创建二叉树
{
	CSNode* p,* q,* r;
	char temp[60],ch;
	int i = 0,j,n;
	Queue Q;
	InitQueue(Q);
	ch = fgetc(fp);
	while(!feof(fp))
	{
		temp[i] = ch;         //建树信息暂存在temp[]数组中
		++i;
		ch = fgetc(fp);
	}
	i = 1;
	p = (CSNode *)malloc(sizeof(CSNode));
	C = p;
	p->data = temp[0];            //树根赋值
	p->parent = NULL;           //树根的双亲结点为空
	p->nextsibling = NULL;            //树根的兄弟指针为空
	Enqueue(Q,p);
	while(!QueueEmpty(Q))
	{
		p = DeQueue(Q);
		for(j = 0; j < 3; ++j)        //每一个双亲结点下最多三个结点，所以用for循环往下最多读取三个
		{
			if(temp[i + j] != '#')           //如果不为'#'，
			{
				r = (CSNode *)malloc(sizeof(CSNode));
				r->data = temp[i + j];
				r->parent = p;
				r->nextsibling = NULL;
				Enqueue(Q,r);
				if(j == 0)          //如果是循环第一圈
				{
					p->firstchild = r;
					q = r;
				}
				else         //如果不是第一圈
				{
					q->nextsibling = r;
					q = r;
				}
			}
			else
			{
				if(j == 0) p->firstchild = NULL;
				i = i + j + 1;         //给i赋值为最后读取的位置之后
				break;
			}
		}//endfor
		if(j == 3) i = i + 3;        //如果循环三次后退出
	}
	printf("创建完成!\n");
	return C;
}

void visit1(CSNode* C)
{
	if(C == NULL) return;
	printf("%c",C->data);
}

void visit2(Queue &Q, CSNode* C)
{
	if(C == NULL) return;
	CSNode* p;
	p = C;
	while(p != NULL)
	{
		printf("%c",p->data);
		Enqueue(Q,p);
		p = p->nextsibling;
	}
}

void ShowQueue(Queue Q)
{
	printf("\n对列为:");
	qnode* q;
	q = Q.front->next;
	while(q)
	{
		printf("%c",q->C->data);
		q = q->next;
	}
	printf("\n");
}

CSNode* Next(Queue Q)
{
	qnode* e;
	e = Q.front->next;
	while(e->next)
	{
		if(e->C->firstchild != NULL) return e->C->firstchild;
		e = e->next;
	}return NULL;
}

void PreOrderTraverse(CSNode* C)        //递归先序遍历
{
	if(C) printf("%c",C->data);
	else return;
	if(C->firstchild)
	{
		PreOrderTraverse(C->firstchild);
		if(C->firstchild->nextsibling) PreOrderTraverse(C->firstchild->nextsibling);
	}
}

void InOrderTraverse(CSNode* C)          //递归中序遍历
{
	if(C->firstchild) InOrderTraverse(C->firstchild);
	else
	{
		printf("%c",C->data);
		return;
	}
	printf("%c",C->data);
	if(C->firstchild->nextsibling) InOrderTraverse(C->firstchild->nextsibling);
}

void PostOrderTraverse(CSNode* C)          //递归后序遍历
{
	if(C->firstchild)
	{
		PostOrderTraverse(C->firstchild);
		if(C->firstchild->nextsibling) PostOrderTraverse(C->firstchild->nextsibling);
		printf("%c",C->data);
	}
	else printf("%c",C->data);
}
void PreOrderTraverseF(CSNode* T)         //非递归先序遍历
{
	printf("先序遍历:");
	Stack S;
	node a;
	InitStack(S);
	CSNode* p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			printf("%c",p->data);
			push(S,p,-1);
			p = p->firstchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			if(p->firstchild) p = p->firstchild->nextsibling;
			else p = NULL;
		}//endif
	}//endwhile
	DestroyStack(S);
	printf("\n");
}
void InOrderTraverseF(CSNode* C)         //中序遍历
{
	printf("中序遍历:");
	Stack S;
	node a;
	InitStack(S);
	CSNode* p;
	p = C;
	while(p != NULL || !StackEmpty(S))
	{
		while(p != NULL)
		{
			push(S,p,-1);
			p = p->firstchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			printf("%c",p->data);
			if(p->firstchild) p = p->firstchild->nextsibling;
			else p = NULL;
		}//endif
	}//endwhile
	DestroyStack(S);
	printf("\n");
}//InorderTraverseF

void PostOrderTraverseF(CSNode* C)         //后序遍历
{
	printf("后序遍历:");
	Stack S;
	node a;
	InitStack(S);
	push(S,C,0);
	while(!StackEmpty(S))
	{
		pop(S,a);
		switch(a.tag)
		{
		case 0:
			push(S,a.ch,1);
			if(a.ch->firstchild) push(S,a.ch->firstchild,0);
			break;
		case 1:
			push(S,a.ch,2);
			if(a.ch->firstchild)
				if(a.ch->firstchild->nextsibling) push(S,a.ch->firstchild->nextsibling,0);
			break;
		case 2:
			printf("%c",a.ch->data);
			break;
		}
	}//while
	DestroyStack(S);
	printf("\n");
}

void LevelTraverse(CSNode* C,void visit1(CSNode* p), void visit2(Queue &Q,CSNode* q),
				   int &num, int &depth, int &width)
{
	printf("层次遍历:");
	Queue Q;
	int i = 2,width2 = 1;
	CSNode *p,*q,*r,*s;
	InitQueue(Q);
	p = C;
	q = C;
	if(C)
	{
		visit1(C);
		Enqueue(Q,p);
		while(!QueueEmpty(Q))
		{
			p = DeQueue(Q);
			++num;
			if(p == q)
			{
				++depth;
				q = p->firstchild;
				if(width <= width2)
				{
					width = width2;
					width2 = 1;
				}
			}
			else ++width2;
			if(q == NULL) q = Next(Q);
			visit1(p->firstchild);
			if(p->firstchild != NULL)
			{
				Enqueue(Q,p->firstchild);
				visit2(Q,p->firstchild->nextsibling);
			}
			
		}
	}
	DestroyQueue(Q);
	if(width < width2) width = width2;
	printf("\n");
}
int Judge(CSNode* C)         //非递归先序遍历
{
	Stack S;
	node a;
	InitStack(S);
	char temp = 0;
	CSNode* p;
	p = C;
	while(p != NULL || !StackEmpty(S))
	{
		while(p != NULL)
		{
			push(S,p,-1);
			p = p->firstchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			if(p->data <= temp) return 0;
//			printf("%c",p->data);
			temp = p->data;
			if(p->firstchild) p = p->firstchild->nextsibling;
			else p = NULL;
		}//endif
	}//endwhile
	DestroyStack(S);
	printf("\n");
	return 1;
}
int main()
{
	CSNode* C = NULL;
	FILE* fp;
	int num = 0,depth = 0,width = 0,temp;
	fp = fopen("file1.txt","r");
	if(!fp) printf("文件打开失败!\n");
	C = CreateCSNode(C,fp);
	printf("递归先序遍历:");
	PreOrderTraverse(C);
	printf("\n递归中序遍历:");
	InOrderTraverse(C);
	printf("\n递归后序遍历:");
	PostOrderTraverse(C);
	printf("\n");
	PreOrderTraverseF(C);
	InOrderTraverseF(C);
	PostOrderTraverseF(C);
	LevelTraverse(C,visit1,visit2,num,depth,width);
	printf("高度为：%d\n",depth);
	printf("宽度为：%d\n",width);
	printf("节点数量为：%d\n",num);
	temp = Judge(C);
	if(temp == 1) printf("是二叉排序树!\n");
	else printf("不是二叉排序树!\n");
	fclose(fp);
	system("pause");
	return 0;
}
