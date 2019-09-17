#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 50
#define ElemType int

typedef struct {
	ElemType *data;
	int length;
	int listsize;
}Sqlist;

int InitList(Sqlist &L) {
	L.data = (ElemType *)malloc(sizeof(ElemType)*INITSIZE);
	if (!L.data) {
		printf("构造空表失败\n");
		return 0;
	}
	L.length = 0;
	L.listsize = INITSIZE;
	return 1;
}

void DestroyList(Sqlist L){      //销毁顺序表
	if(L.data != NULL) free(L.data); 
	printf("销毁完成\n");
}

int Reverse(Sqlist L) {
	if (L.data != NULL) {
		int i = 0,n;
		while (i < (L.length/2)){
			n = L.data[i];                //中间变量n
			L.data[i] = L.data[L.length - i - 1];
			L.data[L.length - i - 1] = n;
			++i;
		}
		printf("逆置完成\n");
		return 1;
	}
	else {
		printf("逆置失败\n");
		return 0;
	}
}

int visit(Sqlist L) {
	if (L.data) {
		int i;
		for (i = 0;i < L.length;i++) {
			printf("%d ", L.data[i]);
		}
		printf("\n");
		return 1;
	}
	else{
		printf("展示失败\n");
		return 0;
	}
}

int main(){
	Sqlist L;
	InitList(L);
	int i;
	for (i = 0;i < 40;i++) {
		L.data[i] = i;
		++L.length;
	}
	printf("长度：%d\n", L.length);
	visit(L);
	Reverse(L);
	visit(L);
	DestroyList(L);
	system("pause");
	return 0;
}
