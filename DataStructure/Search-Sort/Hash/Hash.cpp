//哈希函数，文件中存有30个人的信息
//文件是同级目录下的"data.dat"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Length 100


int number = 0;
 
typedef struct node
{
	char name[20],gender[5];
	int num;
	int state;
}Student;

int Address(Student S, Student T[Length])
{
	int n,m = 1,tag = 0,i,temp;
	for(n = 0; S.name[n]; ++n)
	{
		if(S.name[n] > 64 && S.name[n] < 91)
		{
			if(tag == 0)
			{
				tag = 1;
				m = S.name[n];
			}
			else
			{
				m = (m * S.name[n] * S.name[n + 1])%Length;
				++number;
				if(T[m].state == 1)
				{
					temp = m;
					for(i = 1; T[m].state == 1; ++i)
					{
						m = (temp + (int)pow((float)-1,i + 1) * i * i)%Length;
						++number;
						if(m < 0) m = Length + m;
					}
				}
				return m;
			}
		}
	}
}

void GetFile(Student S[Length])
{
	FILE* fp;
	int i,l;
	Student temp;
	for(i = 0; i < Length; ++i)
		S[i].state = 0;
	fp = fopen("data.dat","rb");
	fread(&temp,sizeof(Student),1,fp);
	while(!feof(fp))
	{
//		printf("%s\n",temp.name);
		l = Address(temp,S);
		strcpy(S[l].name,temp.name);
		strcpy(S[l].gender,temp.gender);
		S[l].num = temp.num;
		S[l].state = temp.state;
		fread(&temp,sizeof(Student),1,fp);
	}
	fclose(fp);
}

void Find(Student S[Length])		//查找同学
{
	printf("请输入查找姓名(注意大小写):");
	char name[20];
	scanf("%s",&name);
	int n = 0,tag = 0,m,temp,i,time = 0;
	for(n = 0; name[n]; ++n)
	{
		if(name[n] > 64 && name[n] < 91)
		{
			if(tag == 0)
			{
				tag = 1;
				m = name[n];
			}
			else
			{
				m = (m * name[n] * name[n + 1])%Length;      //一次定址
				++time;
				if(S[m].state == 0)         //如果定址后为空，则无此人
				{
					printf("查无此人！\n");
					return;
				}
				if(strcmp(name,S[m].name) != 0)
				{
					temp = m;              //temp用来记录第一次哈希结果
					for(i = 1; strcmp(name,S[m].name) != 0; ++i)
					{
						m = (temp + (int)pow((float)-1,i + 1) * i * i)%Length;
						++time;
						if(S[m].state == 0)
						{
							printf("查无此人！\n");
							return;
						}
						if(m < 0) m = Length + m;
					}
				}
				break;
			}
		}
		if(n == strlen(name) - 1)
		{
			printf("请注意输入格式!!!\n");
			return;
		}
	}
	printf("姓名:%s\n",S[m].name);
	printf("学号:%d\n",S[m].num);
	printf("性别：%s\n",S[m].gender);
	printf("查询%d次\n",time);
}

int main()
{
	Student S[Length];
	FILE* fp;
	GetFile(S);
	printf("平均查找次数：%f\n",(float)number/30);
	Find(S);
	system("pause");
	return 0;
	//H(ZhangKangkang) = (Z * K * a) mod Length;
	//H2 = (H(ZhangKangkang) + di) mod Length;
}
