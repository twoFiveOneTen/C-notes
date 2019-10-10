<h3>城市修建</h3>
<b>题目：</b>
<blockquote>有一个城市需要修建，给你N个民居的坐标X,Y，问把这么多民居全都包进城市的话，城市所需最小面积是多少（注意，城市为平行于坐标轴的正方形）</blockquote>

- 时间限制：1s
- 空间限制：65536K

<!--more-->

**输入描述:**
```
第一行为 N，表示民居数目（2≤N≤1000），后面 N 行为每个居民的坐标
```
**输出描述:**
```
城市所需最小面积
```
**示例1**

**输入**
```
2
0 0
2 2
```
**输出**
```
4
```

**示例2**

**输入**
```
2
0 0
0 3
```
**输出**
```
9
```

**我的作答**
编译器：C++11(clang++3.9)
```cpp
#include <stdio.h>
 
int main()
{
    int i, num;
    long xmin, ymin, xmax, ymax, xtemp, ytemp, area;
    scanf("%d", &num);
    scanf("%ld%ld", &xmin, &ymin);
    xmax = xmin;
    ymax = ymin;
    for(i = 0; i < (num - 1); ++i)
    {
        scanf("%ld%ld", &xtemp, &ytemp);
        if(xtemp < xmin) xmin = xtemp;
        else if(xtemp > xmax) xmax = xtemp;
        if(ytemp < ymin) ymin = ytemp;
        else if(ytemp > ymax) ymax = ytemp;
    }
    xtemp = xmax - xmin;
    ytemp = ymax- ymin;
    area = (xtemp > ytemp)? (xtemp * xtemp) : (ytemp * ytemp);
    printf("%ld", area);
    return 0;
}
```
