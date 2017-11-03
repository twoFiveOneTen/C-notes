//Visual studio 2012 is recommended.

#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 40
#define ElemType int

typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}Sqlist;

void InitList(Sqlist &L){
	L.elem = (ElemType *)malloc(INITSIZE*sizeof(ElemType));
	L.length = 0;
	L.listsize = INITSIZE;
}

void ShowList(Sqlist L){
	int i;
	for(i = 0;i < L.length;i++) printf("%d ",L.elem[i]);
	printf("\n");
}

int ListInsert(Sqlist L,int k,ElemType e){
	int i = L.length;
	int j;
	for(j = 1;j < k;j++){
		if(L.elem[i - 1] > e){
			L.elem[i] = L.elem[i - 1];
			--i;
			continue;
		}
		else break;
	}
	L.elem[i] = e;
	return 1;
}

ElemType ListDelete(Sqlist L){
	ElemType e;
	int j = 0;
	e = L.elem[0];
	while(j < L.length - 1){
		L.elem[j] = L.elem[j + 1];
		++j;
	}
	return e;
}

int Sort(Sqlist L){
	ElemType e;
	int i;
	for(i = 1;i <= L.length;i++){
		e = ListDelete(L);--L.length;
		ListInsert(L,i,e);++L.length;
	}
	printf("\n");
	return 1;
}

int main(){
	Sqlist L;
	InitList(L);
	int i;
	for(i = 0;i < 30;i++){
		L.elem[i] = rand()%20;
		++L.length;
	}
	ShowList(L);
	if(Sort(L) == 1) printf("插入排序成功\n");
	else printf("插入排序失败\n");
	ShowList(L);
	system("pause");
	free(L.elem);
	return 0;
}
