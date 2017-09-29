//Visual Studio 2012 Express is recommended.

#include <stdio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	system("title 猜数游戏");
	int i,j,x,y,n,z,s;
	printf("请输入下限(整数）:");
	scanf("%d",&x);
	printf("\n请输入上限(整数）:");
	scanf("%d",&y);
	z = rand()%(y - x + 1) + x;
	int m =(int)log10(y + 1 - x) + 1;
	n = (int)pow(10,m);
	float p = (float(n - y + x))/float(n);
	//printf("\n0000@%f@0000\n",p);
	if(p >= 0.1&&p <=0.5) i = 3*(int)log10(y + 1 - x) + 2;
	else if(p > 0.5 && p <= 0.9) i = 3*(int)log10(y + 1 - x) + 1;
	else if(p < 0.1) i = 3*(int)log10(y + 1 - x) + 3;
	else i =  3*(int)log10(y + 1 - x);
	printf("您有%d次猜数机会",i);
	for(j = 1;j < i + 1;j++)
	{
		printf("\n请输入您猜的数字:");
		scanf("%d",&s);
		if(s < z) printf("猜小了,");
		else if (s > z) printf("猜大了,");
		else
		{
			printf("您猜对了，数字是%d",z);
			return 0;
		}
		printf("您还有%d次机会",i - j);
	}
	printf("\n正确结果是%d\n",z);
	system("pause");
	return 0;
}
