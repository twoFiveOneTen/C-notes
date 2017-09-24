#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void bea()            // 显示分隔
{
	printf("------***************************------\n");
}
int show(int i)           //第一菜单
{
	while(i != 1 && i != 2 && i != 3)
	{
		printf("1.功能一\n2.进入第二层菜单\n3.退出");
		printf("\n请输入您想要进行的操作：");
		scanf_s("%d",&i);
		if(i != 1 &&i != 2 && i != 3)
			{
				printf("无效输入\n");
				bea();
			}
	}
	bea();
	return i;
}
int show2(int j)               //第二菜单
{
	while(j != 1 && j != 2 && j != 3 && j != 4)
	{
		printf("1.功能一\n2.功能二\n3.功能三\n4.返回上一层");
		printf("\n请输入您想要进行的操作：");
		scanf_s("%d",&j);
		if(j != 1 &&j != 2 && j != 3 && j != 4)
		{
				printf("无效输入\n");
				bea();
		}
	}
	bea();
	return j;
}

int main()            //主函数
{
	system("title 多层菜单模板");
	int k1,k2;
	k1 = 1;
	k2 = 1;
	while(k1 == 1)
	{
		int i = 0,j;
		i = show(i);
		switch(i)
		{
			case 1:
				printf("添加功能\n");
				i = 0;
				break;
			case 2:
				while(k2 == 1)        //第二菜单，参照双层菜单的方法可以做出多层菜单
				{
					j = 0;
					j = show2(j);
					switch(j)
					{
					case 1:
						printf("添加功能\n");
						break;
					case 2:
						printf("添加功能\n");
						break;
					case 3:
						printf("添加功能\n1");
						break;
					case 4:
						k2 = 0; //退出第二层菜单
						break;
					}
				}
				i = 0;
				break;
			case 3:
					printf("谢谢使用！再见！");
					Sleep(1500);
					k1 = 0;
			default:
				break;
		}
	}
	return 0;
}
