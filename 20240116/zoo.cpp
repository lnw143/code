#include<cstdio>
#define pw2(x) (1ull<<(x))
using namespace std;
using ull = long unsigned long;
const int N = 1e6, K = 64;
int n,m,c,k,i,p[N + 2],q[N + 2];
ull a[N + 2],s,bz;
ull pwlg2(ull x) {
	ull r=1;
	while(x) r<<=1,x&=x-1;
	return r;
}
int main() {
	freopen("zoo.in","r",stdin);
	freopen("zoo.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&c,&k);
	if(m==0) {
		if(k<64) printf("%llu",pw2(k)-n);
		else if(n==0) printf("18446744073709551616");
		else printf("%llu",~(ull)n+1);
		return 0;
	}
	for(i=1; i<=n; ++i)
		scanf("%llu",&a[i]),s|=a[i];
	for(i=1; i<=m; ++i)
		scanf("%d%d",&p[i],&q[i]),bz|=pw2(p[i]);
	bz^=pw2(k)-1;
	printf("%llu",pwlg2(s|bz)-n);
	return 0;
}