#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>

#define Length 127
#define TAG 15

typedef struct bi
{
	unsigned int a:1;
}bite;

typedef struct File
{
	char code[18];
	char ch;
}codedata;

void Line()
{
	printf("--------************--------\n");
}

char GetInput1()             //the first menu
{
	int i = 0;
	char c;
	while(i == 0)
	{
		printf("a.生成编码表     b.编码\n");
		printf("c.解码\n");
		printf("q.Quit");
		c = getch();
		if((c < 'a' || c > 'c') && c != 'q')
		{
			Line();
			printf("Wrong input, once again\n");
			Line();
		}
		else
		{
			printf("  --%c--\n",c);
			i = 1;
			Line();
		}
	}
	return c;
}

typedef struct BiTree
{
	 int weight;
	 char code[16];
	 char ch;
	 struct BiTree *lchild,*rchild,* parent;
}BiTree;

typedef struct no
{
	BiTree *data;
	struct no *next,*prior;
}LinkList;

typedef struct
{
	BiTree* ch;
}node;

typedef struct nod
{
	node *base,*top;
	int Stacksize;
}Stack;

typedef struct codenode
{
	int* base,* top;
}SStack;

void InitStack(Stack &T)
{
	T.base = (node *)malloc(sizeof(node) * 50);
	T.Stacksize = 50;
	T.top = T.base;
}

void InitSStack(SStack &S)
{
	S.base = (int *)malloc(sizeof(int) * 16);
	S.top = S.base;
}

int StackEmpty(Stack S)          //栈是否为空
{
	if(S.top == S.base) return 1;
	else return 0;
}

void push(Stack &S, BiTree* p)             //入栈
{
	S.top->ch = p;
	++S.top;
}

BiTree* pop(Stack &S)
{
	BiTree* p;
	--S.top;
	p = S.top->ch;
	return p;
}

void DestroyStack(Stack &S)
{
	free(S.base);
	S.base = S.top = NULL;
}

