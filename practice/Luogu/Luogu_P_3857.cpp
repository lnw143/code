#include <cstdio>
using namespace std;
using ll = long long;
const int N = 50, M = 50;
int n,m;
ll a[M + 2];
char s[N + 2];
ll d[N + 2],tot;
void insert(ll x) {
	for(int i=N; i>=0; --i)
		if((x>>i)&1) {
			if(d[i]) x^=d[i];
			else return d[i]=x,++tot,void();
		}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) {
		scanf("%s",s);
		ll x=0;
		for(int j=0; j<n; ++j)
			if(s[j]=='O')
				x|=1ll<<j;
		insert(x);
	}
	printf("%lld",(1ll<<tot)%2008);
	return 0;
}