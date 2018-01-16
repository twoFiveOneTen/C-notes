/*
设计一个程序，对商铺信息管理，商铺信息包括：商铺编号，商铺名，信誉度，（商品名称1，价格1，销量1），（商品名称2，价格2，销量2），（商品名称3，价格3，销量3）…。
假设商品名称包括(毛巾，牙刷，肥皂，牙膏，洗发水，沐浴露等)，每个商铺具有其中事先确定若干商品及价格，由文件输入，销量初始为0。
[基本要求]
（1）建立一个单向链表存储所有商铺信息（至少30个），以编号为序，编号从1开始递增，从文件中读取数据，并能将数据存储在文件。商铺信息结点的数据结构自行设计。
（2）可以增、删商铺。增加商铺，编号自动加一，插入链表尾部；删除商铺以编号为准，并修改后续结点的编号，保持编号连续性。
（3）可以增、删选定商铺中的商品，修改商品价格。
（4）查询某一种商品名称，建立一个双向循环链表，结点信息是包含该商品的所有商铺编号，商铺名，信誉度，商品名称，价格，销量，按销量高至低排序，并可逐一显示。
（5）购买某一商铺的商品，修改单向链表中商品的信息的销量。
（6）任何的商铺信息变化，实现文件存储。
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

typedef struct goods
{
	int code;           //商品位属性，1表示有商品，0表示没有
	char name[20];          //商品名称
	float price;          //商品价格
	int sales;       //商品销量
}Goods;             //商品节点

typedef struct node
{
	int nump;
	char namep[20];
	int creditp;
	Goods goodsp[15];
	struct node * next;
}Link;

typedef struct LinkListnode
{
	char name[20];
	int sales;
	float price;
	int num;
	int credit;
	char namep[20];
	struct LinkListnode * prior;
	struct LinkListnode * next;
}LinkList;

void Line()
{
	printf("***************************************************************************************\n");
}

void Line2()
{
	printf("----------------------\n");
}

void Line3()
{
	printf("@@@@@@@@@@@@@@@\n");
}

Link* InitList(Link* L){
	L = (Link *)malloc(sizeof(Link));
	L->nump = 0;
	L->nump = 'n';
	L->creditp = 0;
	L->next = NULL;
	return L;
}

void GetFile(Link* L, FILE* fp)             //从文件获取所有信息
{
	Link* p,* q,* r;
	q = L;
	int i,j = 0;
	fp = fopen("file.dat","rb");
	if(fp == NULL)
	{
		printf("文件读取失败！\n");
		return;
	}
	p = (Link *)malloc(sizeof(Link));		//读文件前先开辟内存
	q->next = p;
	q = p;
	p->next = NULL;
	fread(p,sizeof(Link),1,fp);
	while(!feof(fp))
	{
		 p = (Link *)malloc(sizeof(Link));
		 q->next = p;
		 r = q;
		 q = p;
		 p->next = NULL;
		 fread(p,sizeof(Link),1,fp);
	}
	r->next = NULL;
	free(q);
	fclose(fp);
}	

int LinkLength(Link* L)
{
	Link* p;
	p = L->next;
	int i = 0;
	while(p != NULL)
	{
		++i;
		p = p->next;
	}
	return i;
}

void ShowLink(Link* L){                    //展示所有商铺、商品信息
	Link* p;
	p = L->next;
	int i,j = 0;
	while(p != NULL)
	{
		Line();
		printf("商铺编号:%d\n",p->nump);
		printf("商铺名称:%s\n",p->namep);
		printf("商铺信誉:%d/5\n",p->creditp);
		Line2();
		i = p->goodsp[0].code;
		if(i == 0) printf("此商铺暂无商品\n");
		else
		{
			printf("                      商品名称   商品价格   商品销量\n");
			while(i != 0)
			{
				printf("                 %12s%11.2f%8d\n",p->goodsp[j].name,p->goodsp[j].price,p->goodsp[j].sales);
				++j;
				i = p->goodsp[j].code;
			}
		}
		j = 0;
		p = p->next;
	}
}

int ShowGoods(Link* L, int i)          //展示指定编号的商铺及其商品信息
{
	Link* p;
	int j,k = 0;
	p = L;
	while(p->nump != i) p = p->next;
	Line();
	printf("商铺编号:%d\n",p->nump);
	printf("商铺名称:%s\n",p->namep);
	printf("商铺信誉:%d/5\n",p->creditp);
	j = p->goodsp[0].code;
	if(j == 0)
	{
		printf("此商铺无商品!\n");
		return 0;
	}
	else
	{
		printf("     商品名称   商品价格   商品销量\n");
		while(j != 0)
		{
			printf("%12s%11.2f%8d\n",p->goodsp[k].name,p->goodsp[k].price,p->goodsp[k].sales);
			++k;
			j = p->goodsp[k].code;
		}
		return 1;
	}
}

int Judge(int j, int k)             //输出符合要求的数
{
	int i= 0;
	while(1 > 0)
	{
		if(j != k)          //判断需要生成数范围
		{
			if(j > k)
			{
				int temp = j;
				j = k;
				k = temp;
			}
			scanf("%d",&i);
			if(i == 0) return 0;          //输入0退出
			else if(i >= j && i <= k) break;       //输入一个正确数字退出循环
			printf("您的输入不正确，请重新输入:");
		}
		else
		{
			scanf("%d",&i);
			if(i == 0) return 0;          //输入0退出
			else if(i >= j) break;       //输入一个正确数字退出循环
			printf("您的输入格式不正确，请重新输入:");
		}
	}
	return i;
}

char GetInput1()             //菜单1子函数
{
	int i = 0;
	char c;
	while(i == 0)
	{
		Line();
		printf("a.展示信息        b.删除商铺\n");
		printf("c.增加商铺        d.修改商品\n");
		printf("e.购买商品        f.查询商品\n");
		printf("q.退出程序");
		c = getch();
		if((c < 'a' || c > 'f') && c != 'q')
		{
			printf("输入错误，请重新输入\n");
		}
		else
		{
			printf("  --%c--\n",c);
			i = 1;
		}
	}
	return c;
}

char GetInput2()                  //菜单2子函数
{
	int i = 0;
	char c;
	Line();
	while(i == 0)
	{
		printf("a.增加商品     b.删除商品\n");
		printf("c.修改价格     q.返回上一层\n");
		c = getch();
		if((c < 'a' || c > 'c') && c != 'q' && c != 's')
		{
			Line();
			printf("错误输入，请重新输入\n");
		}
		else
		{
			printf("  --%c--\n",c);
			i = 1;
		}
	}
	return c;
}

void LinkDelete(Link* L)              //删除商铺
{
	printf("请输入要删除的商铺号(输入0退出删除）:");
	int i = Judge(1,1);
	if(i == 0) return;		//如果输入为0则退出
	Link* p,* q;		//用p, q两个指针来辅助删除一个商铺节点
	p = L->next;
	q = L;
	while(p != NULL)
	{
		if(p->nump == i)
		{
			q->next = p->next;		//把p节点跨过去
			free(p);
			p = q->next;
			break;
		}
		p = p->next;
		q = q->next;
	}
	if(p == NULL)
	{
		printf("无此商铺!\n");
		return;
	}
	else while(p != NULL)
	{
		--p->nump;
		p = p->next;
	}

}

void LinkInsert(Link* L)                   //增加商铺
{
	Link* p,* q;
	q = L;
	p = (Link *)malloc(sizeof(Link));
	printf("请输入商铺名称:");
	scanf("%s",p->namep);
	p->creditp = 5;
	p->goodsp[0].code = 0;
	while(q->next != NULL) q = q->next;
	q->next = p;
	p->next = NULL;
	p->nump = q->nump + 1;
}

int Goodsnum(Link* L)            //查看某商铺内商品数
{
	int i;
	for(i = 0;; ++i)
		if(L->goodsp[i].code == 0) return i;
}

int ShowShop(Link* L)          //展示所有商铺
{
	Link* p;
	p = L->next;
	if(p == NULL)
	{
		printf("暂无商铺！！！\n");
		return 0;
	}
	printf("  商铺编号   商铺名称   信誉度   商品数  \n");
	while(p != NULL)
	{
		printf("  %4d  %12s%8d%8d\n",p->nump,p->namep,p->creditp,Goodsnum(p));
		p = p->next;
	}
	return 1;
}

void GoodsInsert(Link* L)                      //增加商品
{
	int i;
	printf("请输入增加商品的商铺号(输入0以退出增加):");
	i = Judge(1,LinkLength(L));           //获取合规的输入
	if(i == 0) return;
	Link* p;
	p = L->next;
	while(p->nump != i &&p != NULL)             //找寻商铺
	{
		p = p->next;
	}
	if(p == NULL)            //若无此商铺编号
	{
		system("pause");
		printf("无此商铺！\n");
	}
	else if(p->nump = i)
	{
		ShowGoods(L,i);
		int j = 0;
		while(p->goodsp[j].code == 1) ++j;
		p->goodsp[j].code = 1;
		printf("请输入商品名称:");
		scanf("%s",p->goodsp[j].name);
		float a = -1;
		while(a < 0)
		{
			printf("请输入商品价格:");
			scanf("%f",&a);
			if(a < 0) printf("输入有误，重新输入\n");
		}
		p->goodsp[j].price = a;
		p->goodsp[j].sales = 0;
		++j;
		p->goodsp[j].code = 0;
	}
}

void GoodsOperate(Link* L, int f)         //根据f的值为0、1、2，分别进行删除商品、修改价格、购买商品的功能
{
	ShowLink(L);
	int i;
	printf("请输入商品所在商铺号(输入0以退出）:");
	i = Judge(1,10000);
	if(i == 0) return;
	Link* p;
	float temprice;         //temprice用来临时存储用户修改商品价格时输入的数值
	p = L->next;
	while(p != NULL)
	{
		if(p->nump == i) break;
		else p = p->next;
	}
	if(p == NULL)
	{
		printf("未找到此商铺!\n");
		return;
	}
	else
	{
		if(ShowGoods(L,i) == 0) return;
		else
		{
			char ch[20];
			int j,k = 0;
			printf("请输入商品的名字:");
			scanf("%s",&ch);
			j = p->goodsp[0].code;
			while(j != 0)
			{
				if(strcmp(ch,p->goodsp[k].name) == 0) break;
				else
				{
					++k;
					j = p->goodsp[k].code;
				}
			}
			if(j == 0)
			{
				printf("未找到此商品\n");
				return;
			}
			else
			{
				switch(f)
				{
					case 0:           //f为0，进行删除商品
						while(p->goodsp[k].code != 0)
						{
							p->goodsp[k].code = p->goodsp[k + 1].code;
							if(p->goodsp[k].code == 0) break;
							strcpy(p->goodsp[k].name,p->goodsp[k + 1].name);
							p->goodsp[k].price = p->goodsp[k + 1].price;
							p->goodsp[k].sales = p->goodsp[k + 1].sales;
							++k;
						}
						printf("删除成功!!!\n");
						break;
					case 1:          //f为1，进行修改此商品价格
						temprice = -1;
						while(temprice < 0)
						{
							printf("请输入商品新价格:");
							scanf("%f",&temprice);
							if(temprice < 0) printf("输入有误，重新输入\n");
						}
						p->goodsp[j].price = temprice;
						printf("修改成功!!!\n");
						Sleep(700);
						break;
					case 2:           //f为2，进行购买此商品操作，即销量自增1
						++p->goodsp[k].sales;
						printf("购买成功！！！\n");
						break;
				}
			}
		}
	}
}

int Traverse(LinkList* M)           //判断商品查找结果是否按照销量排序
{
	LinkList* p;
	p = M->next;
	while(p->next != M)
	{
		if(p->next->sales > p->sales) return 1;          //如果有乱序现象则返回1
		else p = p->next;
	}
	return 0;
}

void ShowLinkList(LinkList* M)               //展示双向循环链表
{
	LinkList* p;
	p = M->next;
	Line();
	printf("                         %s 查询结果              \n",p->name);
	printf("   所属店铺    店铺编号    店铺信誉     商品价格      商品销量\n");
	while(p != M)
	{
		printf("  %10s%8d %10d      %11.2f%10d\n",p->namep,p->num,p->credit,p->price,p->sales);
		p = p->next;
	}
}

void LinkListSort(LinkList* M)           //查询商品排序
{
	
	LinkList* p,* q;
	int i = 0;
	while(Traverse(M) == 1)     //某次调换商品顺序后，整个双向循环链表仍有乱序现象
	{
		p = M->next->next;
		q = M->next;
		while(p != M)             //查找乱序位置
		{
			if(p->sales > q->sales)              //如果后面的销量比前面大，则对调
			{
				q->prior->next = p;
				p->next->prior = q;
				q->next = p->next;
				p->prior = q->prior;
				q->prior = p;
				p->next = q;
				p = q->next;
			}
			else
			{
				p = p->next;
				q = q->next;
			}
		}
	}
}

void LinkListDestroy(LinkList* M)                //销毁双向循环链表
{
	if(M->next->next == M)
	{
		free(M->next);
		free(M);
		return;
	}
	LinkList* p,* q;
	q = M->next;
	p = q->next;
	while(p != M)
	{
		free(q);
		q = p;
		p = p->next;
	}
	free(q);
	free(M);
}

void Search(Link* L)                    //搜索商品
{
	if(L->next == NULL)                   //无商铺则无法查询
	{
		printf("暂无商铺，无法查询！\n");
		return;
	}
	LinkList* M,* qa,* qb;
	M = (LinkList *)malloc(sizeof(LinkList));
	strcpy(M->name,"n");
	strcpy(M->namep,"n");
	M->num = 0;
	M->sales = 0;
	M->price = 0;
	M->next = M;
	M->prior = M;
	qa = M;
	char ch[20];
	printf("请输入查询商品名称:");
	scanf("%s",&ch);
	Link* p;
	p = L->next;
	while(p != NULL)
	{
		int j,k = 0;
		j = p->goodsp[0].code;
		while(j != 0)                    //如果商品位有商品
		{
			if(strcmp(p->goodsp[k].name,ch) == 0)           //比较是否为所查商品
			{
				qb = (LinkList *)malloc(sizeof(LinkList));
				qb->credit = p->creditp;
				strcpy(qb->name,p->goodsp[k].name);
				strcpy(qb->namep,p->namep);
				qb->num = p->nump;
				qb->price = p->goodsp[k].price;
				qb->sales = p->goodsp[k].sales;
				qb->next = M;
				M->prior = qb;
				qb->prior = qa;
				qa->next = qb;
				qa = qb;
			}
			++k;
			j = p->goodsp[k].code;                //查看下一个商品位有无商品
		}
		p = p->next;
	}
	if(M->next == M)
	{
		printf("未找到此商品!!!\n");
		Sleep(1000);
		return;
	}
	qb->next = M;
	M->prior = qb;
	LinkListSort(M);               //商品按销量排序
	ShowLinkList(M);
	LinkListDestroy(M);           //销毁双向循环链表
}

void Write(Link* L, FILE* fp)                         //写入文件
{
	fp = fopen("file.dat","wb");
	if(fp == NULL)
	{
		printf("file write fail!\n");
		return;
	}
	Link* p;
	p = L->next;
	while(p != NULL)
	{
		fwrite(p,sizeof(Link),1,fp);
		p = p->next;
	}
	fclose(fp);
}

void LinkDestroy(Link* L)                 //销毁商铺链表
{
	Link* p,* q;
	q = L;
	p = L->next;
	while(p != NULL)
	{
		free(q);
		q = p;
		p = p->next;
	}
	free(q);
}

int main()
{
	Link* L = NULL;
	L = InitList(L);
	FILE* fp = NULL;
	GetFile(L,fp);
	char ch1,ch2;          //ch1,ch2用来存储输入的菜单选项
	ch1 = ch2 = 'z';         //初始化为'z'
	while(ch1 != 'q')                 //菜单1
	{
		ch1 = GetInput1();
		switch(ch1)
		{
		case 'a':                  //展示所有信息
			ShowLink(L);
			break;
		case 'b':                     //删除商铺
			ShowLink(L);
			LinkDelete(L);
			ShowLink(L);
			break;
		case 'c':                    //增加商铺
			LinkInsert(L);
			break;
		case 'd':                  //修改商品
			while(ch2 != 'q')                      //菜单2
			{
				ch2 = GetInput2();
				switch(ch2)
				{
				case 'a':               //增加商品
					ShowShop(L);
					GoodsInsert(L);
					Line();
					break;
				case 'b':                 //删除商品
					GoodsOperate(L,0);
					Line();
					break;
				case 'c':
					GoodsOperate(L,1);         //修改商品价格
					break;
				case 'q':
					break;
				default:
					break;
				}
			}
			ch2 = 'z';         //退出菜单2时ch2重新赋值为'z',否则退出菜单2时由于ch2值为'q'而无法再次进入菜单2
			break;
		case 'e':               //购买商品
			GoodsOperate(L,2);
			Sleep(1000);
			break;
		case 'f':
			Line2();
			Search(L);                 //查找商品
			break;
		case 'q':
			Write(L,fp);		//写入文件
			LinkDestroy(L);		//销毁单链表
			printf("Good Bye!!!");
			Sleep(1000);
			break;
		default:
			break;
		}
	}
	return 0;
}
