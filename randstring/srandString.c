/*************************************************************************
	> File Name: srandString.c
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: 2015/12/17 17:35:16
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void get_rand_str(char s[], int num) {
    char * str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz/?*&^%$#@!~";
    int i, strlength;
    char stemp[2] = {0};
    strlength = strlen(str);
    srand((unsigned int)time((time_t *)NULL));

    for(i = 0; i <= num; ++i) {
        sprintf(stemp, "%c", str[(rand() % strlength)]);
        strcat(s, stemp);
    }
}

int main() {
    char s[16] = {0};
    get_rand_str(s, 16);
    printf("%s\n", s);
    return 0;
}

