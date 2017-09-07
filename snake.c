#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 20  //游戏画面尺寸
#define Width 30

// È«¾Ö±äÁ¿
int moveDirection; // Ð¡ÉßÒÆ¶¯Î»ÖÃ£¬ÉÏÏÂ×óÓÒ·Ö±ðÓÃ1£¬2£¬3£¬4±íÊ¾
int food_x,food_y; // Ê³ÎïµÄÎ»ÖÃ
int canvas[High][Width] = {0}; // ¶þÎ¬Êý×é´æ´¢ÓÎÏ·»­²¼ÖÐ¶ÔÓ¦µÄÔªËØ
	// 0Îª¿Õ¸ñ0£¬-1Îª±ß¿ò#£¬-2ÎªÊ³ÎïF£¬1ÎªÉßÍ·@£¬´óÓÚ1µÄÕýÊýÎªÉßÉí*

void gotoxy(int x,int y)  //¹â±êÒÆ¶¯µ½(x,y)Î»ÖÃ
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

// ÒÆ¶¯Ð¡Éß
// µÚÒ»²½É¨ÃèÊý×écanvasËùÓÐÔªËØ£¬ÕÒµ½ÕýÊýÔªËØ¶¼+1
// ÕÒµ½×î´óÔªËØ£¨¼´ÉßÎ²°Í£©£¬°ÑÆä±äÎª0
// ÕÒµ½=2µÄÔªËØ£¨¼´ÉßÍ·£©£¬ÔÙ¸ù¾ÝÊä³öµÄÉÏÏÂ×óÓÒ·½Ïò£¬°Ñ¶ÔÓ¦µÄÁíÒ»¸öÏñËØÖµÉèÎª1£¨ÐÂÉßÍ·£©
void moveSnakeByDirection()
{
	int i,j;
	for (i=1;i<High-1;i++)
		for (j=1;j<Width-1;j++)
			if (canvas[i][j]>0)
				canvas[i][j]++;

	int oldTail_i,oldTail_j,oldHead_i,oldHead_j;
	int max = 0;

	for (i=1;i<High-1;i++)
		for (j=1;j<Width-1;j++)
			if (canvas[i][j]>0)
			{
				if (max<canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}
				if (canvas[i][j]==2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}
			}

	int newHead_i,newHead_j;

	if (moveDirection==1) // ÏòÉÏÒÆ¶¯
	{
		newHead_i = oldHead_i-1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==2) // ÏòÏÂÒÆ¶¯
	{
		newHead_i = oldHead_i+1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==3) // Ïò×óÒÆ¶¯
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j-1;
	}
	if (moveDirection==4) // ÏòÓÒÒÆ¶¯
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j+1;
	}

	// ÐÂÉßÍ·Èç¹û³Ôµ½Ê³Îï
	if (canvas[newHead_i][newHead_j]==-2)
	{
		canvas[food_x][food_y] = 0;
		// ²úÉúÒ»¸öÐÂµÄÊ³Îï
		food_x = rand()%(High-5) + 2;
		food_y = rand()%(Width-5) + 2;
		canvas[food_x][food_y] = -2;

		// Ô­À´µÄ¾ÉÉßÎ²Áô×Å£¬³¤¶È×Ô¶¯+1
	}
	else // ·ñÔò£¬Ô­À´µÄ¾ÉÉßÎ²¼õµô£¬±£³Ö³¤¶È²»±ä
		canvas[oldTail_i][oldTail_j] = 0;

	// ÊÇ·ñÐ¡ÉßºÍ×ÔÉí×²£¬»òÕßºÍ±ß¿ò×²£¬ÓÎÏ·Ê§°Ü
	if (canvas[newHead_i][newHead_j]>0 || canvas[newHead_i][newHead_j]==-1)
	{
		printf("ÓÎÏ·Ê§°Ü£¡\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	else
		canvas[newHead_i][newHead_j] = 1;
}

void startup() // Êý¾Ý³õÊ¼»¯
{
	int i,j;
	
	// ³õÊ¼»¯±ß¿ò
	for (i=0;i<High;i++)
	{
		canvas[i][0] = -1;
		canvas[i][Width-1] = -1;
	}
	for (j=0;j<Width;j++)
	{
		canvas[0][j] = -1;
		canvas[High-1][j] = -1;
	}
	
	// ³õÊ¼»¯ÉßÍ·Î»ÖÃ
	canvas[High/2][Width/2] = 1;
	// ³õÊ¼»¯ÉßÉí£¬»­²¼ÖÐÔªËØÖµ·Ö±ðÎª2,3,4,5....
	for (i=1;i<=4;i++)
		canvas[High/2][Width/2-i] = i+1;

	// ³õÊ¼Ð¡ÉßÏòÓÒÒÆ¶¯
	moveDirection = 4;
	
	food_x = rand()%(High-5) + 2;
	food_y = rand()%(Width-5) + 2;
	canvas[food_x][food_y] = -2;
}

void show()  // ÏÔÊ¾»­Ãæ
{
	gotoxy(0,0);  // ¹â±êÒÆ¶¯µ½Ô­µãÎ»ÖÃ£¬ÒÔÏÂÖØ»­ÇåÆÁ
	int i,j;
	for (i=0;i<High;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (canvas[i][j]==0)
				printf(" ");   //   Êä³ö¿Õ¸ñ
			else if (canvas[i][j]==-1)
				printf("#");   //   Êä³ö±ß¿ò#
			else if (canvas[i][j]==1)
				printf("@");   //   Êä³öÉßÍ·@
			else if (canvas[i][j]>1)
				printf("*");   //   Êä³öÉßÉí*
			else if (canvas[i][j]==-2)
				printf("F");   //   Êä³öÊ³ÎïF
		}
		printf("\n");
	}
	Sleep(100);
}	

void updateWithoutInput()  // ÓëÓÃ»§ÊäÈëÎÞ¹ØµÄ¸üÐÂ
{
	moveSnakeByDirection();
}

void updateWithInput()  // ÓëÓÃ»§ÊäÈëÓÐ¹ØµÄ¸üÐÂ
{
	char input;
	if(kbhit())  // ÅÐ¶ÏÊÇ·ñÓÐÊäÈë
	{
		input = getch();  // ¸ù¾ÝÓÃ»§µÄ²»Í¬ÊäÈëÀ´ÒÆ¶¯£¬²»±ØÊäÈë»Ø³µ
		if (input == 'a') 
		{
			moveDirection = 3;   // Î»ÖÃ×óÒÆ
			moveSnakeByDirection();
		}
		else if (input == 'd')
		{
			moveDirection = 4;  // Î»ÖÃÓÒÒÆ
			moveSnakeByDirection();
		}
		else if (input == 'w')
		{
			moveDirection = 1;  // Î»ÖÃÉÏÒÆ
			moveSnakeByDirection();
		}
		else if (input == 's')
		{
			moveDirection = 2;   // Î»ÖÃÏÂÒÆ
			moveSnakeByDirection();
		}
	}
}

int main()
{
	startup();  // Êý¾Ý³õÊ¼»¯	
	while (1) //  ÓÎÏ·Ñ­»·Ö´ÐÐ
	{
		show();  // ÏÔÊ¾»­Ãæ
		updateWithoutInput();  // ÓëÓÃ»§ÊäÈëÎÞ¹ØµÄ¸üÐÂ
		updateWithInput();  // ÓëÓÃ»§ÊäÈëÓÐ¹ØµÄ¸üÐÂ
	}
	return 0;
}
