#include<cstdio>
using namespace std;
int i,j;
int main() {
	freopen(".in","w",stdout);
	printf("5\n");
	for(i=1; i<=5; ++i) {
		for(j=1; j<=(1<<20); ++j)
			putchar('a');
		putchar('\n');
	}
	return 0;
}