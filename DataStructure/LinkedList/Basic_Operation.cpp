Visual Studio Express 2012 is recommended.
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct node{
	ElemType data;
	struct node *next;
}*LinkList;

int compare(ElemType e,ElemType f){           //对比
	return e == f;
}

int visit(LinkList L){             //遍历的visit()函数
	LinkList p;
	p = L;
	while(p->next != NULL){
		p = p->next;
		printf("%d\n",p->data);
	}
	return 1;
}

void InitList(LinkList &L){                     //构造空的带头节点的单链表
	L= (LinkList)malloc(sizeof(LinkList));
	L->data = 0;
	L->next = NULL;
}

int DestroyList(LinkList L){                    //销毁单链表
	LinkList p;
	p = L;
	while(L != NULL){
		p = p->next;
		//free(L);
		L = p;
	}
	return 1;
}

void ClearList(LinkList &L){                       //清空单链表
	LinkList p,q;
	p = L->next;
	while(p != NULL){
		q = p;
		p = p->next;
		L->next = p;
		//free(q);
	}
	printf("清空成功\n");
}

int ListEmpty(LinkList L){                  //查看是否为空
	LinkList p;
	p = L;
	if(p == NULL){
		printf("无此表\n");
		return 0;
	}
	if(p->next != NULL) return 1;
	else return 0;
}

int ListLength(LinkList L){          //查看单链表长度
	LinkList p;
	p = L->next;
	int i = 0;
	while(p != NULL){
		++i;
		p = p->next;
	}
	return i;
}

ElemType GetElem(LinkList L,int i,ElemType &e){               //返回某个元素
	if(i < 1||i > ListLength(L)){
		printf("查找序号有误\n");
		exit(0);
	}
	LinkList p;
	p = L;
	int j = 0;
	while(j < i){
		++j;
		p = p->next;
	}
	e = p->data;
	return e;
}

int LocateElem(LinkList L,ElemType e,int (*compare)(ElemType e,ElemType f)){            //定位
	int i = 0;
	LinkList p;
	p = L;
	while(p != NULL){
		++i;
		p = p->next;
		if(compare(e,p->data)) return i;
	}
	printf("未找到\n");
	return 0;
}

ElemType PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e){               //前驱操作
	LinkList p,q;
	p = L;
	while(p->data != cur_e&&p != NULL){
		q = p;
		p = p->next ;
	}
	if(p == NULL){
		printf("前驱操作失败\n");
		return 0;
	}
	else{
		pre_e = q->data;
		return pre_e;
	}
}

ElemType NextElem(LinkList L,ElemType cur_e,ElemType &next_e){                  //后继操作
	LinkList p,q;
	p = q = L;
	while(q->data != cur_e&&p != NULL){
		q = p;
		p = p->next ;
	}
	if(p == NULL){
		printf("后继操作失败\n");
		exit(0);
	}
	else{
		next_e = p->data;
		return next_e;
	}
}

int ListInsert(LinkList &L,int i,ElemType e){                    //插入
	if(i < 1||i > ListLength(L) + 1){
		printf("插入序号有误\n");
		return 0;
	}
	int j = 1;
	LinkList p,q,r;
	p = q = L;
	r = (LinkList )malloc(sizeof(LinkList));
	r->data = e;
	while(j <= i){
		q = p;
		p = p->next;
		++j;
	}
	r->next = p;
	q->next = r;
	return 1;
}

ElemType ListDelete(LinkList L,int i,ElemType e){             //删除
	if(i < 1||i > ListLength(L)){
		printf("删除元素序号错误\n");
		return 0;
	}
	LinkList p,q;
	p = L;
	int j = 0;
	while(j < i){
		q = p;
		p = p->next;
		++j;
	}
	q->next = p->next;
	e = p->data;
	//free(p);
	p = NULL;
	return e;
}

void ListTraverse(LinkList L,int (*visit)(LinkList L)){           //遍历
	if(visit(L) == 1) printf("遍历成功\n");
	else printf("遍历失败\n");
}

int main()
{
	LinkList L,p,q;
	ElemType f = 0;
	InitList(L);             //构造空表
	int i;
	p = L;
	for(i = 1;i < 30;i++){
		q = (LinkList)malloc(sizeof(LinkList));
		q->data = i;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	printf("是否为空：%d\n",ListEmpty(L));
	printf("长度为：%d\n",ListLength(L));
	printf("获取元素:%d\n", GetElem(L, 10, f));
	printf("定位元素：%d\n",LocateElem(L,22,compare));
	printf("前驱：%d\n",PriorElem(L,10,f));
	printf("后继：%d\n",NextElem(L,10,f));
	ListInsert(L,10,100);            
	printf("删除：%d\n", ListDelete(L, 16, f));
	ListTraverse(L,visit);            
	ClearList(L);
	printf("销毁：%d\n",DestroyList(L));
	system("pause");
	return 0;
}
