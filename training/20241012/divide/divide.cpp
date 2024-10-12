#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
using ll = long long;
const int N = 19, W = 7, S = 1 << W;
int n,w,m,a[N + 2],b[S + 2],c[S + 2];
bitset<S> f[N + 2][S][S];
void solve() {
	scanf("%d%d%d",&n,&w,&m);
	int s=(1<<w)-1,sum=0;
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		sum=(sum+a[i])&s;
	}
	for(int i=0; i<(1<<w); ++i) scanf("%d",&b[i]);
	for(int i=0; i<(1<<w); ++i) scanf("%d",&c[i]);
	f[0][0][0][0]=1;
	for(int i=0; i<n; ++i)
		for(int j=0; j<(1<<w); ++j)
			for(int k=0; k<(1<<w); ++k)
				for(int l=f[i][j][k]._Find_first(); l<(1<<w); l=f[i][j][k]._Find_next(l)) {
					f[i+1][(j+a[i+1])&s][k][l]=
					f[i+1][j][(k+a[i+1])&s][l]=
					f[i+1][j][k][(l+a[i+1])&s]=
					f[i+1][j][k][l]=1;
				}
	ll ans=-1;
	for(int i=0; i<(1<<w); ++i)
		for(int j=0; j<(1<<w); ++j)
			for(int k=f[n][i][j]._Find_first(); k<(1<<w); k=f[n][i][j]._Find_next(k)) {
				int l=(sum+(3<<w)-i-j-k)&s;
				int h[]={b[i],b[j],b[k],b[l]};
				sort(h,h+4);
				if(h[3]-h[2]>m) continue;
				ans=max(ans,ll(c[i])+c[j]+c[k]+c[l]);
			}
	printf("%lld\n",ans);
	for(int i=0; i<=n; ++i)
		for(int j=0; j<(1<<w); ++j)
			for(int k=0; k<(1<<w); ++k)
				f[i][j][k].reset();
}
int main() {
	freopen("divide.in","r",stdin);
	freopen("divide.out","w",stdout);
	int T;
	for(scanf("%*d%d",&T); T; --T) solve();
	return 0;
}