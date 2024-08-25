#include <cstdio>
using namespace std;
using ll = long long;
const int N = 10, P = 998244353;
int n,m,s[N + 2];
int e[N + 2],t[N + 2];
int p[N + 2];
bool bz[N + 2];
int ans;
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
void calc() {
	int ban=0;
	for(int i=0; i<n; ++i) {
		if(i) ban|=1<<p[i]-1;
		for(int i=1; i<=n; ++i) t[i]=e[i]&(~ban);
		for(int i=n; i>=1; --i)	
			for(int j=i+1; j<=n; ++j)
				if((t[i]>>(j-1))&1)
					t[i]|=t[j];
		for(int i=1; i<=n; ++i) if(!((ban>>(i-1))&1)) ans+=__builtin_popcount(t[i]);
	}
}
void dfs(int u) {
	if(u>n) {
		calc();
		return ;
	}
	for(int i=1; i<=n; ++i)
		if(!bz[i]) {
			bz[i]=true;
			p[u]=i;
			dfs(u+1);
			bz[i]=false;
		}
}
int main() {
	freopen("bfs.in","r",stdin);
	freopen("bfs.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) scanf("%d",&s[i]);
	for(int i=1; i<n; ++i) e[i]|=1<<i;
	for(int i=1; i<=m; ++i)
		for(int j=i+1; j<=m; ++j)
			e[s[i]]|=1<<s[j]-1;
	dfs(1);
	int fac=1;
	for(int i=1; i<=n; ++i) fac=(ll)fac*i%P;
	printf("%d",ans*qpow(fac,P-2)%P);
	return 0;
}