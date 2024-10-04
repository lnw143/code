#include <cstdio>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <utility>
using namespace std;
const int N = 2e5, Q = 1e6;
int n,q,p[N + 2];
vector<pair<int,int>> qr[N + 2];
int ans[Q + 2];
namespace treap {
	const int S = N << 1;
	int tot,rt,sz[S + 2],ls[S + 2],rs[S + 2],maxn[S + 2],val[S + 2];
	unsigned int pri[S + 2];
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int New(int _val) {
		int u=++tot;
		maxn[u]=val[u]=_val;
		sz[u]=1;
		ls[u]=rs[u]=0;
		pri[u]=rnd();
		return u;
	}
	void pushup(int u) {
		sz[u]=sz[ls[u]]+sz[rs[u]]+1;
		maxn[u]=max({maxn[ls[u]],maxn[rs[u]],val[u]});
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(pri[u]<pri[v]) return rs[u]=merge(rs[u],v),pushup(u),u;
		return ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	void sprnk(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		if(k<=sz[ls[u]]) y=u,sprnk(ls[u],x,ls[u],k);
		else x=u,sprnk(rs[u],rs[u],y,k-sz[ls[u]]-1);
		pushup(u);
	}
	void spval(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		if(ls[u]&&maxn[ls[u]]>k||val[u]>k) y=u,spval(ls[u],x,ls[u],k);
		else x=u,spval(rs[u],rs[u],y,k);
		pushup(u);
	}
	int askrnk(int u,int k) {
		if(!u) return -1;
		if(k<=sz[ls[u]]) return askrnk(ls[u],k);
		if(k==sz[ls[u]]+1) return val[u];
		return askrnk(rs[u],k-sz[ls[u]]-1);
	}
	void init() {
		rt=0;
		for(int i=1; i<=n; ++i) rt=merge(rt,New(p[i]));
	}
	int begin(int u) {
		while(u&&ls[u]) u=ls[u];
		return u;
	}
	int end(int u) {
		while(u&&rs[u]) u=rs[u];
		return u;
	}
	void solve() {
		int x,y;
		sprnk(rt,x,y,n/2);
		rt=0;
		while(x&&y) {
			int z;
			if(val[begin(x)]<val[begin(y)])
				spval(x,z,x,val[begin(y)]);
			else
				spval(y,z,y,val[begin(x)]);
			rt=merge(rt,z);
		}
		rt=merge(rt,x|y);
	}
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i) scanf("%d",&p[i]);
	for(int i=1; i<=q; ++i) {
		int t,x;
		scanf("%d%d",&t,&x);
		if(t>n) t=n;
		qr[t].emplace_back(x,i);
	}
	treap::init();
	for(int i=0; i<=n; ++i) {
		for(auto [k,j] : qr[i])
			ans[j]=treap::askrnk(treap::rt,k);
		treap::solve();
	}
	for(int i=1; i<=q; ++i)
		printf("%d\n",ans[i]);
	return 0;
}