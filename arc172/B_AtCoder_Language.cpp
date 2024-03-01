#include<cstdio>
#include<algorithm>
using namespace std;
const int N(5e5), P(998244353);
int n,k,l;
long long ans=1;
int main() {
	scanf("%d%d%d",&n,&k,&l);
	for(int i=1; i<=n; ++i) {
		ans*=l-(i-max(1,i-n+k));
		ans%=P;
	}
	printf("%lld",ans);
	return 0;
}