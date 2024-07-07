#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e3, M = N * (N - 1) / 2, P = 998244353;
using ll = long long;
int n,m,a[N + 2],t[N + 2],p[N + 2];
ll s[N + 2],ans;
ll f[N + 2],g[N + 2],h[N + 2],q[N + 2];
inline ll sum(int l,int r) {
	return s[r-1]-s[l];
}
int main() {
	freopen("mage.in","r",stdin);
	freopen("mage.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(x>y) swap(x,y);
		++t[x];
	}
	{
		vector<int> v;
		for(int i=1; i<=n; ++i) v.push_back(i);
		for(int i=1; i<=n; ++i) {
			p[i]=v[t[i]];
			v.erase(v.begin()+t[i]);
		}
	}
	p[n+1]=n+1;
	f[0]=1;
	/*
		f : count
		g : choosed sum
		h : unchoosed sum
		q : answer
	*/
	for(int i=0; i<=n; ++i) {
		for(int j=i+1,mn=n+2; j<=n+1; ++j)
			if(p[i]<p[j]&&mn>p[j]) {
				mn=p[j];
				(f[j]+=f[i])%=P;
				(g[j]+=g[i]+f[i]*a[j]%P)%=P;
				(h[j]+=h[i]+f[i]*sum(i,j)%P)%=P;
				(q[j]+=q[i]+g[i]*sum(i,j)%P+a[j]*(sum(i,j)*f[i]%P+h[i])%P)%=P;
			}
	}
	printf("%lld",q[n+1]);
	return 0;
}