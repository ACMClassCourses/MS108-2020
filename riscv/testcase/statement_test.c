#include "io.h"
//考察点：section 8 语句，包括if,while,for,break,continue,return等
//算法：线性筛法求欧拉函数
//样例输入：10
//样例输出：
//1
//2
//2
//4
//2
//6
//4
//6
//4

int N;
int M = 0;
int check[20];

int main() {
    N = inl();
	int i = 0;
	while ( i <= N ) check[i++] = 1;
	int phi[15];
	int P[15];
	phi[1] = 1;
	for (i = 2; ; ++i ) {
		if ( i > N ) break;
		if ( check[i] ) {
			P[++M] = i;
			phi[i] = i - 1;
		}
		int k = i;
		int i;
		for (i = 1; i <= M && (k * P[i] <= N); i++) {
			int tmp = k * P[i];
			if ( tmp > N ) continue;
			check[tmp] = 0;
			if ( k % P[i] == 0) {
				phi[tmp] = phi[k] * P[i];
				break;
			}
			else {
				phi[k * P[i]] = phi[k] * (P[i] - 1);
			}
		}
		outlln(phi[k]);
	}
    return 0;
}
