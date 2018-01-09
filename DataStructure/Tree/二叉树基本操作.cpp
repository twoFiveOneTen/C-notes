//二叉树的基本操作

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

BiTree *ClearBiTree(BiTree *T)         //清空二叉树
{
	if(T == NULL) return T;
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	free(T);
	T = NULL;
	return T;
}

int BiTreeEmpty(BiTree *T)            //判断是否为空
{
	if(NULL == T) return 0;
	else return 1;
}

int BiTreeDepth(BiTree *T)
{
	int u,v;
	if(T == NULL) return 0;
	u = BiTreeDepth(T->lchild);
	v = BiTreeDepth(T->rchild);
	if(u > v) return u + 1;
	else return v + 1;
}

BiTree *Root(BiTree *T)             //返回二叉树根
{
	if(T) return T;
	else return NULL;
}

char Value(BiTree *T, BiTree *e)           //返回某节点值
{
	if(e) return e->data;
	else return NULL;
}

void Assign(BiTree *T, BiTree *e, char value)           //赋值
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p == e)
			{
				p->data = value;
				DestroyStack(S);
				return;
			}
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			p = p->rchild;
		}//endif
	}//endwhile
	printf("未找到\n");
	DestroyStack(S);
}

BiTree *Parent(BiTree *T, BiTree *e)         //返回根节点
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p->lchild == e) return p;
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			if(p->rchild == e) return p;
			p = p->rchild;
		}//endif
	}//endwhile
	DestroyStack(S);
}

BiTree *LeftChild(BiTree *T, BiTree *e)             //返回左孩子
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p == e) return p->lchild;
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			p = p->rchild;
		}//endif
	}//endwhile
	return NULL;
	DestroyStack(S);
}

BiTree *RightChild(BiTree *T, BiTree *e)             //返回右孩子
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p == e) return p->rchild;
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			p = p->rchild;
		}//endif
	}//endwhile
	return NULL;
	DestroyStack(S);
}

BiTree *LeftSibling(BiTree *T, BiTree *e)             //返回左兄弟
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p->rchild == e) return p->lchild;
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			p = p->rchild;
		}//endif
	}//endwhile
	return NULL;
	DestroyStack(S);
}
BiTree *RightSibling(BiTree *T, BiTree *e)             //返回右兄弟
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p->lchild == e) return p->rchild;
			push(S,p,-1);
			p = p->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			p = pop(S,a);
			p = p->rchild;
		}//endif
	}//endwhile
	return NULL;
	DestroyStack(S);
}

void InsertChild(BiTree *T, BiTree *p, int LR, BiTree *c)         //插入孩子
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *e;
	e = T;
	//p->lchild = c;
	while(e != NULL || !StackEmpty(S))
	{
		while(e)
		{
			if(e == p)
			{
				if(LR == 0)
				{
					if(e->lchild != NULL)          //如果欲插入为左子树且原原左子树不为空，
					{
						c->rchild = e->lchild;             //则原左子树变为c的右子树
						e->lchild = c;
					}
					p->lchild = c;
				}
				else
				{
					if(e->rchild != NULL)               //同上
					{
						c->rchild = e->rchild;
						e->rchild = c;
					}
					p->rchild = c;
				}
				return;
			}
			push(S,e,-1);
			e = e->lchild;
		}//endwhile
		if(!StackEmpty(S))
		{
			e = pop(S,a);
			e = e->rchild;
		}//endif
	}//endwhile
	DestroyStack(S);
}

void DeleteChild(BiTree *T, BiTree *q, int LR)      //删除孩子
{
	Stack S;
	node a;
	InitStack(S);
	BiTree *p;
	p = T;
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			if(p == q)
			{
				if(LR == 0)
				{
					DestroyBiTree(p->lchild);
					p->lchild = NULL;
				}
				else
				{
					DestroyBiTree(p->rchild);
					p->rchild = NULL;
				}
				return;
			}
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
}

void PreOrderTraverse(BiTree *T, void visit(BiTree *q))           //递归遍历，下同
{
	if(T)
	{
		visit(T);
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
	}
}

void InOrderTraverse(BiTree *T, void visit(BiTree *q))
{
	if(T)
	{
		InOrderTraverse(T->lchild,visit);
		visit(T);
		InOrderTraverse(T->rchild,visit);
	}
}

void PostOrderTraverse(BiTree *T, void visit(BiTree *q))
{
	if(T)
	{
		PostOrderTraverse(T->lchild,visit);
		PostOrderTraverse(T->rchild,visit);
		visit(T);
	}
}
int print(BiTree *T,int level)
{
	if(!T) return 0;
	if(level == 0)
	{
		printf("%c",T->data);
		return 1;
	}
	else return print(T->lchild, level - 1) + print(T->rchild, level - 1);
}

void LevelOrderTraverse(BiTree *T)         //层次遍历
{
	int i;
	for(i = 0; i < BiTreeDepth(T) ; ++i)
	{
		print(T,i);
	}
}

int main()
{
	BiTree *T,*q,*A,*B,*C,*D,*E,*F,*G,*H,*I,*J,*K,*L;
	T = NULL;
	char temp;
	InitBiTree(T);
	printf("请输入二叉树:");
	T = CreateBiTree(T);
	A = T;
	B = T->lchild;
	C = T->rchild;
	D = B->lchild;
	E = B->rchild;
	F = C->rchild;
	G = E->lchild;
	H = G->lchild;
	I = G->rchild;
	J = D->lchild;
	L = J->rchild;
	K = F->lchild;
	printf("\n先根遍历:");
	PreOrderTraverse(T,visit);
	printf("\n");
	printf("中根遍历:");
	InOrderTraverse(T,visit);
	printf("\n");
	printf("后根遍历:");
	PostOrderTraverse(T,visit);
	printf("\n");
	printf("层次遍历:");
	LevelOrderTraverse(T);
	printf("\n\n");
	printf("将'a'赋值为'z'...\n");
	Assign(T,A,'z');
	temp = Value(T,A);
	printf("A节点值为:%c\n",temp);
	q = LeftChild(T,A);
	printf("A的左孩子为:%c\n",q->data);
	printf("先根遍历:");
	PreOrderTraverse(T,visit);
	printf("\n\n");
	printf("深度为:%d\n",BiTreeDepth(T));
	q = LeftSibling(T,C);
	if(q) printf("\nC的左兄弟结点是:%c\n",q->data);
	else printf("%c无左兄弟！\n",C->data);
	printf("\n向C节点插入左孩子a、b!\n");
	//////////////////
	BiTree *o;
	o = (BiTree *)malloc(sizeof(BiTree));
	o->data = 'a';
	o->lchild = (BiTree *)malloc(sizeof(BiTree));
	o->rchild = NULL;
	o->lchild->data = 'b';
	o->lchild->lchild = NULL;
	o->lchild->rchild = NULL;
	/////////////////
	printf("插入前先根遍历:");
	PreOrderTraverse(T,visit);
	printf("\n");
	InsertChild(T,C,0,o);
	printf("插入后先根遍历:");
	PreOrderTraverse(T,visit);
	printf("\n");
	DeleteChild(T,E,0);
	printf("\n删除e的左子树\n");
	printf("层次遍历:");
	LevelOrderTraverse(T);
	printf("\n");
	system("pause");
	DestroyBiTree(T);
	return 0;
	//测试输入：abdj#l###egh##i###c#fk###
	//插入测试树:ab###
}
