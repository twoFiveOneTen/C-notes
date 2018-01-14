/*
（1）从文件中读取数据，生成模拟迷宫地图，不少于10行10列。
（2）给出任意入口和出口，显示输出迷宫路线。
*/
//程序所需文件已放在同级目录下，需改名为"data.txt"
#include <stdio.h>
#include <stdlib.h>
#define back -1
#define start -2
#define end -3
#define no -4
#define MAX 200
#define target 4

typedef struct node
{
	int x,y,d;
}Sqnode;

typedef struct
{
	Sqnode *base;
	Sqnode *top;
	int Sqsize;
}Sqstack;

void InitStack(Sqstack &S)                //初始化栈
{
	S.base = (Sqnode *)malloc(sizeof(Sqnode) * MAX);
	S.top = S.base;
	S.Sqsize = MAX;
}

void DestroyStack(Sqstack &S)               //销毁栈
{
	free(S.base);
	S.top = S.base = NULL;
}

void GetFile(int file[10][11])               //从文件读取迷宫信息
{
	int n,i = 0,j,k;
	FILE *fq = fopen("data.txt","r");
	for(j = 0; j < 10; ++j)
		for(k = 0; k < 11; ++k)
		{
			n = (int)fgetc(fq) - 48;          //获取迷宫一格内容
			if(n != 0 && n != 1)
			{
				--k;
				continue;
			}
			file[j][k] = n;
		}
	fclose(fq);
}

void ShowArray(int array[10][11])             //展示迷宫现状
{
	int i,j;
	printf("   j");
	for(j = 0; j < 11; ++j) printf("%2d",j);
	printf("\ni ");
	for(i = 0; i < 13; ++i) printf("■");              //迷宫上边界
	printf("\n");
	for(i = 0; i < 10; ++i)
	{
		printf("%d ■",i);
		for(j = 0; j < 11; ++j)
		{
			if(array[i][j] == 1) printf("■");      //如果值为1表示为墙
			else if(array[i][j] == 2) printf("·");              //值为2表示最终确定路径
			else if(array[i][j] == 3) printf("入");          //值为3表示入口
			else if(array[i][j] == 4) printf("出");            //值为4表示出口
			else printf("□");                   //值为0或5表示为未利用空白

		}
		printf("■\n");
	}
	printf("  ");
	for(i = 0; i < 13; ++i) printf("■");               //迷宫下边界
	printf("\n");
}

void GetGoto(int array[10][11],Sqstack &S)           //获取出入口坐标
{
	int x = -1,y = -1,a = 10,b = 10;
	printf("请输入入口坐标(以i j的形式):");
	while(x < 0 || x > 9 || y < 0 || y > 10 || array[x][y] == 1)
	{
		scanf("%d %d",&x,&y);
		if(x < 0 || x > 9 || y < 0 || y > 10 || array[x][y] == 1) printf("输入坐标有误，重新输入:");
	}
	array[x][y] = 3;
	++S.top;
	S.base->x = x;             //在栈底存入入口坐标
	S.base->y = y;
	S.base->d = 0;
	printf("请输入出口坐标(以i j的形式):");
	while(a < 0 || a > 9 || b < 0 || b > 10 || array[a][b] == 3 || array[a][b] == 1)
	{
		scanf("%d %d",&a,&b);
		if(a < 0 || a > 9 || b < 0 || b > 10 || array[a][b] == 3 || array[a][b] == 1) printf("输入坐标有误，重新输入:");
	}
	array[a][b] = 4;
}

