//推荐使用VS 2012

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef struct
{
	int num;
	int state;
	int left;
}Seat;

typedef struct
{
	Seat *data;
	int length;
	int listsize;
}Sqlist;

void InitSqlist(Sqlist &T)
{
	if(!(T.data = (Seat *)malloc(MAXSIZE * sizeof(Seat))))
	{
		printf("内存开辟失败\n");
		return;
	}
	int i;
	for(i = 0;i < MAXSIZE;++i)
	{
		T.data[i].num = i + 1;              //初始化时每个座位号码
		T.data[i].state = 0;                //初始化时每个座位状态，本程序中0表示空缺，1表示已被购买
		if(i % 5 == 0) T.data[i].left = 5;
		else T.data[i].left = 0;
	}
	T.length = MAXSIZE;
	T.listsize = MAXSIZE;
}

void Destroy(Sqlist T)
{
	free(T.data);
}
void Buy(Sqlist &T)
{
	int n,t[100],i,m,j,k,q = 1,r = 0;
	printf("请输入购买次数:");
	scanf("%d",&n);
	while(n <= 0 || n > 100)
	{
		printf("输入格式有误,重新输入:");
		scanf("%d",&n);
	}
	printf("请输入每次购票数量（空格间隔且一次最多购买5张):\n");
	while(q)
	{
		m = 0;
		for(i = 0; i < n; ++i)
		{
			scanf("%d",&t[i]);
			if(t[i] < 1 || t[i] > 5) m = 1;          //如果数据有误，给m赋值1，表示输入有错误
			if(i == n - 1)            //如果数据已经全部读入
				if(m == 1)                //如果读入数据中有错误
				{
					printf("输入数据有误，重新输入:\n");
					break;
				}
				else q = 0;             //输入数据完成且无误后，给q复制0，退出
		}
	}
	for(i = 0; i < n; ++i)             //依次查看每个购票指令的数量并满足之
	{
		if(T.data[0].left == 6)         //如果车厢已无票
		{
			printf("已无票\n");
			continue;             //已无票，进行下一个购票指令
		}
		else
		for(j = 0; j < 100; j = j + 5)               //一排一排查看是否有满足要求的连座
		{
			if(T.data[j].left >= t[i])           //如果此排所剩座位数大于等于购票数
			{
				for(k = 0; k < 5; ++k)                    //具体查看每排的座位
				{
					if(T.data[j + k].state == 0)          //如果座位为空
					{
						T.data[j + k].state = 1;
						printf("%d ",j + k + 1);         //输出座位号
						++r;              //此次已购票计数器加1
						if(r == t[i])      //如果已购票计数器等于此次需要购票数
						{
							T.data[j].left = T.data[j].left - t[i];          //每排剩的座位数减去购票数
							printf("\n");               //输出一个换行
							r = 0;             //此次购票完成，计数器归零
							break;               //此次购票完成，退出此排
						}
					}
					else continue;         //如果座位不为空，则继续看此排下一个座
				}
				break;            //在某排购相邻票成功后退出遍历，进行下一次购票
			}
			else if(j == 95)            //如果查看到车厢尾部时仍无相邻座，则分散购票
			{
				for(q = 0; q < 99; q = q + 5)          //依然是一排一排查看
				{
					if(T.data[q].left >= 1)            //如果此排尚有空座
					{
						for(k = 0; k < 5; ++k)
						{
							if(T.data[q + k].state == 0)      //如果座位为空
							{
								printf("%d ",q + k + 1);
								T.data[q + k].state = 1;
								--T.data[q].left;           //此排所剩座位数减1
								++r;              //此次已购票计数器加1
								if(r == t[i])      //如果已购票计数器等于此次需要购票数
								{
									printf("\n");               //输出一个换行
									break;               //此次购票完成，退出此排
								}
								if(T.data[q].left > 0) continue;    //如果此排尚有空座且此次购票未完成则继续
								else break;
							}
							else continue;
						}//end for(k)
						if(r == t[i])
						{
							r = -1;
							break;
						}
					}//end if(T.data[q].left >= 1)
					else continue;             //如果某排空座为0，则继续看下一排
				}//end for(q)
				if(-1 != r)
				{
					r = 0;
					printf("已无票\n");
					T.data[0].left = 6;       //无票时修改第一排所剩空座数为6，表示车厢已满
					break;
				}
			}//end if(j == 95)
			else continue;          //如果看完某排无相邻，且未看到车厢尾部，则继续看下一排
		}//end for(j)
	}//end for(i)
}

int main()
{
	Sqlist T;
	InitSqlist(T);
	Buy(T);
	system("pause");
	Destroy(T);
	return 0;
}
