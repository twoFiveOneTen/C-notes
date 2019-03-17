#include <stdio.h>

typedef struct data
{
	char act;
	int dir;
}code;	//定义结构体code用于存放一个一组进程信息 

int point[10000];	//point数组用于存放各个进程所应该执行的指令，进程命令指针 
int ta[10000];	//标记某进程是否已被读过命令 
int re[666];	//标记某一组进程通信命令是否形成死锁 
	
int judge(code data[10000][9], int p, char a, int to)	//判断本进程是否与所欲通信进程正常通信（可以则返回0） 
{
	char aa;
	int tmp;
	if(data[p][point[p]].act == a && data[p][point[p]].dir == to)	//如果所欲通信进程p为理想状态a，目标为to(to进程为上一层递归的进程） 
	{
		++point[to];	//则p进程和to进程命令执行标记自增  
		++point[p];
		return 0;
	}
	else	//如果p进程和to进程不能完成一次通信。则查看p进程指令内容 
	{
		if(data[p][point[p]].act == 'S') aa = 'R';	//aa为p进程期待下一目标进程所执行动作 
		else aa = 'S';
		if(ta[data[p][point[p]].dir] == 1)	//检测下一目标是否已被读取，如果已读取，则形成死锁 
		{
			return 1;	//形成死锁返回1 
		}
		else ta[data[p][point[p]].dir] = 1;
		tmp = judge(data, data[p][point[p]].dir, aa, p);	//发起递归判断 
		if(tmp == 0) 
		{
			return 0;
		}
	}
}

int start(code data[10000][9], int n, int t)	//此函数负责寻找未正常通信进程并发起判断 
{
	char a;
	int flag;
	int i, j, k;
	while(1)
	{
		for(i = 0; i < 10000; ++i)	//初始化各进程标记 
		{
			ta[i] = 0;
		}
		for(i = 0; i < n; ++i)	//进行未完成通信进程探测 
		{
			if(data[i][point[i]].act != 'A')	//如果进程i尚未完成所有通信，则进行判断 
			{
				ta[i] = 1;
				if(data[i][point[i]].act == 'S') a = 'R';
				else a = 'S';
				flag = judge(data, data[i][point[i]].dir, a, i);
				if(flag == 0) break;
				else	//flag为1，re[]记录t组进程死锁 
				{
					re[t] = 1;
					return 0;
				}
			}
			else if(i == n-1)
			{
				re[t] = 0;
				return 0;
			}
		}
		
	}
}

int init(code data[10000][9])	//整组进程信息结构体和进程命令指针初始化 
{
	int i, j;
	for(i = 0; i < 10000; ++i)
	 for(j = 0; j < 9; ++j)
	 {
	 	data[i][j].act = '\0';
	 	data[i][j].dir = -1;
	 	point[i] = 0;
	 }
}

int main()
{
	code data[10000][9];
	int T, n, tag;
	scanf("%d%d", &T, &n);
	getchar();
	char ch;
	int i, j, k;
	for(i = 0; i < 10000; ++i)
	{
		point[i] = 0;
		ta[i] = 0;
	}
	for(i = 0; i < 666; ++i) re[i] = -1;
	for(i = 0; i < T; ++i)	//三层嵌套循环读取信息， 
	{
		for(j = 0; j < n; ++j)
		{
			for(k = 0; k < 8; ++k)
			{
				ch = getchar();
				if(ch == '\n')
				{
					data[j][k].act = 'A';
					break;
				}
				if(ch == ' ')
				{
					--k;
					continue;
				}
				data[j][k].act = ch;
				scanf("%d", &data[j][k].dir);
				if(k == 7)
				{
					getchar();
					data[j][k+1].act = 'A';
				}
			}
		}
		start(data, n, i);	//读取完一组信息开始处理 
		init(data);
	}
	
	for(i = 0; i < T-1; ++i) printf("%d\n", re[i]);
	printf("%d", re[T-1]);
	return 0;
}