int Find(int array[10][11], int i, int j, int dir, int tar)  //供choose()调用的函数，用于搜寻特定点
{
	switch (dir)               //前进时判断旁边是否有终点
	{
	case 0:           //如果上一步是向右
		++j;
		if(j <= 10)
		{
			if(array[i][j] == tar) return 0;         //如果右面是终点
			else --j;
		}
		else --j;
		++i;
		if(i <= 9)
		{
			if(array[i][j] == tar) return 1;         //如果下面是终点
			else --i;
		}
		else --i;
		--i;
		if(i >= 0)
		{
			if(array[i][j] == tar) return 3;         //如果上面是终点
			else ++i;
		}
		else ++i;
		break;
	case 1:           //如果上一步是向下
		++i;
		if(i <= 9)
		{
			if(array[i][j] == tar) return 1;
			else --i;
		}
		else --i;
		++j;
		if(j <= 10)
		{
			if(array[i][j] == tar) return 0;
			else --j;
		}
		else --j;
		--j;
		if(j >=0)
		{
			if(array[i][j] == tar) return 2;
			else ++j;
		}
		else ++j;
		break;
	case 2:           //如果上一步是向左
		--j;
		if(j >=0)
		{
			if(array[i][j] == tar) return 2;
			else ++j;
		}
		else ++j;
		++i;
		if(i <= 9)
		{
			if(array[i][j] == tar) return 1;
			else --i;
		}
		else --i;
		--i;
		if(i >= 0)
		{
			if(array[i][j] == tar) return 3;
			else ++i;
		}
		else ++i;
		break;
	case 3:           //如果上一步是向上
		--i;
		if(i >= 0)
		{
			if(array[i][j] == tar) return 3;
			else ++i;
		}
		else ++i;
		++j;
		if(j <= 10)
		{
			if(array[i][j] == tar) return 0;
			else --j;
		}
		else --j;
		--j;
		if(j >=0)
		{
			if(array[i][j] == tar) return 2;
			else ++j;
		}
		else ++j;
		break;
	case start:
		++j;
		if(j <= 10)
		{
			if(array[i][j] == tar) return 0;
			else --j;
		}
		else --j;
		++i;
		if(i <= 9)
		{
			if(array[i][j] == tar) return 1;
			else --i;
		}
		else --i;
		--j;
		if(j >=0)
		{
			if(array[i][j] == tar) return 2;
			else ++j;
		}
		else ++j;
		--i;
		if(i >= 0)
		{
			if(array[i][j] == tar) return 3;
			else ++i;
		}
		else ++i;
		if(tar == 1) return end;
		break;
	default:
		break;
	}
	return no;
}

int Choose(int array[10][11],int i,int j,int dir,Sqstack &S)           //判断下一步方向方向的函数
{
	if(dir == back)
		if((S.top-1)->d == (S.top-2)->d)           //如果是直行时后退
		{
			switch((S.top-1)->d)             //判断直行方向
			{
			case 0:         //如果是向右前进时后退
				++i;
				if(i <= 9)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 1;
						return 1;
					}
					else --i;
				}
				else --i;
				--i;
				if(i >= 0)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 3;
						return 3;
					}
					else ++i;
				}
				else ++i;
				break;
			case 1:                 //如果是向下前进时后退
				++j;
				if(j <= 10)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 0;
						return 0;
					}
					else --j;
				}
				else --j;
				--j;
				if(j >= 0)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 2;
						return 2;
					}
					else ++j;
				}
				else ++j;
				break;
			case 2:                 //如果是向左前进时后退
				++i;
				if(i <= 9)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 1;
						return 1;
					}
					else --i;
				}
				else --i;
				--i;
				if(i >= 0)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 3;
						return 3;
					}
					else ++i;
				}
				else ++i;
				break;
			case 3:                 //如果是向上前进时后退
				++j;
				if(j <= 10)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 0;
						return 0;
					}
					else --j;
				}
				else --j;
				--j;
				if(j >= 0)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 2;
						return 2;
					}
					else ++j;
				}
				else ++j;
				break;
			}
			return back;         //如果上一次是在直行退一步之后，四周仍无空格，则继续返回back，再退一格
		}
		else           //如果上一步是转弯时后退
		{
			switch ((S.top-1)->d)       //判断退的那一步的转弯方向
			{
			case 0:                 //如果当时是向右转
				--j;
				if(j >= 0)
				{
					if(array[i][j] == 0)            //则看上一步如果向左转是不是空格
					{
						(S.top-1)->d = 2;
						return 2;
					}
					else ++j;
				}
				else ++j;
				break;
			case 1:                //如果当时是向下转
				--i;
				if(i >= 0)
				{
					if(array[i][j] == 0)            //则看上一步如果向上转是不是空格
					{
						(S.top-1)->d = 3;
						return 3;
					}
					else ++i;
				}
				else ++i;
				break;
			case 2:
				++j;
				if(j <= 10)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 0;
						return 0;
					}
					else --j;
				}
				else --j;
				break;
			case 3:
				++i;
				if(i <= 9)
				{
					if(array[i][j] == 0)
					{
						(S.top-1)->d = 1;
						return 1;
					}
					else --i;
				}
				else --i;
				break;
			}
			return back;             //如果转弯时与原转弯方向相反转向的话依然不是空格，则返回back，再退一格
		}//end else[if((S.top-1)->d == (S.top-2)->d)]
	int temp;
	temp = dir;
	dir = Find(array,i,j,dir,target);
	if(dir != no) return dir;
	else
	{
		dir = temp;
		dir = Find(array,i,j,dir,0);
			if(dir != no) return dir;
			else return back;
	}
}

