#include <cstdio>
#include <vector>
#include <set>
using namespace std;
const int N = 10, S = 1 << N, P = 1e9 + 7, M = 1e6;
int n,m,k,f[S + 2][N + 2],a[M + 2],b[M + 2];
set<int> e[M + 2];
int abs(int x) {
	return x<0?-x:x;
}
int main() {
	freopen("home.in","r",stdin);
	freopen("home.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	if(k==0) return printf("%d",n==1),0;
	if(n==1) return printf("1"),0; // k>0
	if(n==2) return printf("%d",!m),0; // k>0
	if(k==1) return printf("0"),0; // n>2
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].emplace(y);
	}
	if(n<=10) {
		f[1][1]=1;
		for(int i=1; i<(1<<n); ++i)
			for(int j=1; j<=n; ++j) if(i&(1<<(j-1)))
				for(int l=1; l<=n; ++l) if(!(i&(1<<(l-1)))&&abs(j-l)<=k&&!e[j].count(l))
					(f[i|(1<<(l-1))][l]+=f[i][j])%=P;
		int ans=0;
		for(int i=1; i<=n; ++i)
			if(abs(i-1)<=k&&!e[i].count(1))
				(ans+=f[(1<<n)-1][i])%=P;
		printf("%d",ans);
		return 0;
	}
	if(k==2) {
		vector<int> p{1},q{1};
		for(int i=2; i<=n; i+=2) a[++*a]=i;
		for(int i=n&1?n:n-1; i>1; i-=2) a[++*a]=i;
		for(int i=3; i<=n; i+=2) b[++*b]=i;
		for(int i=n&1?n-1:n; i>1; i-=2) b[++*b]=i;
		int ans=2;
		for(auto t : {a, b})
			for(int i=1; i<=n; ++i)
				if(e[t[i]].count(t[i%n+1])) {
					--ans;
					break;
				}
		printf("%d",ans);
	}
	return 0;
}