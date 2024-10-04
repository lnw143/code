#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
using ll = long long;
const int N = 500, M = N * N / 2, P = 998244353, I = 86583718;
int n,m;
int id(int x,int y) {
	return ((x-1)*m+y+1)/2;
}
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
map<int,map<int,int>> mp;
int det(int n,ll f[N + 2][N + 2]) {
	int sgn=0;
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j) {
			while(f[i][i]) {
				ll d=f[j][i]/f[i][i];
				for(int k=1; k<=n; ++k)
					f[j][k]=(f[j][k]-d*f[i][k]%P)%P;
				swap(f[i],f[j]);
				sgn^=1;
			}
			swap(f[i],f[j]);
			sgn^=1;
		}
	ll ans=sgn?-1:1;
	for(int i=1; i<=n; ++i)
		(ans*=f[i][i])%=P;
	return (ans%P+P)%P;
}
ll f[M + 2][N / 2 + 2];
void add(int i,int j,ll d) { // j+=i*d;
	if(!d) return;
	for(int k=1; k<=m/2; ++k)
		f[j][k]=(f[j][k]+f[i][k]*d%P)%P;
}
int solve() {
	int k=n*m/2;
	for(int i=1; i<=m/2; ++i)
		for(auto [j,v] : mp[i])
			if(j<=m/2) f[i][j]=v;
			else f[i][0]=v;
	for(int i=m/2+1; i<=k; ++i) {
		vector<int> todo;
		for(auto [j,v] : mp[i])
			if(j<=m/2)
				f[i][j]=v;
			else if(j-m/2<i)
				add(j-m/2,i,-v*qpow(f[j-m/2][0],P-2)%P);
			else
				f[i][0]=v;
	}
	ll res=(k-m/2)*(m/2)%2?-1:1;
	for(int i=1; i<=k-m/2; ++i)
		(res*=f[i][0])%=P;
	static ll g[N + 2][N + 2];
	for(int i=1; i<=m/2; ++i)
		for(int j=1; j<=m/2; ++j)
			g[i][j]=f[k-m/2+i][j];
	return (res*det(m/2,g)%P+P)%P;
}
int main() {
	freopen("thewitness.in","r",stdin);
	freopen("thewitness.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n*m%2) return printf("0"),0;
	if(m&1) swap(n,m);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			if((i+j)%2==0) {
				if(1<j) mp[id(i,j)][id(i,j-1)]=1;
				if(j<m) mp[id(i,j)][id(i,j+1)]=1;
				if(1<i) mp[id(i,j)][id(i-1,j)]=I;
				if(i<n) mp[id(i,j)][id(i+1,j)]=I;
			}
	// printf("%d",det(n*m/2,f));
	printf("%d",solve());
	return 0;
}