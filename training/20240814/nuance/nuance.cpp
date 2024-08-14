#include <cstdio>
#include <algorithm>
using namespace std;
using llu = long long unsigned;
const int N = 1e5, logN = 20, Sig = 1e3, K = 11451419;
inline char gc() {
	static char buf[1<<25],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<25,stdin),l==r)?-1:*l++;
}
template<class T> void read(T &x) {
	x=0;
	char c=gc();
	int f=1;
	for(; c<'0'||c>'9'; c=gc()) if(c=='-') f=-1;
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
int n,sig,m,a[N + 2],nxt[N + 2],pos[Sig + 2],pre[logN][N + 2];
int p[Sig + 2],q[Sig + 2];
llu kpow[N + 2];
namespace segtree {
	const int S = N << 6;
	int tot,ls[S],rs[S],rt[N + 2];
	struct node {
		llu hash;
		int len;
	} s[S];
	node operator+(const node& x,const node& y) {
		return {x.hash*kpow[y.len]+y.hash,x.len+y.len};
	}
	bool operator==(const node& x,const node& y) {
		return x.hash==y.hash;
	}
#define mid (l+r>>1)
	int build(int l,int r) {
		int u=++tot;
		if(l<r) {
			ls[u]=build(l,mid);
			rs[u]=build(mid+1,r);
			s[u]=s[ls[u]]+s[rs[u]];
		} else
			s[u].len=1;
		return u;
	}
	int modify(int u,int l,int r,int x,int c) {
		int v=++tot;
		s[v]=s[u],ls[v]=ls[u],rs[v]=rs[u];
		if(l==r) {
			s[v].hash=c;
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x,c);
		else rs[v]=modify(rs[v],mid+1,r,x,c);
		s[v]=s[ls[v]]+s[rs[v]];
		return v;
	}
	node query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return {0,0};
		if(x<=l&&r<=y) return s[u];
		return query(ls[u],l,mid,x,y)+query(rs[u],mid+1,r,x,y);
	}
#undef mid
}
int main() {
	freopen("nuance.in","r",stdin);
	freopen("nuance.out","w",stdout);
	read(n),read(sig);

	for(int i=1; i<=n; ++i) read(a[i]);

	kpow[0]=1;
	for(int i=1; i<=n; ++i) kpow[i]=kpow[i-1]*K;

	for(int i=n; i>=1; --i) nxt[i]=pos[a[i]],pos[a[i]]=i;
	for(int i=1; i<=sig; ++i) pos[i]=0;

	for(int i=1; i<=n; ++i) pre[0][i]=pos[a[i]],pos[a[i]]=i;
	for(int j=1; j<logN; ++j)
		for(int i=1; i<=n; ++i)
			pre[j][i]=pre[j-1][pre[j-1][i]];

	{
		using namespace segtree;
		rt[n+1]=build(1,n);
		for(int i=n; i>=1; --i) {
			rt[i]=rt[i+1];
			if(nxt[i]) rt[i]=modify(rt[i],1,n,nxt[i],nxt[i]-i);
		}
	}

	read(m);
	for(int i=1; i<=m; ++i) {
		int l1,r1,l2,r2;
		read(l1),read(r1),read(l2),read(r2);
		int ans=0,len=min(r1-l1,r2-l2)+1,comp=0;
		using namespace segtree;
		{
			int l=1,r=len;
			while(l<=r) {
				int mid=(l+r)/2;
				if(query(rt[l1],1,n,l1,l1+mid-1)==query(rt[l2],1,n,l2,l2+mid-1)) l=mid+1;
				else r=mid-1;
			}
			ans=l-1;
		}
		if(ans==len) {
			if(r1-l1!=r2-l2) comp=r1-l1<r2-l2?-1:1;
		} else {
			int x=l1+ans,y=l2+ans;
			for(int j=logN-1; ~j; --j) {
				if(pre[j][x]>=l1) x=pre[j][x];
				if(pre[j][y]>=l2) y=pre[j][y];
			}
			comp=x-l1<y-l2?-1:1;
		}
		printf("%d ",ans);
		printf(comp<0?"a\n":comp>0?"b\n":"same\n");
	}
	return 0;
}