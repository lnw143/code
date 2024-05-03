#include<cstdio>
#include<vector>

#define rep(i,l,r) for(int i(l),i##End(r); i<=i##End; ++i)
#define rep_(i,l,r) for(int i(l),i##End(r); i<i##End; ++i)
#define per(i,l,r) for(int i(r),i##End(l); i>=i##End; --i)
#define per_(i,l,r) for(int i(r),i##End(l); i>i##End; --i)

using namespace std;

using ll = long long;

ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}

template<int P> struct ModInt {
  public:
	using mint = ModInt<P>;
	using mintp = mint&;

	operator int() const { return r?0:x; }

	mint operator+(int t) const { return x+t>=P?x+t-P:x+t; }
	mint operator-(int t) const { return x<t?x-t+P:x-t; }
	mintp operator+=(int t) { return ((x+=t)>=P)&&(x-=P),(*this); }
	mintp operator-=(int t) { return ((x-=t)<0)&&(x+=P),(*this); }

	mint operator++(int) { return (++x>=P)?x=0,P-1:x-1;}
	mint operator--(int) { return (--x<0)?x=P-1,0:x+1;}
	mintp operator++() { return (++x>=P)?x=0,(*this):(*this);}
	mintp operator--() { return (--x<0)?x=P-1,(*this):(*this);}

	mint operator*(int t) const {
		mint p=*this;
		if(t==0) ++p.r;
		else p.x=(ll)p.x*t%P;
		return p;
	}
	mintp operator*=(int t) {
		if(t==0) ++r;
		else x=(ll)x*t%P;
		return *this;
	}
	mint operator/(int t) {
		mint p=*this;
		if(t==0) --p.r;
		else p.x=(ll)p.x*qpow(t,P-2,P)%P;
		return p;
	}
	mintp operator/=(int t) {
		if(t==0) --r;
		else x=(ll)x*qpow(t,P-2,P)%P;
		return *this;
	}

	ModInt():x(0) {}
	template<typename Tp> ModInt(Tp y):r(0) {
		if(y<0) x=y%P+P;
		else if(y<P) x=y;
		else x=y%P;
	}
  private:
	int x,r;
};

constexpr int
	N = 2e5,
	M = N << 2,
	K = 0,
	Q = 0,
	S = 0,
	P = 998244353// 1e9 + 7
;

using mint = ModInt<P>::mint;

// #define MULTITEST
// #define FILE_IO_NAME ""

int n,q,p[N + 2],a[N + 2];
vector<int> e[N + 2];
int dfc,dfn[N + 2],sz[N + 2],wson[N + 2],top[N + 2],low[N + 2],rnk[N + 2];
mint f[N + 2],g[N + 2];

void dfs(int u) {
	sz[u]=1;
	if(e[u].size()==0) f[u]=a[u];
	else {
		f[u]=1;
		for(auto v : e[u]) {
			dfs(v);
			sz[u]+=sz[v];
			f[u]*=f[v];
			if(sz[v]>sz[wson[u]]) wson[u]=v;
		}
		f[u]+=a[u];
	}
}

void dfs2(int u,int tp) {
	dfn[u]=++dfc;
	rnk[dfc]=u;
	top[u]=tp;
	if(wson[u]) dfs2(wson[u],tp);
	else {
		low[u]=low[tp]=dfn[u];
		return ;
	}
	low[u]=low[tp];
	g[u]=1;
	for(auto v : e[u])
		if(v!=wson[u]) {
			dfs2(v,v);
			g[u]*=f[v];
		}
}

struct matrix {
	int n,m;
	mint a[5][5];
	mint* operator[](int x) { return a[x]; }
	const mint* operator[](int x) const { return a[x]; }
};
matrix operator*(const matrix& a,const matrix& b) {
	matrix c;
	c.n=a.n;
	c.m=b.m;
	for(int i=1; i<=c.n; ++i)
		for(int j=1; j<=c.m; ++j) {
			c[i][j]=0;
			for(int k=1; k<=a.m; ++k)
				c[i][j]+=a[i][k]*b[k][j];
		}
	return c;
}
matrix mat2x2(ll a,ll b,ll c,ll d) {
	matrix x;
	x.n=x.m=2;
	x[1][1]=a;
	x[1][2]=b;
	x[2][1]=c;
	x[2][2]=d;
	return x;
}
const matrix E = mat2x2(1,0,0,1);
namespace segtree {
	matrix tr[M];
#define mid ((l+r)>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		if(l==r) {
			tr[u]=mat2x2(g[rnk[l]],0,a[rnk[l]],1);
			return ;
		}
		build(li);
		build(ri);
		tr[u]=tr[rs]*tr[ls];
	}
	matrix query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return E;
		if(x<=l&&r<=y) return tr[u];
		return query(ri,x,y)*query(li,x,y);
	}
	template<typename F> void modify(int u,int l,int r,int x,F f) {
		if(r<dfn[x]||dfn[x]<l) return ;
		if(l==r) {
			f(tr[u]);
			return ;
		}
		if(dfn[x]<=mid) modify(li,x,f);
		else modify(ri,x,f);
		tr[u]=tr[rs]*tr[ls];
	}
}

mint get_ans(int x) {
	matrix s;
	s.n=1;
	s.m=2;
	s[1][1]=a[rnk[low[x]]];
	s[1][2]=1;
	return (s*segtree::query(1,1,n,dfn[top[x]],low[x]-1))[1][1];
}

mint update(int x) {
	x=top[x];
	using namespace segtree;
	mint cur=get_ans(x);
	if(x==1) return cur;
	modify(1,1,n,p[x],[=](matrix &t) {
		t[1][1]/=f[x];
		t[1][1]*=cur;
	});
	f[x]=cur;
	return update(p[x]);
}

void _main() {
	scanf("%d%d",&n,&q);
	rep(i,2,n) scanf("%d",&p[i]),e[p[i]].emplace_back(i);
	rep(i,1,n) scanf("%d",&a[i]);
	dfs(1);
	dfs2(1,1);
	using namespace segtree;
	build(1,1,n);
	rep(i,1,q) {
		int x,y;
		scanf("%d%d",&x,&y);
		modify(1,1,n,x,[=](matrix &t){
			t[2][1]=y;
		});
		a[x]=y;
		printf("%d\n",update(x));
	}
}

int main() {
#if defined(FILE_IO_NAME) && !defined(ONLINE_JUDGE)
	freopen(FILE_IO_NAME".in","r",stdin);
	freopen(FILE_IO_NAME".out","w",stdout);
#endif
	int T=1;
#if defined(MULTITEST)
	scanf("%d",&T);
#endif
	while(T--) _main();
	return 0;
}