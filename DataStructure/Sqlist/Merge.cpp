//合并两个正序顺序表为一个正序顺序表，忽略重复多余元素
#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 50

typedef struct{
	int *elem;
	int length;
	int listsize;
}Sqlist;

void Initlist(Sqlist &L){       
	L.elem = (int *)malloc(sizeof(int)*INITSIZE);
	L.length = 0;
	L.listsize = INITSIZE;
}

void DestroyList(Sqlist L){
	if(L.elem != NULL) free(L.elem); 
	printf("Destroy OK\n");
}


int ShowList(Sqlist L){
	int i = 0;
	while(i < L.length)
	{
		printf("%d ",L.elem[i]);
		++i;
	}
	printf("Show OK\n");
	return 0;
}

int ListInsert(Sqlist &L, int e){
	int i;
	for(i = L.length - 1;i >= 0;i--){
		if(L.elem[i] > e){
			L.elem[i + 1] = L.elem[i];
			continue;
		}
		else break;
	}
	L.elem[i + 1] = e;
	++L.length;
	return 1;
}

int Judge(Sqlist A,int e){           //判断A中是否有元素e
	int i;
	for(i = 0; i < A.length; ++i){
		if(A.elem[i] == e) return 1;
		else continue;
	}
	return 0;
}

Sqlist MergeList(Sqlist &A,Sqlist B){             //合并
	int e;
	int i;
	for(i = 0;i < B.length;i++){
		e = B.elem[i];
		if(Judge(A,e) == 1) continue;
		else ListInsert(A,e);
	}
	printf("\n");
	return A;
}

int main(){
	Sqlist A, B, C;
	int e;
	Initlist(A);
	int i;
	for(i = 0; i < 20; ++i){
		A.elem[i] = 5 * i;
		++A.length;
	}
	Initlist(B);
	for(i = 0; i < 20; ++i){
		B.elem[i] = 3 * i;
		++B.length;
	}
	ShowList(A);
	ShowList(B);
	C = MergeList(A, B);
	ShowList(C);
	system("pause");
	return 0;
}
