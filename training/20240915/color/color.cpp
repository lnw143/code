#include <cstdio>
#include <cassert>
#include <algorithm>
#include <utility>
#include <queue>
#include <vector>
#include <set>
#define mkp make_pair
using namespace std;
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
using ll = long long;
const int N = 1e5, M = 14, S = 1 << M, P = 1e9 + 7;
int n,m,k,deg[N + 2],id[N + 2];
ll f[N + 2][2],g[N + 2][3],ans=1;
ll h[M + 2][S + 2];
bool bz[N + 2];
multiset<pair<int,int>> e[N + 2];
template<class T> void delone(multiset<T>& st,T x) {
	auto it=st.find(x);
	if(it!=st.end()) st.erase(it);
}
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
int main() {
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=m; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].emplace(v,0);
		e[v].emplace(u,0);
	}
	f[1][0]=k-1;
	for(int i=2; i<=n; ++i) {
		f[i][1]=f[i-1][0];
		f[i][0]=f[i-1][1]*(k-1)%P+f[i-1][0]*(k-2)%P;
	}
	g[1][0]=k-2;
	g[1][2]=1;
	for(int i=2; i<=n; ++i) {
		g[i][0]=(g[i-1][1]+g[i-1][2])*(k-2)%P+g[i-1][0]*(k-3)%P;
		g[i][1]=(g[i-1][0]+g[i-1][2])%P;
		g[i][2]=(g[i-1][0]+g[i-1][1])%P;
	}
	heap<pair<int,int>> hp;
	for(int i=1; i<=n; ++i) deg[i]=e[i].size(),hp.emplace(deg[i],i);
	while(hp.size()) {
		auto [d,u]=hp.top();
		hp.pop();
		if(d!=deg[u]||bz[u]) continue;
		vector<pair<int,int>> t(e[u].begin(),e[u].end());
		if(d==1) {
			bz[u]=true;
			(ans*=k-1)%=P;
			int v=t[0].first;
			delone(e[v],mkp(u,0));
			hp.emplace(--deg[v],v);
			continue;
		} else if(d==2) {
			auto [x,wx]=t[0];
			auto [y,wy]=t[1];
			if(x==y) continue;
			bz[u]=true;
			delone(e[x],mkp(u,wx));
			delone(e[y],mkp(u,wy));
			int w=wx+wy+1;
			e[x].emplace(y,w);
			e[y].emplace(x,w);
		} else break;
	}
	vector<int> node;
	for(int i=1; i<=n; ++i)
		if(!bz[i])
			node.push_back(i),
			id[i]=node.size()-1;
	m=node.size();
	assert(m<=14);
	h[0][0]=1;
	for(int i=1; i<=m; ++i) {
		for(int j=1; j<(1<<m); ++j) {
			for(int t=(j-1)&j; ; --t&=j) {
				ll prod=1;
				for(int p=0; p<m; ++p)
					if(((j^t)>>p)&1) {
						for(auto [v,w] : e[node[p]])
							if((t>>id[v])&1) {
								if(w) (prod*=g[w][0]+g[w][1])%=P;
							} else if(((j>>id[v])&1)) {
								if(w==0) {
									prod=0;
									break;
								}
								if(id[v]<p) continue;
								(prod*=f[w][0])%=P;
							}
						if(!prod) break;
					}
				(h[i][j]+=h[i-1][t]*prod%P*(k-i+1)%P)%=P;
				if(!t) break;
			}
		}
	}
	ll sum=0,fac=1;
	for(int i=1; i<=m; ++i) {
		(fac*=i)%=P;
		(sum+=h[i][(1<<m)-1]*qpow(fac,P-2))%=P;
	}
	printf("%lld",ans*sum%P);
	return 0;
}