#include "io.h"
// Target: qsort
// Possible optimization: Dead code elimination, common expression, strength reduction
// REMARKS: nothing.
//
//

//int a[10100];
int a[10100];
int n = 10000;

int qsrt(int l, int r) {
    int i = l;
    int j = r;
    int x = a[(l + r) / 2];
    while (i <= j) {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i <= j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    if (l < j) qsrt(l, j);
    if (i < r) qsrt(i, r);
    return 0;
}

int main() {
    int i;
    for (i = 1; i <= n; i++)
        a[i] = n + 1 - i;
    qsrt(1, n);
    for (i = 1; i <= n; i++) {
		outl(a[i]);
		print(" ");
        sleep(1); // to prevent UART buffer from overflowing
	}
    print("\n");
    return 0;
}

