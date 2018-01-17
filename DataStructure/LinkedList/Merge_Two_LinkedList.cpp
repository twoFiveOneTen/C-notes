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
}

void ShowList(LinkList *L){
	LinkList *p;
	p = L;
	while(p != NULL){
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
}

void ListInsert(LinkList *L,int e){
	LinkList *p,*q;
	q = L;
	p = q->next;
	LinkList *r;
	r = (LinkList *)malloc(sizeof(LinkList));
	r->data = e;
	if(q->data >= e){
		r->next = q;
		return;
	}
	while(p != NULL){
		if(p->data < e) {
			q = p;
			p = p->next;
		}
		else{
			r->next = p;
			q->next = r;
			return;
		}
	}
	r->next = p;
	q->next = r;
}

int Judge(LinkList *A,int e){
	LinkList *p;
	p = A;
	while(p != NULL){
		if(p->data == e) return 1;
		else p = p->next;
	}
	return 0;
}
LinkList *Merge(LinkList *A,LinkList *B){
	LinkList *p;
	p = B;
	while(p != NULL){
		if(Judge(A,p->data) == 1) p = p->next;
		else{
			ListInsert(A,p->data);
			p = p->next;
		}
	}
	return A;
}

int main(){
	LinkList *A = NULL,*B = NULL,*p,*q;
	A = InitList(A);
	int i,j;
	A->data = 0;;
	q = A;
	for(i = 1;i < 11;i++){
		p = (LinkList *)malloc(sizeof(LinkList));
		p->data = 5 * i;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	B = InitList(B);
	B->data = 0;;
	q = B;
	for(j = 1;j < 10;j++){
		p = (LinkList *)malloc(sizeof(LinkList));
		p->data = 3 * j;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	ShowList(A);
	ShowList(B);
	LinkList *C = Merge(A,B);
	ShowList(C);
	system("pause");
	return 0;
}
