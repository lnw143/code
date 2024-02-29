#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
int Rnd(int x,int y) {
	uniform_int_distribution<int> d(x,y);
	return d(rnd);
}
int n=1e6,k=Rnd(1,n-2);
int main() {
	freopen(".in","w",stdout);
	printf("%d %d\n",n,k);
	for(int i=1; i<=n; ++i)
		printf("%d ",Rnd(-5e6,5e6));
	return 0;
}