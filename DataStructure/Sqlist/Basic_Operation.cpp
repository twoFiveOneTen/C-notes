Visual Studio Express 2012 is recommended.
#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 50
#define ElemType int

typedef struct{
	int *data;
	int length;
	int listsize;
}Sqlist;

int compare(ElemType e,Sqlist L,int i){          //比较元素
	if(e == L.data[i]) return 1;
	else return 0;
}

int visit(Sqlist L){                        //遍历的visit()函数
	int i = 0;
	while(i < L.length)
	{
		printf("%d ",L.data[i]);
		++i;
	}
	printf("\n");
	return 0;
}

void Initlist(Sqlist &L){                  //创建一个空的顺序表
	L.data = (ElemType *)malloc(sizeof(ElemType)*INITSIZE);
	L.length = 0;
	L.listsize = INITSIZE;
}

void DestroyList(Sqlist L){      //销毁顺序表
	if(L.data != NULL) free(L.data); 
	printf("销毁完成\n");
}

void ClearList(Sqlist &L){        //清空顺序表
	L.length = 0;
	printf("Clear OK!\n");
}

int ListEmpty(Sqlist L){             //展示顺序表是否为空
	if(&L)
		if(L.length == 0) return 0;
		else return 1;
	else{
		printf("无此表\n");
		return 0;
	}
}

int ListLength(Sqlist L){              //展示顺序表长度
	return L.length;
}

ElemType GetElem(Sqlist L,int i,ElemType &e){       //展示第i个数据
	if(!&L){
		printf("无此表\n");
		return 0;
	}
	else{
		return L.data[i];
	}
}

int LocateElem(Sqlist L,ElemType e,int (* compare)(ElemType a,Sqlist b,int c)){  //定位数据满足compare()的元素
	int i;
	for(i = 0;i <= L.length;i++){
		if(compare(e,L,i) == 1) return i;
	}
	if(i == L.length){
		printf("无满足条件元素\n");
		return 0;
	}
}

ElemType PriorElem(Sqlist L,ElemType cur_e,ElemType &pre_e){           //返回前驱
	int i;
	for(i = 0;i <=L.length;i++){
		if(L.data[i] == cur_e) break;
	}
	if(i == L.length){
		printf("查无此元素\n");
		return 0;
	}
	else{
		pre_e = L.data[i-1];
		return pre_e;
	}
}

ElemType NextElem(Sqlist L,int cur_e,ElemType &next_e){        //返回下一个元素
	int i;
	for(i = 0;i <=L.length;i++){
		if(L.data[i] == cur_e) break;
	}
	if(i == L.length){
		printf("查无此元素\n");
		return 0;
	}
	else{
		next_e = L.data[i+1];
		return next_e;
	}
}

void ListInsert(Sqlist &L,int i,ElemType e){                  //插入
	if(i < 1||i > L.length + 1||L.length == L.listsize){
		printf("error\n");
		return;
	}
	else{
		int j = 0;
		while(i < L.length -j){
			L.data[L.length - j] = L.data[L.length - j - 1];
			++j;
		}
		L.data[L.length - j] = e;
		++L.length;
		printf("插入成功\n");
	}
}

ElemType ListDelete(Sqlist &L,int i,ElemType &e){               //删除元素
	if(i < 1||i > L.length){
		printf("删除序号错误\n");
		return 0;
	}
	else{
		e = L.data[i];
		int j;
		for(j = i - 1;j < L.length;j++){
			L.data[j] = L.data[j + 1];
		}
		L.data[L.length] = 0;
		--L.length;
		return e;
	}
}

int ListTraverse(Sqlist L,int (*visit)(Sqlist a)){                //遍历
	if (L.length == 0) {
		printf("空表，无法遍历\n");
		return 1;
	}
	if(visit(L) == 0) printf("遍历成功\n");
	else{
		printf("操作失败\n");
		return 0;
	}
}

int main()
{
	Sqlist L;
	ElemType e;
	Initlist(L);                //构造空表
	int i;
	for(i = 0;i < 40;i++){
		L.data[i] = i;
		++L.length;
	}
	printf("是否为空：%d\n", ListEmpty(L));
	printf("长度：%d\n", ListLength(L));
	printf("展示元素:%d\n", GetElem(L, 20, e));
	printf("定位元素:%d\n", LocateElem(L, 20, compare));
	printf("前驱:%d\n", PriorElem(L, 20, e));
	printf("后继:%d\n", NextElem(L, 20, e));
	ListTraverse(L, visit);
	ListInsert(L, 15, 2222);
	ListTraverse(L, visit);
	printf("删除：%d\n", ListDelete(L, 2, e));
	ClearList(L);
	printf("长度：%d\n", ListLength(L));
	ListTraverse(L, visit);
	DestroyList(L);
	system("pause");
	return 0;
}
