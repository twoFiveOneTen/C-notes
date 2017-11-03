//推荐使用VS 2012
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

int Search(Sqlist L,int e){
	int i,m = 0,n = 0;
	for(i = 0;i < L.length;i++){
		if(L.elem[i] < e) ++m;
		else if(L.elem[i] > e) ++n;
		else continue;
	}
	if(m == n) return 1;
	else return 0;
}
int Find(Sqlist L){
	int n = L.length,m,o,i;
	if(n % 2 == 0){
		m = n / 2 - 1;
		o = n /2 ;
			if(L.elem[m] == L.elem[o]){
				if(Search(L,L.elem[m]) == 1) return L.elem[m];
				else return -1;
			}
			else return -1;
	}
	else{
		m = (n - 1) / 2;
		if(Search(L,L.elem[m]) == 1) return L.elem[m];
		else return -1;
	}
}

int main(){
	Sqlist L;
	InitList(L);
	int i,m,n;
	printf("Please input n:");
	scanf("%d",&n);
	for(i = 0;i < n;i++){
		printf("\nPlease input:");
		scanf("%d",&L.elem[i]);
		++L.length;
	}
	ShowList(L);
	if(Sort(L) == 1) printf("插入排序成功\n");
	else printf("插入排序失败\n");
	ShowList(L);
	m = Find(L);
	if(m == -1) printf("No this elem!\n");
	else printf("this elem is %d\n",m);
	system("pause");
	free(L.elem);
	return 0;
}
