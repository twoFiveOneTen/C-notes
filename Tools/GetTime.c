#include <stdio.h> 
#include <stdlib.h>
#include <time.h>  
#include <Windows.h>
void time()  
{  
    time_t timep;  
    struct tm *p;  
    time(&timep);  
    p =localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间  
    //p = gmtime(&timep); //把日期和时间转换为格林威治(GMT)时间的函数  
  
    printf("现在是%d年", 1900+p->tm_year);  
    printf("%d月", 1+p->tm_mon);  
    printf("%d日    ", p->tm_mday);  
    printf("%d:", p->tm_hour);  
    printf("%d:", p->tm_min);  
    printf("%d\n",  p->tm_sec);  
    printf("Weekday:  %d\n", p->tm_wday);  
    printf("今天是今年第%d天\n", p->tm_yday);  
    printf("Isdst:  %d\n", p->tm_isdst); 
	//system("pause");
	//return 0;
} 
int main()
{
	while(1 > 0)
	{
		time();
		Sleep(1000);
		system("cls");
	}
	return 0;
}
