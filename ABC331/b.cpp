#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e2 + 2;
int n,s,m,l,f[N + 12],i;
int main() {
	scanf("%d%d%d%d",&n,&s,&m,&l);
	for(i=1; i<n+12; ++i)
		f[i]=1e9;
	for(i=6; i<n+12; ++i)
		f[i]=min(f[i],f[i-6]+s);
	for(i=8; i<n+12; ++i)
		f[i]=min(f[i],f[i-8]+m);
	for(i=12; i<n+12; ++i)
		f[i]=min(f[i],f[i-12]+l);
	printf("%d",*min_element(f+n,f+n+11));
	return 0;
}