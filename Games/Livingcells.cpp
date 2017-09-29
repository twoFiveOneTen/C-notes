//Visual Studio 2012 Express is recommended.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
const int type_live=1;
const int type_dead=0;
const int map_size=20;

int map[20][20];

void initGame();//初始化 
void run();//每一轮的运行 
int getLivingNum(int x, int y);//判断某个格子周边有几个存活的细胞 
void show_map();//把地图的状态打印到屏幕上 

int main()
{
	int sum=0,sum2=0,p=0,w,q;
	float bi;
	system("title 生命游戏");
	system("color B1");
    initGame();
    while(1>0){
	run();
        show_map();
		for(w=0;w<map_size+1;w++)
			for(q=0;q<map_size+1;q++)
			{
				if(map[w][q]==type_live)
				{
					++sum;
					++sum2;
				}
			}
		printf("the num of living is: %d",sum);
		sum=0;
		++p;
	    if(p%10==0) bi=(float)sum2/(map_size*map_size*p);
		printf("\nthe gailv is %f",bi);
        system("cls");
    }
    system("pause");
    return 0;
}
void initGame(){//初始化 
    int i,j;
    srand((unsigned) time(NULL));
    for(i=0;i<map_size;i++){
	for(j=0;j<map_size;j++){
	    map[i][j]=rand()%2;//每一个格子的细胞生死状态都是随机的
        }
    }
}
void run(){//每一轮的运行 
    int i,j,num;
    for(i=0;i<map_size;i++){
	for(j=0;j<map_size;j++){
	    num=getLivingNum(i,j);
	    //按规则决定下一轮的生死状态
            if(num==3){
		map[i][j]=type_live;
            }
            else if(num!=2){
		map[i][j]=type_dead;
            }
        }
    }
}
//获取当前格子周边8个格子的活着的细胞数量
int getLivingNum(int x, int y){
    int i,j;
    int num=0;
    for(i=x-1;i<=x+1;i++){
	if(i<0||i>=map_size){//防止数组下标越界
	continue;
        }
        for(j=y-1;j<=y+1;j++){
	    if(j<0 || j>=map_size){//防止数组下标越界
		continue;
            }
            if(map[i][j]==type_live){
		num++;
            }
        }
    }
    if(map[x][y]==type_live){
		num--;
    }
    return num;
}
void show_map(){//把地图状态输出到屏幕上
	int i,j;
    for(i=0;i<map_size;i++){
	for(j=0;j<map_size;j++){
	    if(map[i][j]==type_live){
		printf(" *");
            }
            else if(map[i][j]==type_dead){
		printf("  ");
            }
        }
        printf("\n");
    }
}