void MakeCode(BiTree* p, SStack &Q)              //从叶子节点逆向求编码
{
	BiTree* q = p->parent;
	while(q)
	{
		if(q->lchild == p)
		{
			*Q.top++ = 0;
		}
		else
		{
			*Q.top++ = 1;
		}
		p = q;
		q = q->parent;
	}
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

void PreOrderTraverse(BiTree* T)         //进行哈夫曼编码并写入文件
{
	Stack S;
	SStack Q;
	InitSStack(Q);
	InitStack(S);
	BiTree* p;
	int j = 0, * o;
	p = T;
	FILE* fp;
	fp = fopen("编码表.dat","wb");
	codedata data;
	printf(" 字符   次数      编码\n");
	printf("----------------------------------\n");
	while(p != NULL || !StackEmpty(S))
	{
		while(p)
		{
			push(S,p);
			if(p->lchild == NULL && p->rchild == NULL)
			{
				MakeCode(p,Q);     //从叶子节点逆向求编码
				if(p->ch == '\n') printf("换行    %4d      ",p->weight);
				else if(p->ch == TAG);
				else printf(" [%c]    %4d      ",p->ch,p->weight);
				o = Q.top;
				data.ch = p->ch;
				while(o != Q.base)
				{
					--o;
					if(*o == 1) p->code[j] = '1';
					else p->code[j] = '0';
					++j;
				}
				p->code[j] = '\0';
//				printf("%4d  ",p->weight);
				if(p->ch != 15) printf("%s\n",p->code);
				strcpy(data.code, p->code);		//转移编码以写入文件
				fwrite(&data,sizeof(codedata),1,fp);
				j = 0;
				Q.top = Q.base;
			}
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
	fclose(fp);
	DestroyBiTree(T);
}//

LinkList *InitList(LinkList *L){                     //构造空的带头节点的单链表
	L = (LinkList *)malloc(sizeof(LinkList));
	L->data = NULL;
	L->next = NULL;
	L->prior = NULL;
	return L;
}

void DeleteList(LinkList* p)
{
	p->prior->next = p->next;
	if(p->next != NULL) p->next->prior = p->prior;
	p = NULL;
}

void Merge(LinkList *L)
{
	LinkList* s,* p,* q;
	p = L->next;
	q = p->next;
	s = (LinkList *)malloc(sizeof(LinkList));
	s->data = (BiTree *)malloc(sizeof(BiTree));
	s->data->weight = p->data->weight + q->data->weight;
	p->data->parent = s->data;
	q->data->parent = s->data;
	s->data->lchild = p->data;
	s->data->rchild = q->data;
	s->data->parent = NULL;
	LinkList* r = L->next;
	int k = -1;
	while(r->data->weight < s->data->weight)
	{
		if(r->next == NULL)
		{
			r->next = s;
			s->prior = r;
			s->next = NULL;
			k = 0;
			break;
		}
		r = r->next;
	}
	if(k == -1)
	{
		s->next = r;
		s->prior = r->prior;
		r->prior->next = s;
		r->prior = s;
	}
	DeleteList(p);
	DeleteList(q);
}

int DestroyList(LinkList *L){                    //销毁单链表
	LinkList* p;
	p = L;
	while(L != NULL){
		p = p->next;
		free(L->data);
		free(L);
		L = p;
	}
	return 1;
}

int CreateRoot(LinkList* L, int w[Length])            //创建多个单节点二叉树
{
	int i,num = 0;
	LinkList* p,* q;
	q = L;
	for(i = 0; i < Length; ++i)
	{
		if(w[i] == 0) continue;
		p = (LinkList *)malloc(sizeof(LinkList));
		p->data = (BiTree *)malloc(sizeof(BiTree));
		p->data->weight = w[i];
		p->data->ch = i;
		p->data->lchild = NULL;
		p->data->rchild = NULL;
		p->next = NULL;
		p->prior = q;
		q->next = p;
		q = p;
		++num;
	}
	return num;
}

void ShowList(LinkList* L)
{
	printf("二叉树集合为:");
	LinkList* p = L->next;
	while(p != NULL)
	{
		printf("%d\n",p->data->weight);
		p = p->next;
	}
	printf("\n"); 
}

void Sort(LinkList* L)
{
	LinkList* p,* q,* r;
	q = L->next;
	p = q->next;
	while(p != NULL)
	{
		q = p->prior;
		if(q->data->weight > p->data->weight)
		{
		while(q->data->weight > p->data->weight)
		{
			q = q->prior;
			if(q == L) break;
		}
		r = p->next;
		p->prior->next = p->next;
		if(p->next != NULL) p->next->prior = p->prior;
		p->next = q->next;
		q->next->prior = p;
		p->prior = q;
		q->next = p;
		p = r;
		}
		else p = p->next;
	}
}

void Coding(LinkList* L)
{
	FILE* fp;
	if((fp = fopen("file.txt","r")) == NULL)
	{
		printf("文件打开失败");
		return;
	}
	int Library[Length],num,i;
	for(i = 0; i < Length; ++i)
		Library[i] = 0;
	char ch;
	ch = fgetc(fp);
	while(!feof(fp))
	{
		++Library[(int)ch];
		ch = fgetc(fp);
	}
	Library[TAG] = 10000;
	num = CreateRoot(L,Library);
	Sort(L);
	for(i = 0; i < num - 1; ++i) Merge(L);
	PreOrderTraverse(L->next->data);
	fclose(fp);
}
//1111110111001000
void Codefile()		//编码
{
	FILE* fp,* fq;
	int num;
	fp = fopen("编码表.dat","rb");
	codedata data[Length],temp;
	fread(&temp,sizeof(codedata),1,fp);
	while(!feof(fp))
	{
		num = temp.ch;
		data[num].ch = temp.ch;
		strcpy(data[num].code,temp.code);
		fread(&temp,sizeof(codedata),1,fp);
	}
	fclose(fp);
	fq = fopen("编码结果.dat","wb");
	fp = fopen("file.txt","r");
	char ch;
	int n, i, j = 0;
	unsigned char buffer = 0x00;
	ch = fgetc(fp);
	while(!feof(fp))
	{
		for(i = 0; data[ch].code[i] != '\0'; ++i)
		{
			buffer = buffer << 1;
			if(data[ch].code[i] == '1')
			{
				buffer = buffer | 0x01;
				++j;
			}
			else
			{
				buffer = buffer | 0x00;
				++j;
			}
			if(j == 8)
			{
				fwrite((char *)&buffer, sizeof(buffer), 1, fq);
				j = 0;
			}
		}
		ch = fgetc(fp);
	}
	for(i = 0; data[TAG].code[i] != '\0'; ++i)
	{
		
			buffer = buffer << 1;
			if(data[ch].code[i] == '1')
			{
				buffer = buffer | 0x01;
				++j;
			}
			else
			{
				buffer = buffer | 0x00;
				++j;
			}
			if(j == 8)
			{
				fwrite((char *)&buffer, sizeof(buffer), 1, fq);
				j = 0;
			}
	}
	if(j != 0 && j < 8)
	{
		buffer = buffer << 1;
		++j;
	}
	if(j)
		fwrite((char *)&buffer, sizeof(buffer), 1, fq);
	fclose(fp);
	fclose(fq);
	printf("       编码结束!!!\n\n\n");
} 

char Find(BiTree* T, char code[])
{
	BiTree* p;
	p = T;
	int i;
	for(i = 0; code[i]; ++i)
	{
		if(code[i] == '0')
			p = p->lchild;
		else p = p->rchild;
		if(p->lchild == NULL && p->rchild == NULL)
			return p->ch;
	}
	return 0;
}

void Decoding()		//解码
{
	BiTree* T,* p,* q;
	T = (BiTree *)malloc(sizeof(BiTree));
	T->lchild = NULL;
	T->parent = NULL;
	T->rchild = NULL;
	q = T;
	p = T;
	FILE* fp,* fq;
	codedata data;
	int i = 0;
	fp = fopen("编码表.dat","rb");		//读取编码表文件
	fread(&data,sizeof(codedata),1,fp);
	while(!feof(fp))		//根据编码表生成哈夫曼树
	{
		while(data.code[i])
		{
			if(data.code[i] == '0')		//如果编码为0，则向左进行
			{
				p = q->lchild;
				if(p == NULL)
				{
					p = (BiTree *)malloc(sizeof(BiTree));
					p->parent = q;
					p->lchild = NULL;
					p->rchild = NULL;
					q->lchild = p;
					q = p;
				}
				else q = p;
			}
			else		//如果编码为1，则向右进行
			{
				p = q->rchild;
				if(p == NULL)
				{
					p = (BiTree *)malloc(sizeof(BiTree));
					p->parent = q;
					p->lchild = NULL;
					p->rchild = NULL;
					q->rchild = p;
					q = p;
				}
				else q = p;
			}
			++i;
		}
		p->ch = data.ch;
		q = T;
		i = 0;
		fread(&data,sizeof(codedata),1,fp);
	}
	fclose(fp);
	char ch, code[18];
	fp = fopen("编码结果.dat","rb");
	fq = fopen("解码结果.txt","w");
	unsigned char buffer = 0x00, get = 0x00;
	fread(&buffer,sizeof(buffer), 1, fp);
	i = 0;
	int j = 0;
	while(!feof(fp))
	{
		get = buffer & 0x80;
		if(get == 0x80)
		{
			code[i] = '1';
			code[i+1] = '\0';
			++i;
		}
		else if(get == 0x00)
		{
			code[i] = '0';
			code[i+1] = '\0';
			++i;
		}
		++j;
		buffer = buffer << 1;
		if(j == 8)
		{
			j = 0;
			fread(&buffer,sizeof(buffer), 1, fp);
			if(feof(fp))
				break;
		}
		ch = Find(T, code);
		if(ch == TAG) break;
		if(ch != 0)
		{
			fputc(ch,fq);
			i = 0;
		}
	}
	fclose(fp);
	fclose(fq);
	DestroyBiTree(T);
}

int main()
{
	LinkList* L = NULL;
	L = InitList(L);
	char ch1;
	ch1 = 'z';
	while(ch1 != 'q')
	{
		ch1 = GetInput1();
		switch(ch1)
		{
		case 'a':
			Coding(L);
			printf("      编码表形成完成!!!\n\n\n");
			Line();
			break;
		case 'b': 
			Codefile();
			Line();
			break;
		case 'c':
			Decoding();
			Line();
			printf("      解码完成!!!   \n\n");
			Line();
			break;
		case 'q':
			printf("   Good Bye!!!\n");
			Sleep(800);
			break;
		default:
			break;
		}
	}
	return 0;
}