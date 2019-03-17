#include <stdio.h>

int main()
{
	float mid;
	int max, min, n, i, temp;
	scanf("%d", &n);
	int data[10000];
	for(i = 0; i < n; ++i)
	{
		scanf("%d", &data[i]);
	}
	if(data[n-1] >= data[0])
	{
		max = data[n-1];
		min = data[0];
	}
	else
	{
		max = data[0];
		min = data[n-1];
	}
	if(n % 2 == 1)
	{
		mid = data[n/2];
		printf("%d %.0f %d", max, mid, min);
	}
	else
	{
		temp = data[(n-1)/2] + data[n/2];
		mid = (float)temp / 2;
		if(temp % 2 == 0)
		{
			printf("%d %.0f %d", max, mid, min);
		}
		else
		{
			printf("%d %2.1f %d", max, mid, min);
		}
	}
	return 0;
}
