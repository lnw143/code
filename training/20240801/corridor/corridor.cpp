#include <cstdio>
#include <chrono>
#include <random>
#include <utility>
#include <set>
#include <map>
using namespace std;
using ll = long long;
const int N = 5e4, K = 1.5e5;
int n,m,k,Q;
set<int> row[N + 2],col[N + 2];
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
namespace treap {
	const int S = 2 * K + 5;
	ll val[S];
	int ls[S],rs[S],fa[S],sz[S];
	unsigned int pri[S];
	int tot;
	int newnode(ll x) {
		int u=++tot;
		val[u]=x;
		ls[u]=rs[u]=0;
		sz[u]=1;
		pri[u]=rnd();
		return u;
	}
	void pushup(int u) {
		sz[u]=sz[ls[u]]+sz[rs[u]]+1;
		fa[ls[u]]=fa[rs[u]]=u;
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(pri[u]<pri[v]) return rs[u]=merge(rs[u],v),pushup(u),u;
		else return ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	void spval(int u,int &x,int &y,ll k) {
		if(!u) return x=y=0,void();
		if(val[u]<=k) x=u,spval(rs[u],rs[u],y,k);
		else y=u,spval(ls[u],x,ls[u],k);
		pushup(u);
	}
	void sprnk(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		if(sz[ls[u]]<k) x=u,sprnk(rs[u],rs[u],y,k-sz[ls[u]]-1);
		else y=u,sprnk(ls[u],x,ls[u],k);
		pushup(u);
	}
	int findrt(int u) {
		if(!u) return 0;
		while(fa[u]) u=fa[u];
		return u;
	}
	int last(int u) {
		if(!u) return 0;
		while(rs[u]) u=rs[u];
		return u;
	}
}
ll pos(ll x,ll y) {
	return (x-1)*m+y;
}
map<ll,int> ind;
void insert(int x,int y) {
	int u,d,l,r;
	{
		row[x].insert(y);
		auto it=row[x].find(y);
		if(it==row[x].begin()) l=0;
		else {
			auto _it=it;
			l=*--_it;
		}
		{
			auto _it=it;
			++_it;
			if(_it==row[x].end()) r=0;
			else r=*_it;
		}
	}
	{
		col[y].insert(x);
		auto it=col[y].find(x);
		if(it==col[y].begin()) u=0;
		else {
			auto _it=it;
			u=*--_it;
		}
		{
			auto _it=it;
			++_it;
			if(_it==col[y].end()) d=0;
			else d=*_it;
		}
	}
	using namespace treap;
	if(u) u=ind[pos(u,y)*2+1];
	if(d) d=ind[pos(d,y)*2];
	if(l) l=ind[pos(x,l)*2];
	if(r) r=ind[pos(x,r)*2+1];
	int a,b,s,t;
	if(!u) a=0,b=findrt(d);
	else if(!d) a=findrt(u),b=0;
	else spval(findrt(u),a,b,val[u]);
	if(!l) s=0,t=findrt(r);
	else if(!r) s=findrt(l),t=0;
	else spval(findrt(l),s,t,val[l]);
	ll p=pos(x,y)*2,q=p+1;
	p=ind[p]=newnode(p);
	q=ind[q]=newnode(q);
	fa[merge(merge(a,p),t)]=0;
	fa[merge(merge(s,q),b)]=0;
}
pair<int,int> query(int x,int y,int q) {
	using namespace treap;
	if(x==0) {
		if(col[y].empty()) return {n+1,y};
		int rt=findrt(ind[pos(*col[y].begin(),y)*2]);
		if(sz[rt]<q) {
			ll res=val[last(rt)];
			return res&1?pair<int,int>{n+1,(res/2-1)%m+1}:pair<int,int>{(res/2-1)/m+1,m+1};
		} else {
			int s,t;
			sprnk(rt,s,t,q);
			ll res=val[last(s)]/2;
			fa[merge(s,t)]=0;
			return {(res-1)/m+1,(res-1)%m+1};
		}
	} else {
		if(row[x].empty()) return {x,m+1};
		int rt=findrt(ind[pos(x,*row[x].begin())*2+1]);
		if(sz[rt]<q) {
			ll res=val[last(rt)];
			return res&1?pair<int,int>{n+1,(res/2-1)%m+1}:pair<int,int>{(res/2-1)/m+1,m+1};
		} else {
			int s,t;
			sprnk(rt,s,t,q);
			ll res=val[last(s)]/2;
			fa[merge(s,t)]=0;
			return {(res-1)/m+1,(res-1)%m+1};
		}
	}
}
int main() {
	freopen("corridor.in","r",stdin);
	freopen("corridor.out","w",stdout);
	scanf("%*d%d%d%d",&n,&m,&k);
	for(int i=1; i<=k; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		insert(x,y);
	}
	scanf("%d",&Q);
	for(int i=1; i<=Q; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x,y;
			scanf("%d%d",&x,&y);
			insert(x,y);
		} else {
			int x,y,q;
			scanf("%d%d%d",&x,&y,&q);
			auto [s,t]=query(x,y,q);
			printf("%d %d\n",s,t);
		}
	}
	return 0;
}