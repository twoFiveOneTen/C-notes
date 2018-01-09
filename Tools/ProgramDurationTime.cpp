//此程序可用于获取程序运行时间

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int main(int argc,char *argv[])
{
	clock_t e,s = clock();                //Get start time
	Sleep(1000);
	e = clock() - s;                         //Get end time
	printf("The time is %.3fs\n",(double)e/1000);
	system("pause");
	return 0;
}
