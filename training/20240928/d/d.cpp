#include <cstdio>
#include <random>
#include <chrono>
#include <algorithm>
#include <utility>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5, M = 2e5;
int n,m,q;
ll a[N + 2];
map<pair<int,int>,int> mp;
struct oper {
	int op,x,y;
} p[M * 2 + 2];
ll ans[M + 2];
namespace treap {
	const int S = N << 5;
	int tot,ls[S],rs[S],sz[S];
	ll val[S],sum[S];
	unsigned int pri[S];
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int newnode(ll _val) {
		int u=++tot;
		ls[u]=rs[u]=0;
		sz[u]=1;
		val[u]=sum[u]=_val;
		pri[u]=rnd();
		return u;
	}
	void pushup(int u) {
		sz[u]=sz[ls[u]]+sz[rs[u]]+1;
		sum[u]=sum[ls[u]]+sum[rs[u]]+val[u];
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(pri[u]<pri[v]) return rs[u]=merge(rs[u],v),pushup(u),u;
		return ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	void spval(int u,int &x,int &y,ll k) {
		if(!u) return x=y=0,void();
		if(val[u]<=k) x=u,spval(rs[u],rs[u],y,k);
		else y=u,spval(ls[u],x,ls[u],k);
		pushup(u);
	}
	void insert(int &rt,ll _val) {
		int x,y;
		spval(rt,x,y,_val);
		rt=merge(merge(x,newnode(_val)),y);
	}
	void del(int &rt,ll _val) {
		int x,y,z;
		spval(rt,x,z,_val);
		spval(x,x,y,_val-1);
		rt=merge(merge(x,merge(ls[y],rs[y])),z);
	}
	ll rnk_sum(int u,int k) {
		if(!u||!k) return 0;
		if(sz[rs[u]]<k) return val[u]+sum[rs[u]]+rnk_sum(ls[u],k-sz[rs[u]]-1);
		return rnk_sum(rs[u],k);
	}
	void mergeTo(int u,int &rt) {
		if(!u) return ;
		insert(rt,val[u]);
		mergeTo(ls[u],rt);
		mergeTo(rs[u],rt);
	}
}
namespace dsu {
	int fa[N + 2],sz[N + 2],rt[N + 2];
	void init() {
		for(int i=1; i<=n; ++i) fa[i]=i,sz[i]=1,rt[i]=treap::newnode(a[i]);
	}
	int find(int u) {
		return fa[u]==u?u:fa[u]=find(fa[u]);
	}
	void merge(int u,int v) {
		u=find(u),v=find(v);
		if(u==v) return ;
		if(sz[u]<sz[v]) swap(u,v);
		fa[v]=u;
		sz[u]+=sz[v];
		treap::mergeTo(rt[v],rt[u]);
	}
}
namespace tarjan {
	vector<int> e[N + 2];
	int dfc,dfn[N + 2],low[N + 2];
	int scc[N + 2],scnt;
	bool in_stk[N + 2];
	int stk[N + 2],tp;
	void dfs(int u) {
		in_stk[u]=true;
		dfn[u]=low[u]=++dfc;
		stk[++tp]=u;
		for(auto v : e[u])
			if(!dfn[v]) {
				dfs(v);
				low[u]=min(low[u],low[v]);
			} else if(in_stk[v])	
				low[u]=min(low[u],dfn[v]);
		if(low[u]==dfn[u]) {
			++scnt;
			while(stk[tp]!=u) {
				scc[stk[tp]]=scnt;
				in_stk[stk[tp]]=false;
				--tp;
			}
			scc[u]=scnt;
			in_stk[u]=false;
			--tp;
		}
	}
	void solve(const vector<pair<int,int>>& Eg) {
		scnt=0;
		for(auto [x,y] : Eg)
			e[x].push_back(y),
			scc[x]=scc[y]=0;
		for(auto [x,y] : Eg)
			if(!dfn[x])
				dfs(x);
		for(auto [x,y] : Eg)
			e[x].clear(),
			dfn[x]=dfn[y]=
			low[x]=low[y]=
			in_stk[x]=in_stk[y]=0;
		dfc=tp=0;
	}
	bool linked(int x,int y) {
		return scc[x]==scc[y];
	}
}
void solve(int l,int r,const vector<int>& Q) {
	if(l==r) {
		for(auto i : Q)
			if(p[i].op==1) {
				dsu::merge(p[i].x,p[i].y);
			} else if(p[i].op==2) {
				int &rt=dsu::rt[dsu::find(p[i].x)];
				treap::del(rt,a[p[i].x]);
				a[p[i].x]-=p[i].y;
				treap::insert(rt,a[p[i].x]);
			} else if(p[i].op==3) {
				ans[i]=treap::rnk_sum(dsu::rt[dsu::find(p[i].x)],p[i].y);
			}
		return ;
	}
	const int mid=l+r>>1;
	vector<int> Ql,Qr;
	vector<pair<int,int>> egs;
	for(auto i : Q)
		if(i<=mid)
			Ql.push_back(i);
		else if(p[i].op!=1)
			Qr.push_back(i);
		else {
			if(dsu::find(p[i].x)!=dsu::find(p[i].y))
				egs.emplace_back(dsu::find(p[i].x),dsu::find(p[i].y));
		}
	tarjan::solve(egs);
	for(auto i : Q)
		if(mid<i&&p[i].op==1) {
			if(dsu::find(p[i].x)==dsu::find(p[i].y)) continue;
			if(tarjan::linked(dsu::find(p[i].x),dsu::find(p[i].y))) Qr.push_back(i);
			else Ql.push_back(i);
		}
	solve(mid+1,r,Qr);
	solve(l,mid,Ql);
}
int main() {
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	for(int i=1; i<=m; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		mp[make_pair(x,y)]=q+1;
	}
	for(int i=1; i<=q; ++i) {
		auto &[op,x,y]=p[i];
		scanf("%d%d%d",&op,&x,&y);
		if(op==1) {
			mp[make_pair(x,y)]=i;
		} else if(op==2) {
			a[x]+=y;
		}
	}
	int cnt=q;
	for(auto [i,j] : mp)
		if(j==q+1)
			p[++cnt]={1,i.first,i.second};
	vector<int> Q(cnt);
	for(int i=0; i<cnt; ++i) Q[i]=i+1;
	dsu::init();
	solve(1,q+1,Q);
	for(int i=1; i<=q; ++i)
		if(p[i].op==3)
			printf("%lld\n",ans[i]);
	return 0;
}