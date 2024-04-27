#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
int n=110,m=110;
int main() {
	freopen("matrix.in","w",stdout);
	printf("%d %d\n",n,m);
	for(int i=1; i<=n; ++i,putchar('\n'))
		for(int j=1; j<=m; ++j)
			putchar(rand()%26+'A');
	return 0;
}