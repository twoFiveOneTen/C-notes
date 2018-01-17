//逆置单链表

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}*LinkList;

LinkList InitList(LinkList L){
	LinkList head;
	head = (LinkList)malloc(sizeof(int));
	head->data = 0;
	head->next = NULL;
	return head;
}

int Reverse(LinkList L){
	if(L->next->next  == NULL){
		printf("无须逆置\n");
		return 0;
	} 
	LinkList p,q,r;
	p = L->next;
	q = p->next;
	r = q->next;
	p->next = NULL;
	while(r != NULL){
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	L->next = q;
	printf("逆置成功\n");
	return 1;
}

int Show(LinkList L){
	if(L->next == NULL){
		printf("空表，无法展示\n");
		return 0;
	}
	LinkList p;
	p = L->next;
	while(p != NULL){
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
	return 1;
}

int main(){
	LinkList L = 0;
	L = InitList(L);
	int i;
	LinkList p, q = L;
	for(i = 1; i < 41; ++i){
		p = (LinkList)malloc(sizeof(int));
		p->data = i;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	Show(L);
	Reverse(L);
	Show(L);
	system("pause");
	return 0;
}
