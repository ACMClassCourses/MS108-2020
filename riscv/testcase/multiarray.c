#include "io.h"
int a[4][11];
int i;
int j;

struct rec {
    int num;
    int c;
}b[5];

void printNum(int num) {
    outlln(num);
}
int main() {


    for (i = 0; i < 4; i ++) {
        for (j = 0; j < 10; j ++)
            a[i][j] = 888;
    }
    for (i = 0; i < 5; i ++) {
        b[i].num = -1;
    }

    printNum(a[3][9]);
    for (i = 0; i <= 3; i ++)
        for (j = 0; j <= 9; j ++)
            a[i][j] = i * 10 + j;

    for (i = 0; i <= 3; i ++)
        for (j = 0; j <= 9; j ++)
            printNum(a[i][j]);
    a[2][10]=0;
    printNum(a[2][10]);
    b[0].num = -2;
    b[a[2][10]].num = -10;
    printNum(b[0].num);
    printNum(b[1].num);
    return 0;
}
