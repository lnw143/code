#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 3e5, logN = 20;
int n,q;
vector<int> e[N + 2];
int anc[logN][N + 2],siz[N + 2],wson[N + 2],dep[N + 2];
int dfc,dfn[N + 2],low[N + 2],pos[N + 2],top[N + 2];
void dfs(int u,int p) {
	anc[0][u]=p;
	for(int i=1; i<logN; ++i)
		anc[i][u]=anc[i-1][anc[i-1][u]];
	dep[u]=dep[p]+1;
	siz[u]=1;
	for(auto v : e[u])
		if(v!=p) {
			dfs(v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[wson[u]]) wson[u]=v;
		}
}
void dfs2(int u,int p,int t) {
	top[u]=t;
	pos[dfn[u]=++dfc]=u;
	if(wson[u]) {
		dfs2(wson[u],u,t);
		for(auto v : e[u])
			if(v!=p&&v!=wson[u])
				dfs2(v,u,v);
	}
	low[u]=dfc;
}
namespace fenwick {
	struct ftree {
		ll s[N + 2];
		void add(int u,ll x) {
			for(; u<=n; u+=u&-u) s[u]+=x;
		}
		ll sum(int u) {
			ll r=0;
			for(; u; u&=u-1) r+=s[u];
			return r;
		}
	} t1,t2;
	void add(int u,ll x) {
		t1.add(u,x);
		t2.add(u,u*x);
	}
	void add(int l,int r,ll x) {
		add(l,x);
		add(r+1,-x);
	}
	ll sum(int u) {
		return (u+1)*t1.sum(u)-t2.sum(u);
	}
	ll sum(int l,int r) {
		return sum(r)-sum(l-1);
	}
	int find_mid(ll s) {
		int u=0;
		ll s1=0,s2=0;
		for(int i=logN-1; i>=0; --i) {
			int v=u+(1<<i);
			if(v>n) continue;
			if((v+1)*(s1+t1.s[v])-(s2+t2.s[v])<=s) {
				s1+=t1.s[v];
				s2+=t2.s[v];
				u=v;
			}
		}
		return u+1;
	}
}
int solve() {
	const ll sum=fenwick::sum(1,n);
	int c=pos[fenwick::find_mid(sum/2)];
	if(fenwick::sum(dfn[c],low[c])*2>sum) return c;
	for(int i=logN-1; i>=0; --i)
		if(fenwick::sum(dfn[anc[i][c]],low[anc[i][c]])*2<=sum)
			c=anc[i][c];
	return anc[0][c];
}
inline char gc() {
	static char buf[1<<16],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
void read(int &x) {
	x=0;
	char c=gc();
	while(c>'9'||c<'0') c=gc();
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c^48);
}
char pbuf[1<<22],*p1=pbuf;
inline void pc(char c) {
	*p1++=c;
}
void write(ll x) {
	static char stk[1<<6];
	char *p=stk;
	do *p++=(x%10)^48; while(x/=10);
	while(p!=stk) pc(*--p);
}
int main() {
	freopen("yyl.in","r",stdin);
	freopen("yyl.out","w",stdout);
	read(n);
	for(int i=1; i<n; ++i) {
		int u,v;
		read(u),read(v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	dfs2(1,1,1);
	read(q);
	for(int i=1; i<=q; ++i) {
		int op;
		read(op);
		if(op==1) {
			int x,w;
			read(x),read(w);
			fenwick::add(dfn[x],low[x],w);
		} else {
			int u,v,w;
			read(u),read(v),read(w);
			while(top[u]!=top[v]) {
				if(dep[top[u]]>dep[top[v]]) swap(u,v);
				fenwick::add(dfn[top[v]],dfn[v],w);
				v=anc[0][top[v]];
			}
			if(dep[u]>dep[v]) swap(u,v);
			fenwick::add(dfn[u],dfn[v],w);
		}
		write(solve());
		pc('\n');
	}
	fwrite(pbuf,1,p1-pbuf,stdout);
	return 0;
}