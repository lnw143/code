#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const int BUF = 1 << 20;
char pbuf[BUF],*p=pbuf;
inline char gc() {
	static char buf[BUF],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,BUF,stdin),l==r)?-1:*l++;
}
inline void pc(char c) {
	if(p-pbuf==BUF) fwrite(pbuf,1,BUF,stdout),p=pbuf;
	*p++=c;
}
inline int read() {
	int x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c^48);
	return x;
}
inline void write(ll x) {
	static int stk[1 << 7];
	int tp=0;
	do stk[++tp]=(x%10)^48; while(x/=10);
	while(tp) pc(stk[tp--]);
}
struct TMP { ~TMP() { fwrite(pbuf,1,p-pbuf,stdout); } } tmp;
const int N = 3e5, S = N * 2, M = S * 2, logS = 20;
int n,m,q,anc[logS][S + 2],dep[S + 2];
int ls[S + 2],nx[M + 2],em,e[M + 2];
ll d[S + 2],a[S + 2],b[S + 2];
void insert(int u,int v) {
	e[++em]=v;
	nx[em]=ls[u];
	ls[u]=em;
}
void dfs(int u,int p) {
	anc[0][u]=p;
	dep[u]=dep[p]+1;
	for(int i=1; i<logS; ++i)
		anc[i][u]=anc[i-1][anc[i-1][u]];
	for(int i=ls[u]; i; i=nx[i])
		if(e[i]!=p)
			dfs(e[i],u);
}
int lca(int u,int v) {
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=logS-1; ~i; --i)
		if(dep[anc[i][v]]>=dep[u])
			v=anc[i][v];
	if(u==v) return u;
	for(int i=logS-1; ~i; --i)
		if(anc[i][u]!=anc[i][v])
			u=anc[i][u],v=anc[i][v];
	return anc[0][u];
}
void dfs2(int u,int p) {
	for(int i=ls[u]; i; i=nx[i])
		if(e[i]!=p) {
			dfs2(e[i],u);
			d[u]+=d[e[i]];
		}
	a[u]=u>n?-d[u]:d[u];
}
void dfs3(int u,int p) {
	b[u]+=a[u];
	for(int i=ls[u]; i; i=nx[i])
		if(e[i]!=p) {
			b[e[i]]+=b[u];
			dfs3(e[i],u);
		}
}
int main() {
	freopen("soong.in","r",stdin);
	freopen("soong.out","w",stdout);
	n=read(),m=read(),q=read();
	for(int i=1; i<n; ++i) {
		int u=read(),v=read();
		insert(u,i+n);
		insert(i+n,u);
		insert(i+n,v);
		insert(v,i+n);
	}
	dfs(1,1);
	for(int i=1; i<=m; ++i) {
		int x,y,w;
		x=read(),y=read();
		w=read();
		int l=lca(x,y);
		d[x]+=w;
		d[y]+=w;
		d[l]-=w;
		if(l!=1) d[anc[0][l]]-=w;
	}
	dfs2(1,1);
	dfs3(1,1);
	for(int i=1; i<=q; ++i) {
		int u=read(),v=read();
		int l=lca(u,v);
		ll ans=b[u]+b[v]-b[l];
		if(l!=1) ans-=b[anc[0][l]];
		write(ans);
		pc('\n');
	}
	return 0;
}