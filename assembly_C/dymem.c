#include <stdio.h>
int main(int argc,char **argv){
    char* ch = *(argv+1);
    int n = *ch-'0';
    int p[n];
    for (int i=0;i<n;++i){
        p[i] = i;
    }
    return 0;
}