#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 3e5 + 2, LOG_N = 20, M = 3e5 + 2;
int n,m,i,x[M],y[M],d[M],t[M],tag[N],maxn,k,limit;
namespace Graph {
	int em,e[N << 1],ls[N],nx[N << 1],cs[N << 1];
	int dis[N],dep[N],pos[N],dfn[N << 1],dfc,lg2[N << 1],st[LOG_N][N << 1];
	void insert(int x,int y,int z) {
		e[++em]=y;
		nx[em]=ls[x];
		ls[x]=em;
		cs[em]=z;
	}
	void dfs(int x,int s) {
		dis[x]=s;
		dfn[++dfc]=x;
		pos[x]=dfc;
		for(int i=ls[x],v=e[i]; i; i=nx[i],v=e[i])
			if(!dep[v]) {
				dep[v]=dep[x]+1;
				dfs(v,s+cs[i]);
				dfn[++dfc]=x;
			}
	}
	void get_st() {
		lg2[1]=0;
		for(int i=2; i<=dfc; ++i)
			lg2[i]=lg2[i>>1]+1;
		for(int i=1; i<=dfc; ++i)
			st[0][i]=dfn[i];
#define pw2(x) (1<<(x))
		for(int j=1; j<LOG_N; ++j)
			for(int i=1; i<=dfc; ++i)
				st[j][i]=dep[st[j-1][i]]<dep[st[j-1][i+pw2(j-1)]]?st[j-1][i]:st[j-1][i+pw2(j-1)];
	}
	int lca(int x,int y) {
		x=pos[x],y=pos[y];
		if(x>y) x^=y^=x^=y;
		int k=lg2[y-x+1];
		return dep[st[k][x]]<dep[st[k][y-pw2(k)+1]]?st[k][x]:st[k][y-pw2(k)+1];
	}
#undef pw2
}
void mk(int x,int y,int t) {
	tag[t]-=2;
	++tag[x],++tag[y];
}
bool cnt(int x,int fa) {
	using namespace Graph;
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa) {
			if(cnt(e[i],x)) return true;
			tag[x]+=tag[e[i]];
			if(tag[e[i]]==k&&cs[i]>=limit) return true;
		}
	return false;
}
bool ck(int lim) {
	int maxv=0;
	for(int i=1; i<=n; ++i)
		tag[i]=0;
	k=0;
	for(int i=1; i<=m; ++i)
		if(d[i]>lim) {
			++k;
			maxv=max(maxv,d[i]-lim);
			mk(x[i],y[i],t[i]);
		}
	if(maxv==0) return true;
	limit=maxv;
	return cnt(1,-1);
}
int bin_ans() {
	int l=0,r=maxn,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(ck(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	return r+1;
}
char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
int read() {
	int x=0;
	char ch=gc();
	while(ch<'0'||ch>'9') ch=gc();
	do {
		x=(x<<1)+(x<<3)+(ch^'0');
		ch=gc();
	} while(ch>='0'&&ch<='9');
	return x;
}
int main() {
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	n=read(),m=read();
	for(i=1; i<n; ++i) {
		int u,v,w;
		u=read(),v=read(),w=read();
		Graph::insert(u,v,w);
		Graph::insert(v,u,w);
	}
	Graph::dep[1]=1;
	Graph::dfs(1,0);
	Graph::get_st();
	for(i=1; i<=m; ++i) {
		x[i]=read(),y[i]=read();
		t[i]=Graph::lca(x[i],y[i]);
		d[i]=Graph::dis[x[i]]+Graph::dis[y[i]]-Graph::dis[t[i]]*2;
		maxn=max(maxn,d[i]);
	}
	printf("%d",bin_ans());
	return 0;
}