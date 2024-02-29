#include<cstdio>
#include<random>
using namespace std;
random_device rd;
mt19937_64 rnd(rd());
int n=200,i;
long long m;
int main() {
	freopen("experiment.in","w",stdout);
	printf("%d %d\n",n,n);
	m=n;
	for(i=1; i<=n; ++i) {
		long long l=rnd()%m+1,r=rnd()%(m-l+1)+l;
		if(rnd()%2) {
			m+=r-l+1;
			printf("D %lld %lld\n",l,r);
		} else
			printf("Q %lld %lld\n",l,r);
	}
	return 0;
}