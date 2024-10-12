#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
namespace IO {
	static const int BUF = 1<<20;
	static char pbuf[BUF],*p=pbuf;
	inline char gc() {
		static char buf[BUF],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,BUF,stdin),p1==p2)?-1:*p1++;
	}
	inline void pc(char c) {
		*p++=c;
		if(p-pbuf==BUF) fwrite(pbuf,1,BUF,stdout),p=pbuf;
	}
	inline void flush() {
		fwrite(pbuf,1,p-pbuf,stdout);
		p=pbuf;
	}
	template<typename T> inline void read(T &x) {
		x=0;
		char c=gc();
		T f=1;
		for(; c<'0'||c>'9'; c=gc()) if(c=='-') f=-1;
		for(; c>='0'&&c<='9'; c=gc()) x=(x<<3)+(x<<1)+(c^48);
		x*=f;
	}
	inline void read(char *p) {
		char c=gc();
		for(; !isgraph(c); c=gc());
		for(; isgraph(c); c=gc()) *p++=c;
		*p='\0';
	}
	inline void read(std::string& s) {
		s.clear();
		char c=gc();
		for(; !isgraph(c); c=gc());
		for(; isgraph(c); c=gc()) s+=c;
	}
	template<typename T,typename ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	template<typename T> inline void write(const T &y) {
		T x=y;
		if(x<0) {
			pc('-');
			x=-x;
		}
		static char stk[1<<8],*tp;
		tp=stk;
		do *tp++=(x%10)^48; while(x/=10);
		while(tp!=stk) pc(*--tp);
	}
	inline void write(const char &c) { pc(c); }
	inline void write(const std::string &s) {
		for(auto i : s) pc(i);
	}
	inline void write(const char *p) {
		for(; *p; ++p) pc(*p);
	}
	inline void write(char *p) {
		write(static_cast<const char*>(p));
	}
	template<typename T,typename ...Args> void write(const T &x,const Args &...args) {
		write(x);
		write(args...);
	}
	struct TMP { ~TMP() { flush(); } } tmp;
};
using IO::read;
using IO::write;
using IO::flush;
using namespace std;
using ll = long long;
const int N = 2e5, Q = 2e5, V = 3e7, P = 1e9 + 7, inv2 = (P+1) / 2;
int tid,n,m,k,q;
int powsum;
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
vector<int> e[N + 2];
namespace segtree {
	const int S = N << 2;
	int s[S + 2],t[S + 2],sum[S + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		s[u]=1,t[u]=sum[u]=0;
		if(l==r) return ;
		build(li);
		build(ri);
	}
	void modf(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			s[u]=(ll)s[u]*inv2%P;
			t[u]=(s[u]+t[u])%P;
			sum[u]=inv2*ll(sum[u]+r-l+1)%P;
			return ;
		}
		if(x<=mid) modf(li,x,y);
		if(mid<y) modf(ri,x,y);
		sum[u]=(s[u]*ll(sum[ls]+sum[rs])+t[u]*ll(r-l+1))%P;
	}
	ll qry(int u,int l,int r,int x,int y) {
		if(y<l||r<x) return 0;
		if(x<=l&&r<=y) return sum[u];
		ll len=min(r,y)-max(l,x)+1;
		if(y<=mid) return (s[u]*qry(li,x,y)+t[u]*len)%P;
		if(mid<x) return (s[u]*qry(ri,x,y)+t[u]*len)%P;
		return (s[u]*(qry(li,x,y)+qry(ri,x,y))+t[u]*len)%P;
	}
}
namespace treecut {
	int dep[N + 2],fa[N + 2],sz[N + 2],wson[N + 2];
	int dfn[N + 2],low[N + 2],dfc,top[N + 2];
	void dfs(int u) {
		sz[u]=1;
		dep[u]=dep[fa[u]]+1;
		for(auto v : e[u])
			if(v!=fa[u]) {
				fa[v]=u;
				dfs(v);
				sz[u]+=sz[v];
				if(sz[v]>sz[wson[u]]) wson[u]=v;
			}
	}
	int dfs2(int u,int _top) {
		top[u]=_top;
		dfn[u]=++dfc;
		if(wson[u]) low[u]=dfs2(wson[u],_top);
		else return low[u]=u;
		for(auto v : e[u])
			if(v!=fa[u]&&v!=wson[u])
				dfs2(v,v);
		return low[u];
	}
	void init() {
		dfs(1);
		dfs2(1,1);
	}
}
void modify(int x,int y) {
	using namespace treecut;
	using namespace segtree;
	while(top[x]!=top[y]) {
		if(dep[top[x]]>dep[top[y]]) swap(x,y);
		modf(1,1,dfc,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	modf(1,1,dfc,dfn[x],dfn[y]);
}
ll query(int x,int y) {
	using namespace treecut;
	using namespace segtree;
	ll res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]>dep[top[y]]) swap(x,y);
		res+=qry(1,1,dfc,dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	res+=qry(1,1,dfc,dfn[x],dfn[y]);
	return res%P;
}
namespace linear_sieve {
	int pow[V + 2],prime[V + 2],cnt;
	bool bz[V + 2];
	int get_sum(int n,int k) {
		int res=1;
		for(int i=2; i<=n; ++i) {
			if(!bz[i]) pow[i]=qpow(i,k),prime[++cnt]=i;
			for(int j=1; j<=cnt&&i*prime[j]<=n; ++j) {
				bz[i*prime[j]]=true;
				pow[i*prime[j]]=pow[i]*(ll)pow[prime[j]]%P;
				if(i%prime[j]==0) break;
			}
			res=(res+pow[i])%P;
		}
		return res;
	}
}
int main() {
	freopen("sigma.in","r",stdin);
	freopen("sigma.out","w",stdout);
	read(tid,n,m,k,q);
	powsum=linear_sieve::get_sum(m,k)*qpow(m+1,P-2)%P;
	for(int i=1; i<n; ++i) {
		int x,y;
		read(x,y);
		e[x].emplace_back(y);
		e[y].emplace_back(x);
	}
	treecut::init();
	segtree::build(1,1,treecut::dfc);
	for(int i=1; i<=q; ++i) {
		int op,x,y;
		read(op,x,y);
		if(op==1)
			modify(x,y);
		else
			write(query(x,y)*powsum%P,'\n');
	}
	return 0;
}