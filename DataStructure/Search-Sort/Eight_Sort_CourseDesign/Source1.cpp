#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <math.h>

#define Length 20000

typedef struct node1
{
	int num;
	struct node1* next;
}Temp;

typedef struct Tempnode
{
	Temp* r[10], *f[10];
}TempTo;

typedef struct node
{
	int data1[20000];
	int data2[20000];
	int data3[20000];
	int data4[20000];
	int data5[20000];
	int data6[20000];
	int data7[20000];
	int data8[20000];		//数组1到8为无序不同数组
	int data9[20000];		//数组9为正序数组
	int data10[20000];		//数组10为逆序数组
}DATA;

void GetFile(DATA &Data)		//读取文件
{
	FILE* fp;
	fp = fopen("data.dat","rb");
	fread(&Data,sizeof(DATA),1,fp);
	fclose(fp);
}
//冒泡排序
void BubbleSort(int data[])		//冒泡排序
{
	clock_t start, finish;
    double duration;
	start = clock();	//开始计时
	int i,j,temp;
	for(i = 0; i < Length - 1; ++i)
		for(j = 0; j < Length - 1; ++j)
			if(data[j] > data[j+1])
			{
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
			else continue;
	finish = clock();		//结束计时
	duration = double(finish - start);
	printf("%8.1f",duration);
}
//堆排序
void HeapAdjust(int data[], int s, int m)		//堆排序
{
	int rc = data[s-1];          //rc暂存data[s]
	int j;
	for(j = 2 * s; j<=m; j *= 2)
	{
		if(j < m && data[j-1] < data[j]) ++j;        //j是最大值的角标
		if(rc >= data[j-1]) break;
		data[s-1] = data[j-1];
		s = j;
	}
	data[s-1] = rc;
}

void HeapSort(int data[])		//堆排序
{  
    clock_t start, finish;
    double duration;
	start = clock();	//开始计时
	int i,temp;
	for(i = Length/2; i>0; --i)          //八无序堆建成小顶堆
		HeapAdjust(data,i,Length);
	for(i = Length; i > 0; --i)           //形成从大到小数组
	{
		temp = data[i-1];
		data[i-1] = data[0];
		data[0] = temp;
		HeapAdjust(data,1,i-1);
	}
	finish = clock();
	duration = double(finish - start);
	printf("%8.1f",duration);
}
//插入排序
void InsertSort(int data[])		//插入排序
{
	clock_t start, finish;
    double duration;
	start = clock();	//开始计时
	int i,j,temp;
	for(i = 1; i < Length; ++i)
	{
		if(data[i] < data[i-1])
		{
			j = i-1;
			temp = data[i];
			data[i] = data[j];
			while(data[j-1] > temp && j != 0)
			{
				data[j] = data[j-1];		//向前移动
				--j;
			}
			data[j] = temp;		//插入
		}
	}
	finish = clock();
	duration = double(finish - start);
	printf("%8.1f",duration);
}
//选择排序
int SelectMin(int data[], int i)		//找出最小数的角标
{
	int temp = data[i], j = i;
	for(i = i + 1; i < Length; ++i)
	{
		if(data[i] < temp)
		{
			temp = data[i];
			j = i;
		}
		else continue;
	}
	return j;
}

void SelectSort(int data[])           //选择排序
{
	clock_t start, finish;
    double duration;
	start = clock();	//开始计时
	int i,j,temp;
	for(i = 0; i < Length; ++i)
	{
		j = SelectMin(data,i);
		if(i != j)
		{
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	finish = clock();
	duration = double(finish - start);
	printf("%8.1f",duration);
}
//归并排序
void Merge(int data[], int i, int m, int n)
{
	int j,k,l,a = i,b = n,t[Length];
	for(j = m + 1, k = i; i <= m && j <= n; ++k)
	{
		if(data[i] < data[j]) t[k] = data[i++];
		else t[k] = data[j++];
	}
	if(i <= m)
	{
		while(i <= m)
			t[k++] = data[i++];
	}
	if(j <= n)
	{
		while(j <= n)
			t[k++] = data[j++];
	}
	for(l = a; l <= b; ++l)
		data[l] = t[l];          //将部分排序结果传回去
}

void MergingSort(int data[])
{
	clock_t start, finish;
    double duration;
	start = clock();	//开始计时
	int l,num,c;
	num = (int)(log10((float)Length)/log10((float)2) + 1);
	for(l = 1; l <= num; ++l)
	{
		for(c = 0; c < Length; c = c + (int)pow((float)2,l))
		{
			if(c + (int)pow((float)2,l-1) >= Length) break;       //如果前面一半都不够
			else if(c + (int)pow((float)2,l) >= Length)
					Merge(data,c,c + (int)pow((float)2,l-1) - 1,Length - 1);   //前面只够一半长
				else
					Merge(data,c,c+(int)pow((float)2,l - 1) - 1,c+(int)pow((float)2,l) - 1);     //前面足够长
		}
		
	}
	finish = clock();		//结束计时
	duration = double(finish - start);
	printf("%8.1f",duration);
}
//快速排序
void Partition(int data[], int l, int h)         //快速排序
{
	int temp,low = l, high = h;
	int pivotkey = data[low]; 
	while(low < high)         //一次快排
	{
		while(low < high && data[high] >= pivotkey) --high;
		temp = data[low];
		data[low] = data[high];
		data[high] = temp;
		while(low < high && data[low] <= pivotkey) ++low;
		temp = data[low];
		data[low] = data[high];
		data[high] = temp;
	}
	if(low- 1 > l)           //递归思想
		Partition(data,l,low - 1);
	if(low + 1 < h)
		Partition(data,low + 1,h);
}

void PartitionTime(int data[])
{
	clock_t start, finish;
    double duration;
	start = clock();	//开始计时
	Partition(data,0,Length-1);
	finish = clock();		//结束计时
	duration = double(finish - start);
	printf("%8.1f",duration);
}
//希尔排序
void ShellInsert(int data[], int dk)
{
	int i, j, temp;
	for(i = dk+1; i < Length; ++i)
		if(data[i] < data[i-dk])
		{
			j = i-dk;
			temp = data[i];
			data[i] = data[j];
			while(data[j-dk] > temp && j != 0)
			{
				data[j] = data[j-dk];		//向前移动
				j -= dk;
			}
			data[j] = temp;		//插入
		}
}

void ShellSort(int data[])
{
	clock_t start, finish;
    double duration;
	start = clock();	//开始计时
	int dlta[5], t = 5, i;
	for(i = 0; i < t; ++i)
		dlta[i] = 2 * i + 1;
	for(i = 0; i < t; ++i)
		ShellInsert(data, dlta[i]);
	finish = clock();		//结束计时
	duration = double(finish - start);
	printf("%8.1f",duration);
}
//基数排序
void InitTempTo(TempTo &T)
{
	int i;
	for(i = 0; i < 10; ++i)
	{
		T.r[i] = (Temp *)malloc(sizeof(Temp));
		T.r[i]->num = 0;
		T.r[i]->next = NULL;
		T.f[i] = T.r[i];
	}
}

int Len(Temp* L)
{
	int i = 0;
	Temp* p = L->next;
	while(p)
	{
		p = p->next;
		++i;
	}
	return i;
}

void Destroy(Temp* L)		//销毁基数排序产生的链表
{
	Temp* p,* q;
	p = L->next;
	while(p)
	{
		L->next = p->next;
		free(p);
		p = L->next;
	}
	free(L);
	L = NULL;
}

void RadixSort(int data[])		//基数排序
{
	Temp* L,* p,* q,* r;
	TempTo T;
	InitTempTo(T);
	int i, j, k, l;
	L = (Temp *)malloc(sizeof(Temp));
	L->num = -1;
	L->next = NULL;
	q = L;
	for(i = 0; i < Length; ++i)		//把数组转为链表
	{
		p = (Temp *)malloc(sizeof(Temp));
		p->num = data[i];
		p->next = NULL;
		q->next = p;
		q = p;
	}
	clock_t start, finish;
    double duration;
	start = clock();		//开始计时
	for(i = 0, j = 1; i <= 5; ++i)
	{
		p = L->next;
		j *= 10;
		while(p)		//根据数位分成若干段
		{
			k = p->num%j;
			k = k / (j / 10);		//获取特定位数上的数字
			T.f[k]->next = p;
			T.f[k] = p;
			++T.r[k]->num;		//序列结点数自增
			p = p->next;
			T.f[k]->next = NULL;
		}
		r = L;
		for(l = 0; l < 10; ++l)
		{
			if(T.r[l]->num != 0)		//如果此子序列结点数不为空
			{
				r->next = T.r[l]->next;		//把非空子序列连接在一起
				r = T.f[l];
				T.r[l]->num = 0;
				T.r[l]->next = NULL;
				T.f[l] = T.r[l];
			}
			else continue;
		}
	}
	finish = clock();		//结束计时
	duration = double(finish - start);
	printf("%8.1f",duration);
	p = L->next;
	for(i = 0; i < Length; ++i)		//把链表转回数组
	{
		data[i] = p->num;
		p = p->next;
	}
}
//输出各排序时间
void BubbleSortPrint(DATA &Data)
{
	printf("冒泡排序");
	BubbleSort(Data.data1);
	BubbleSort(Data.data2);
	BubbleSort(Data.data3);
	BubbleSort(Data.data4);
	BubbleSort(Data.data5);
	BubbleSort(Data.data6);
	BubbleSort(Data.data7);
	BubbleSort(Data.data8);
	BubbleSort(Data.data9);
	BubbleSort(Data.data10);
	printf("\n");
}

void HeapSortPrint(DATA &Data)
{
	printf(" 堆排序 ");
	HeapSort(Data.data1);
	HeapSort(Data.data2);
	HeapSort(Data.data3);
	HeapSort(Data.data4);
	HeapSort(Data.data5);
	HeapSort(Data.data6);
	HeapSort(Data.data7);
	HeapSort(Data.data8);
	HeapSort(Data.data9);
	HeapSort(Data.data10);
	printf("\n");
}

void InsertSortPrint(DATA &Data)
{
	printf("插入排序");
	InsertSort(Data.data1);
	InsertSort(Data.data2);
	InsertSort(Data.data3);
	InsertSort(Data.data4);
	InsertSort(Data.data5);
	InsertSort(Data.data6);
	InsertSort(Data.data7);
	InsertSort(Data.data8);
	InsertSort(Data.data9);
	InsertSort(Data.data10);
	printf("\n");
}

void SelectSortPrint(DATA &Data)
{
	printf("选择排序");
	SelectSort(Data.data1);
	SelectSort(Data.data2);
	SelectSort(Data.data3);
	SelectSort(Data.data4);
	SelectSort(Data.data5);
	SelectSort(Data.data6);
	SelectSort(Data.data7);
	SelectSort(Data.data8);
	SelectSort(Data.data9);
	SelectSort(Data.data10);
	printf("\n");
}

void MergingSortPrint(DATA &Data)
{
	printf("归并排序");
	MergingSort(Data.data1);
	MergingSort(Data.data2);
	MergingSort(Data.data3);
	MergingSort(Data.data4);
	MergingSort(Data.data5);
	MergingSort(Data.data6);
	MergingSort(Data.data7);
	MergingSort(Data.data8);
	MergingSort(Data.data9);
	MergingSort(Data.data10);
	printf("\n");
}

void PartitionPrint(DATA &Data)
{
	printf("快速排序");
	PartitionTime(Data.data1);
	PartitionTime(Data.data2);
	PartitionTime(Data.data3);
	PartitionTime(Data.data4);
	PartitionTime(Data.data5);
	PartitionTime(Data.data6);
	PartitionTime(Data.data7);
	PartitionTime(Data.data8);
//	PartitionTime(Data.data9);
//	PartitionTime(Data.data10);
	printf("     0.0     0.0");
	printf("\n");
}

void ShellSortPrint(DATA &Data)
{
	printf("希尔排序");
	ShellSort(Data.data1);
	ShellSort(Data.data2);
	ShellSort(Data.data3);
	ShellSort(Data.data4);
	ShellSort(Data.data5);
	ShellSort(Data.data6);
	ShellSort(Data.data7);
	ShellSort(Data.data8);
	ShellSort(Data.data9);
	ShellSort(Data.data10);
	printf("\n");
}

void RadixSortPrint(DATA &Data)		//基数排序
{
	printf("基数排序");
	RadixSort(Data.data1);
	RadixSort(Data.data2);
	RadixSort(Data.data3);
	RadixSort(Data.data4);
	RadixSort(Data.data5);
	RadixSort(Data.data6);
	RadixSort(Data.data7);
	RadixSort(Data.data8);
	RadixSort(Data.data9);
	RadixSort(Data.data10);
	printf("\n");
}
//主函数
int main()
{
	DATA Data;
	GetFile(Data);
	printf("******************************************************************************************\n");
	printf("                                                                            单位：ms\n");
	printf("排序方式  数组一  数组二  数组三  数组四  数组五  数组六  数组七  数组八 正序数组 逆序数组 \n");
	BubbleSortPrint(Data);		//冒泡排序
	GetFile(Data);
	HeapSortPrint(Data);		//堆排序
	GetFile(Data);
	SelectSortPrint(Data);		//选择排序
	GetFile(Data);
	MergingSortPrint(Data);		//归并排序
	GetFile(Data);
	ShellSortPrint(Data);		//希尔排序
	GetFile(Data);
	PartitionPrint(Data);		//快速排序
	GetFile(Data);
	InsertSortPrint(Data);		//插入排序
	GetFile(Data);
	RadixSortPrint(Data);
	system("pause");
	return 0;
}