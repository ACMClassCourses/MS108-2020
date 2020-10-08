#include "io.h"

int main(){
	int i = 0;
	for ( ; i < 0x1fff; i ++)
		outb('a' + i & 15);
	return 0;
}
