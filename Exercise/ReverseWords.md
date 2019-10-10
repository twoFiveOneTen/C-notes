<h3>单词逆序</h3>
<b>题目：</b>
<blockquote>对于一个字符串，请设计一个算法，只在字符串的单词间做逆序调整，也就是说，字符串由一些由空格分隔的部分组成，你需要将这些部分逆序。<!--more-->
给定一个原字符串A，请返回逆序后的字符串。</blockquote>

- 时间要求：1s
- 空间限制：65536K

**输入描述:**
```
输入一行字符串str。(1<=strlen(str)<=10000)
```
**输出描述:**
```
返回逆序后的字符串。
```
**示例1**

输入
```
It's a dog!
```
输出
```
dog! a It's
```

**我的作答**
编译器：C++11(clang++3.9)
```cpp
#include <stdio.h>
#include <string.h>

int main()
{
    char str[10000];
    memset(str, 0, 10000);
    gets(str);
    char temp[10000];
    int i, k;
	int j = 0;
    for(i = strlen(str) - 1; i >= 0; --i)
	{
        if(str[i] == ' ')
		{
            for(k = strlen(temp) - 1; k >= 0; --k)
			{
                printf("%c", temp[k]);
            }
            printf(" ");
            memset(temp, 0, 10000);
            j = 0;
        }
        else
		{
            temp[j] = str[i];
            ++j;
        }
    }
    if(i < 0)
        for(k = strlen(temp) - 1; k >= 0; --k)
		{
            printf("%c", temp[k]);
        }
    return 0;
}
```
