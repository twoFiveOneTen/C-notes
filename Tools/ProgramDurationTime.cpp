//Visual Studio 2012 Express is recommended.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char *argv[])
{
	clock_t e,s = clock();                //Get start time
	system("pause");
	e = clock() - s;                         //Get end time
	printf("The time is %.3fs\n",(double)e/1000);
	system("pause");
	return 0;
}
