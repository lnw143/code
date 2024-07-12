#include <cstdio>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
const int N = 1e5, inf = 1 << 30;
int n,k,a[N + 2],p[N + 2],cnt;
vector<pair<int,int>> val,val2;
namespace graph {
	void insert(int x,int y);
}
namespace segtree {
	using graph::insert;
	const int S = N << 6;
	int tot,s[S + 2],ls[S + 2],rs[S + 2];
#define mid ((l+r)>>1)
	int build(int l,int r) {
		int u=++tot;
		s[u]=++cnt;
		if(l==r) return u;
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		insert(s[u],s[ls[u]]);
		insert(s[u],s[rs[u]]);
		return u;
	}
	int modify(int u,int l,int r,int x) {
		int v=++tot;
		s[v]=++cnt;
		ls[v]=ls[u],rs[v]=rs[u];
		if(l==r) {
			insert(s[v],val[x].second);
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x);
		else rs[v]=modify(rs[v],mid+1,r,x);
		insert(s[v],s[ls[v]]);
		insert(s[v],s[rs[v]]);
		return v;
	}
	void link(int u,int l,int r,int x,int y,int z) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			insert(z,s[u]);
			return ;
		}
		link(ls[u],l,mid,x,y,z);
		link(rs[u],mid+1,r,x,y,z);
	}
}
namespace graph {
	const int M = N + segtree::S;
	int deg[M + 2];
	vector<int> e[M + 2];
	inline void insert(int x,int y) {
		e[x].push_back(y);
		++deg[y];
	}
	struct cmp {
		bool operator()(int y,int x) {
			if((x>n)!=(y>n)) return x>n;
			if(x>n) return x<y;
			if(a[x]!=a[y]) return a[x]<a[y];
			return x<y;
		}
	};
	vector<int> topo() {
		priority_queue<int,vector<int>,cmp> hp;
		for(int i=1; i<=cnt; ++i)
			if(deg[i]==0) hp.push(i);
		vector<int> ans;
		while(!hp.empty()) {
			int u=hp.top();
			hp.pop();
			if(u<=n) ans.push_back(u);
			for(auto v : e[u])
				if(--deg[v]==0)
					hp.push(v);
		}
		return ans;
	}
}
int main() {
	freopen("minimizing.in","r",stdin);
	freopen("minimizing.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]),val.emplace_back(a[i],i);
	sort(val.begin(),val.end());
	val2=val;
	reverse(val2.begin(),val2.end());
	for(int i=0; i<n; ++i)
		p[val[i].second]=i;
	cnt=n;
	for(int i=n,rt=segtree::build(0,n-1); i>=1; --i) {
		rt=segtree::modify(rt,0,n-1,p[i]);
		auto l=upper_bound(val2.begin(),val2.end(),make_pair(a[i]-k,-1),greater<pair<int,int>>()),
		r=upper_bound(val.begin(),val.end(),make_pair(a[i]+k,n+1));
		segtree::link(rt,0,n-1,0,n-1-(l-val2.begin()),i);
		segtree::link(rt,0,n-1,r-val.begin(),n-1,i);
	}
	for(auto i : graph::topo())
		printf("%d\n",a[i]);
	return 0;
}