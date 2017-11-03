//推荐使用VS 2012

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}LinkList;

LinkList *InitList(LinkList *L){
	L = (LinkList *)malloc(sizeof(LinkList));
	L->data = 0;
	L->next = NULL;
	return L;
	printf("%d\n",L->data);
}
void ListInsert(LinkList *L,int e){
	LinkList *p,*q;
	q = L;
	p = L->next;
	LinkList *r;
	r = (LinkList *)malloc(sizeof(LinkList));
	r->data = e;
	if(q->data > e){
		r->next = p;
		q->next = r;
		int temp = r->data;
		r->data = q->data;
		q->data = temp;
		return;
	}
	else if(q->data == e){
		r->next = p;
		q->next = r;
		return;
	}
	else while(p->data < e){
		if(p->data < q->data) break;
		p = p->next;
		q = q->next;
	}
	r->next = p;
	q->next = r;
}

int ListDelete(LinkList *L){
	LinkList *p,*q;
	int e;
	p = L->next;
	q = L;
	while(p->next != NULL){
		p = p->next;
		q = q->next;
	}
	e = p->data;
	q->next = NULL;
	free(p);
	p = NULL;
	return e;
}

void ShowList(LinkList *L){
	printf("开始展示\n");
	LinkList *p;
	p = L;
	while(p != NULL){
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
}

int ListLength(LinkList *L){
	LinkList *p;
	p = L;
	int i = 0;
	while(p != NULL){
		++i;
		p = p->next;
	}
	return i;
}

void ListDestroy(LinkList *L){
	LinkList *p;
	p = L;
	while(L != NULL){
		L = L->next;
		free(p);
		p = L;
	}
}
void Sort(LinkList *L){
	int i,e;
	int b = ListLength(L);
	for(i = 1;i <= b;i++){
		e = ListDelete(L);
		ListInsert(L,e);
	}
	printf("排序完成\n");
}
int main(){
	LinkList *L = NULL,*p,*q;
	L = InitList(L);
	int i;
	L->data = rand()%40;
	p = L;q = L;
	for(i = 1;i < 20;i++){
		p = (LinkList *)malloc(sizeof(LinkList));
		p->data = rand()%40;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	ShowList(L);
	Sort(L);
	ShowList(L);
	system("pause");
	ListDestroy(L);
	return 0;
}
