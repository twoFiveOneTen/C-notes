#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void Line()
{
	printf("--------************--------\n");
}
char GetInput1()
{
	int i = 0;
	char c;
	while(i == 0)
	{
		printf("a.Go Function A     b.Go Function B\n");
		printf("q.Quit");
		c = getch();
		if((c < 'a' || c > 'b') && c != 'q')
		{
			Line();
			printf("Wrong input, once again\n");
			Line();
		}
		else
		{
			printf("  --%c--\n",c);
			i = 1;
			Line();
		}
	}
	return c;
}
char GetInput2()
{
	int i = 0;
	char c;
	while(i == 0)
	{
		printf("a.Go Function AA     b.Go Function BB\n");
		printf("q.Go back");
		c = getch();
		if((c < 'a' || c > 'b') && c != 'q')
		{
			Line();
			printf("Wrong input, once again\n");
			Line();
		}
		else
		{
			printf("  --%c--\n",c);
			i = 1;
			Line();
		}
	}
	return c;
}
int main()
{
	char ch1,ch2;
	ch1 = ch2 = 'z';
	while(ch1 != 'q')
	{
		ch1 = GetInput1();
		switch(ch1)
		{
		case 'a':
			printf("Function A Start\n");
			Line();
			break;
		case 'b':
			while(ch2 != 'q')
			{
				ch2 = GetInput2();
				switch(ch2)
				{
				case 'a':
					printf("Go Go GO\n");
					Line();
					break;
				case 'b':
					printf("Come Come Come\n");
					Line();
					break;
				case 'q':
					break;
				default:
					break;
				}
			}
			break;
		case 'q':
			printf("Good Bye");
			Sleep(2000);
			break;
		default:
			break;
		}
	}
	return 0;
}