void Show(Sqstack S)
{
	Sqnode *p;
	p = S.base;
	printf("下面开始展示路径:\n");
	while(p != S.top)
	{
		printf("%d %d\n",p->x,p->y);
		++p;
	}
	printf("路径展示完毕\n");
}

void Search(Sqstack &S,int array[10][11])
{
	int i,j,dir;
	i = S.base->x;           //获取入口横坐标
	j = S.base->y;          //获取入口纵坐标
	dir = Choose(array,i,j,start,S);
	while(S.top-S.base < MAX)
	{
		switch(dir)             //根据dir的值移动下一步
		{
		case 0:              //如果方向值指示向右
			++j;
			if(array[i][j] == 4)          //如果遇到终点
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;             //在上一块的方向指示中输入到达此块的方向值（以下同理）
				++S.top;
				return;
			}
			else                  //如果不是终点
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;
				++S.top;
				array[i][j] = 2;
			}
			break;
		case 1:                  //如果方向值指示向下
			++i;
			if(array[i][j] == 4)          //如果遇到终点
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;
				++S.top;
				return;
			}
			else
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;
				++S.top;
				array[i][j] = 2;
			}
			break;
		case 2:                 //如果方向值指示向左
			--j;
			if(array[i][j] == 4)          //如果遇到终点
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;
				++S.top;
				return;
			}
			else
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;
				++S.top;
				array[i][j] = 2;
			}
			break;
		case 3:              //如果方向值指示向上
			--i;
			if(array[i][j] == 4)          //如果遇到终点
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;
				++S.top;
				return;
			}
			else
			{
				S.top->x = i;
				S.top->y = j;
				(S.top-1)->d = dir;
				++S.top;
				array[i][j] = 2;
			}
			break;
		case back:            //如果方向值指示退一步
			if(S.top - 1 == S.base)
			{
				dir = start;
				break;
			}
			array[i][j] = 5;              //5表示此块已走过且不通
			--S.top;
			i = (S.top-1)->x;
			j = (S.top-1)->y;
			break;
		case end:
			return;
		}
		dir = Choose(array,i,j,dir,S);           //获取下一步的方向
	}
}

int main()
{
	int file[10][11];
	Sqstack S;
	InitStack(S);
	GetFile(file);
	ShowArray(file);
	GetGoto(file,S);
	Search(S,file);
	ShowArray(file);
	if(S.top - 1 == S.base) printf("无出路！！！\n");
	else Show(S);
	system("pause");
	DestroyStack(S);
	return 0;
}
