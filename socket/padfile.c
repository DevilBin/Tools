/*************************************************************************
	> File Name: padfile.c
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: Fri 30 Oct 2015 10:00:46 PM CST
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>

int main() {
    int i, j, k;
    FILE *filefd = fopen("hello.txt", "w+");
    for(i = 0; i < 1024; ++i) {
        for(j = 0; j < 1024; ++j) {
            for(k = 0; k < 1024; ++k) {
                fputs("$", filefd);
            }
        }
    }
    fclose(filefd);
    return 0;
}

