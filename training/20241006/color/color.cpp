#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
const int N = 1e3, K = 10;
int n,v[N + 2];
ll s[N + 2];
ll f[N + 2][N + 2][K + 2][2];
ll sum(int l,int r) {
	return s[r]-s[l-1];
}
void chmax(ll &x,ll y) {
	if(y>x) x=y;
}
bool ok(int l,int r,int k,int p) {
	if(r-l<1) return false;
	if(l<2||r>n-1) return false;
	if(p) {
		if(r+k+1>n) return false;
	} else {
		if(l-k-1<1) return false;
	}
	return true;
}
void solve() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&v[i]),s[i]=s[i-1]+v[i];
	memset(f,0,sizeof(f));
	for(int i=1; i<=n-2; ++i)
		for(int l=2; l<=n; ++l)
			for(int r=max(l+1,i-K+l); r<=l+i&&r<n; ++r) {
				int k=i-(r-l);
				if(ok(l,r,k,0)) {
					if(ok(l-k-1,r-1,1,1)) chmax(f[l-k-1][r-1][1][1],f[l][r][k][0]+sum(l,r));
					if(ok(l+1,r+1,k+1,0)) chmax(f[l+1][r+1][k+1][0],f[l][r][k][0]+sum(l,r));
				}
				if(ok(l,r,k,1)) {
					if(ok(l+1,r+k+1,1,0)) chmax(f[l+1][r+k+1][1][0],f[l][r][k][1]+sum(l,r));
					if(ok(l-1,r-1,k+1,1)) chmax(f[l-1][r-1][k+1][1],f[l][r][k][1]+sum(l,r));
				}
			}
	printf("%lld\n",max(f[2][n-2][1][1]+sum(2,n-2),f[3][n-1][1][0]+sum(3,n-1))+sum(1,n));
}
int main() {
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}