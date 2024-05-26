#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e6, M = 10, S = 1 << M, T = 7, P = 1e9 + 7;
int n,m,k,f[S + 2][M + 2];
bool e[N + 2][T + 2];
int abs(int x) {
	return x<0?-x:x;
}
int check(const vector<int> &p) {
	for(int i=0; i<p.size(); ++i)
		if(e[p[i]][p[i]-p[(i+1)%p.size()]+k])
			return 0;
	return 1;
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
		if(abs(x-y)<=k) e[x][x-y+k]=true;
	}
	if(n<=10) {
		f[1][1]=1;
		for(int i=1; i<(1<<n); ++i)
			for(int j=1; j<=n; ++j) if(i&(1<<(j-1)))
				for(int l=1; l<=n; ++l) if(!(i&(1<<(l-1)))&&abs(j-l)<=k&&!e[j][j-l+k])
					(f[i|(1<<(l-1))][l]+=f[i][j])%=P;
		int ans=0;
		for(int i=1; i<=n; ++i)
			if(abs(i-1)<=k&&!e[i][i-1+k])
				(ans+=f[(1<<n)-1][i])%=P;
		printf("%d",ans);
		return 0;
	}
	if(k==2) {
		vector<int> p{1},q{1};
		for(int i=2; i<=n; i+=2) p.push_back(i);
		for(int i=n&1?n:n-1; i>1; i-=2) p.push_back(i);
		for(int i=3; i<=n; i+=2) q.push_back(i);
		for(int i=n&1?n-1:n; i>1; i-=2) q.push_back(i);
		printf("%d",check(p)+check(q));
		return 0;
	}
	
	return 0;
}