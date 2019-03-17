#include <stdio.h>

int ifon(char ch[], int n)
{
	int h;
	for(h = 0; h < n; ++h)
	{
		if(ch[h] == 'x' || ch[h] == '/') return h;
	}
	return 0;
}

int main()
{
	int n, i, j, k, flag, sum;
	int re[100];
	scanf("%d", &n);
	char ch[7], ch5[5], ch3[3], temp;
	for(i = 0; i < n; ++i)
	{
		scanf("%s", &ch);
		flag = ifon(ch, 7);
		switch(flag)
		{
			case 0:
				if(ch[1] == '+') ch5[0] = ch[0] + ch[2] -48;
				else ch5[0] = ch[0] - ch[2] -48;
  		 		for(k = 1; k < 5; ++k) ch5[k] = ch[2 + k];
				break;
			case 1:
				if(ch[1] == 'x') ch5[0] = (ch[0]-48) * (ch[2]-48) + 48;
				else ch5[0] = (ch[0]-48) / (ch[2]-48) + 48;
  		 		for(k = 1; k < 5; ++k) ch5[k] = ch[2 + k];
				break;
			case 3:
				ch5[0] = ch[0];
				ch5[1] = ch[1];
				if(ch[3] == 'x') ch5[2] = (ch[2]-48) * (ch[4]-48) + 48;
				else ch5[2] = (ch[2]-48) / (ch[4]-48) + 48;
				ch5[3] = ch[5];
				ch5[4] = ch[6];
				break;
			case 5:
				for(k = 0; k < 4; ++k) ch5[k] = ch[k];
				if(ch[5] == 'x') ch5[4] = (ch[4]-48) * (ch[6]-48) + 48;
				else ch5[4] = (ch[4]-48) / (ch[6]-48) + 48;
				break;
		}
		flag = ifon(ch5, 5);
		switch(flag)
		{
			case 1:
				if(ch5[1] == 'x') ch3[0] = (ch5[0]-48) * (ch5[2]-48) + 48;
				else ch3[0] = (ch5[0]-48) / (ch5[2]-48) + 48;
				ch3[1] = ch5[3];
				ch3[2] = ch5[4];
				break;
			case 3:
				ch3[0] = ch5[0];
				ch3[1] = ch5[1];
				if(ch5[3] == 'x') ch3[2] = (ch5[2]-48) * (ch5[3]-48) + 48;
				else ch3[2] = (ch5[2]-48) / (ch5[3]-48) + 48;
			case 0:
				if(ch5[1] == '+') ch3[0] = (ch5[0]-48) + ch5[2];
				else ch3[0] = ch5[0] - ch5[2] + 48;
				ch3[1] = ch5[3];
				ch3[2] = ch5[4];
				break;
		}
		switch(ch3[1])
		{
			case '+':
				sum = (ch3[0]-48) + (ch3[2]-48);
				break;
			case '-':
				sum = (ch3[0]-48) - (ch3[2]-48);
				break;
			case 'x':
				sum = (ch3[0]-48) * (ch3[2]-48);
				break;
			case '/':
				sum = (ch3[0]-48) / (ch3[2]-48);
				break;
		}
		if(sum == 24) re[i] = 1;
		else re[i] = 0;
	}
	for(i = 0; i < n - 1; ++i)
	{
		if(re[i] == 1) printf("Yes\n");
		else printf("No\n");
	}
	if(re[i] == 1) printf("Yes");
	else printf("No");
	return 0;
}
