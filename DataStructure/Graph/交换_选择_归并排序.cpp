//交换排序
//选择排序
//归并排序（非递归）
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Length 21

void Show(int data[])
{
	int i;
	for(i = 0; i < Length; ++i)
		printf("%4d",data[i]);
	printf("\n");
}

void ExchangeSort(int data[])       //交换排序
{
	printf("交换排序:");
	int temp,i,j;
	for(i = 0; i < Length; ++i)
		for(j = i + 1; j < Length; ++j)
		{
			if(data[i] > data[j])
			{
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
		Show(data);
}

int SelectMin(int data[], int i)
{
	int temp = data[i], j = i,k;
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
	printf("选择排序:");
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
	Show(data);
}

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
	printf("归并排序:");
	int i,j,m,n,l,num,c;
	num = log10((float)Length)/log10((float)2) + 1;
	for(l = 1; l <= num; ++l)
	{
		for(c = 0; c < Length; c = c + (int)pow((float)2,l))
		{
			if(c + (int)pow((float)2,l-1) >= Length) break;       //如果前面不够一半
			else if(c + (int)pow((float)2,l) >= Length)
					Merge(data,c,c + (int)pow((float)2,l-1) - 1,Length - 1);   //前面只够一半长
				else
					Merge(data,c,c+(int)pow((float)2,l - 1) - 1,c+(int)pow((float)2,l) - 1);     //前面足够长
		}
		
	}
	Show(data);
}
int main()
{
	int data1[Length],data2[Length],data3[Length],i;
	for(i = 0; i < Length; ++i)
	{
		data1[i] = rand()%100;
		data2[i] = data1[i];
		data3[i] = data1[i];
	}
	printf("原数组为:");
	Show(data1);
	ExchangeSort(data1);   //交换排序
	SelectSort(data2);          //选择排序
	MergingSort(data3);     //归并排序
	system("pause");
	return 0;
}
