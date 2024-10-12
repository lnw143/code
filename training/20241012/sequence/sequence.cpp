#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
const int N = 1e5, M = 2e5, K = 5e4;
int n,m,k,a[N + 2],b[M + 2];
bitset<K> f,g,v,all;
void solve() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=m; ++i) scanf("%d",&b[i]);
	all.reset();
	for(int i=0; i<k; ++i) {
		int x;
		scanf("%d",&x);
		v[i]=x;
		all[i]=1;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	g.reset();
	f.reset();
	f[0]=1;
	for(int i=n,j=m; i>=1; --i) {
		g=f&all;
		f.reset();
		for(; b[j]>=a[i]&&j>=1; --j) {
			f^=g<<(b[j]-a[i])%k;
			f^=g>>k-(b[j]-a[i])%k;
		}
	}
	printf("%d\n",(f&v&all).count()&1);
}
int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int T;
	for(scanf("%*d%d",&T); T; --T) solve();
	return 0;
}