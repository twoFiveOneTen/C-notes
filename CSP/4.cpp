#include <stdio.h>

typedef struct data
{
	char act;
	int dir;
}code;

int point[10000];
int ta[10000];
int re[666];
	
int judge(code data[10000][9], int p, char a, int to)
{
	char aa;
	int tmp;
	if(data[p][point[p]].act == a && data[p][point[p]].dir == to)
	{
		++point[to];
		++point[p];
		return 0;
	}
	else
	{
		if(data[p][point[p]].act == 'S') aa = 'R';
		else aa = 'S';
		if(ta[data[p][point[p]].dir] == 1)
		{
			return 1;
		}
		else ta[data[p][point[p]].dir] = 1;
		tmp = judge(data, data[p][point[p]].dir, aa, p);
		if(tmp == 0) 
		{
			return 0;
		}
	}
}

int start(code data[10000][9], int n, int t)
{
	char a;
	int flag;
	int i, j, k;
	while(1)
	{
		for(i = 0; i < 10000; ++i)
		{
			ta[i] = 0;
		}
		for(i = 0; i < n; ++i)
		{
			if(data[i][point[i]].act != 'A')
			{
				ta[i] = 1;
				if(data[i][point[i]].act == 'S') a = 'R';
				else a = 'S';
				flag = judge(data, data[i][point[i]].dir, a, i);
				if(flag == 0) break;
				else
				{
					re[t] = 1;
					return 0;
				}
			}
			else if(i == n-1)
			{
				re[t] = 0;
				return 0;
			}
		}
	}
}

int init(code data[10000][9])
{
	int i, j;
	for(i = 0; i < 10000; ++i)
	 for(j = 0; j < 9; ++j)
	 {
	 	data[i][j].act = '\0';
	 	data[i][j].dir = -1;
	 	point[i] = 0;
	 }
}

int main()
{
	code data[10000][9];
	int T, n, tag;
	scanf("%d%d", &T, &n);
	getchar();
	char ch;
	int i, j, k;
	for(i = 0; i < 10000; ++i)
	{
		point[i] = 0;
		ta[i] = 0;
	}
	for(i = 0; i < 666; ++i) re[i] = -1;
	for(i = 0; i < T; ++i)
	{
		for(j = 0; j < n; ++j)
		{
			for(k = 0; k < 8; ++k)
			{
				ch = getchar();
				if(ch == '\n')
				{
					data[j][k].act = 'A';
					break;
				}
				if(ch == ' ')
				{
					--k;
					continue;
				}
				data[j][k].act = ch;
				scanf("%d", &data[j][k].dir);
				if(k == 7)
				{
					getchar();
					data[j][k+1].act = 'A';
				}
			}
		}
		start(data, n, i);
		init(data);
	}
	for(i = 0; i < T-1; ++i) printf("%d\n", re[i]);
	printf("%d", re[T-1]);
	return 0;
}
