/*
对于一个字符串，请设计一个算法，只在字符串的单词间做逆序调整，也就是说，字符串由一些由空格分隔的部分组成，你需要将这些部分逆序。
给定一个原字符串A，请返回逆序后的字符串。
例
输入:I am a boy!
输出:boy! a am I
*/

#include <stdio.h>
#include <string.h>
 
 
int main(){
    char str[10000];
    memset(str, 0, 10000);
    gets(str);
    char temp[10000];
    int i, j = 0, k;
    for(i = strlen(str) - 1; i >= 0; --i){
        if(str[i] == ' '){
            for(k = strlen(temp) - 1; k >= 0; --k){
                printf("%c", temp[k]);
            }
            printf(" ");
            memset(temp, 0, 10000);
            j = 0;
        }
        else{
            temp[j] = str[i];
            ++j;
        }
    }
    if(i < 0)
        for(k = strlen(temp) - 1; k >= 0; --k){
                printf("%c", temp[k]);
            }
    return 0;
}
