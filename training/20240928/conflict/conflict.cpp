#include <cstdio>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 2e5, logN = 20;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const ull P1 = 998244353, P2 = chrono::system_clock::now().time_since_epoch().count() / P1, P3 = (rnd()>>2) + 1e8;
const ull B1 = 12, B2 = rnd()%P2, B3 = rnd()%P3;
ull pow1[N + 2],pow2[N + 2],pow3[N + 2];
namespace psegtree {
	const int S = N << 6;
	int tot,ls[S],rs[S];
	struct Hash {
		ull val1,val2,val3;
		int len;
	} s[S];
	Hash operator+(const Hash& x,const Hash& y) {
		return {
			x.val1*pow1[y.len]+y.val1,
			x.val2*pow2[y.len]+y.val2,
			x.val3*pow3[y.len]+y.val3,
			x.len+y.len,
		};
	}
	bool operator==(const Hash& x,const Hash& y) {
		return x.val1==y.val1&&x.val2==y.val2&&x.val3==y.val3&&x.len==y.len;
	}
#define mid (l+r>>1)
	int build(int l,int r) {
		int u=++tot;
		if(l==r) {
			s[u]={B1,B2,B3,1};
			return u;
		}
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		s[u]=s[ls[u]]+s[rs[u]];
		return u;
	}
	int modf(int v,int l,int r,int x,int k) {
		int u=++tot;
		ls[u]=ls[v],rs[u]=rs[v];
		if(l==r) {
			s[u]={(k+B1)%P1,(k+B2)%P2,(k+B3)%P3,1};
			return u;
		}
		if(x<=mid) ls[u]=modf(ls[u],l,mid,x,k);
		else rs[u]=modf(rs[u],mid+1,r,x,k);
		s[u]=s[ls[u]]+s[rs[u]];
		return u;
	}
	int query(int u,int v,int w,int l,int r) {
		if(s[u]==s[v]||s[u]==s[w]||s[v]==s[w]) return 0;
		if(l==r) return 1;
		return query(ls[u],ls[v],ls[w],l,mid)+query(rs[u],rs[v],rs[w],mid+1,r);
	}
}
int n,m,q,anc[logN][N + 2],dep[N + 2];
int rt[N + 2];
int lca(int u,int v) {
	if(dep[u]>dep[v]) swap(u,v);
	for(int j=logN-1; ~j; --j)
		if(dep[anc[j][v]]>=dep[u])
			v=anc[j][v];
	if(u==v) return u;
	for(int j=logN-1; ~j; --j)
		if(anc[j][u]!=anc[j][v])
			u=anc[j][u],v=anc[j][v];
	return anc[0][u];
}
int main() {
	freopen("conflict.in","r",stdin);
	freopen("conflict.out","w",stdout);
	scanf("%*d%d%d%d",&n,&m,&q);
	pow1[0]=pow2[0]=pow3[0]=1;
	for(int i=1; i<=n; ++i)
		pow1[i]=pow1[i-1]*P1,
		pow2[i]=pow2[i-1]*P2,
		pow3[i]=pow3[i-1]*P3;
	rt[0]=psegtree::build(1,m);
	for(int i=1; i<=n; ++i) {
		int x,y;
		scanf("%d%d%d",&anc[0][i],&x,&y);
		rt[i]=psegtree::modf(rt[anc[0][i]],1,m,x,y);
		dep[i]=dep[anc[0][i]]+1;
		for(int j=1; j<logN; ++j)
			anc[j][i]=anc[j-1][anc[j-1][i]];
	}
	for(int i=1; i<=q; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",psegtree::query(rt[u],rt[v],rt[lca(u,v)],1,m));
	}
	return 0;
}