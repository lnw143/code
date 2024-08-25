#include <cstdio>
#include <algorithm>
#include <set>
#include <random>
#include <chrono>
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
	template<typename T,typename ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	template<typename T> inline void write(T x) {
		if(x<0) {
			pc('-');
			x=-x;
		}
		static char stk[1<<8],*tp;
		tp=stk;
		do *tp++=(x%10)^48; while(x/=10);
		while(tp!=stk) pc(*--tp);
	}
	inline void write(char c) { pc(c); }
	template<typename T,typename ...Args> void write(T x,Args ...args) {
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
const int N = 1e5;
int n;
ll a[N + 2],b[N + 2],v[N + 2];
namespace segtree {
	const int S = N << 2;
	ll s[S],t[S];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		s[u]=-1e18,t[u]=0;
		if(l==r) return ;
		build(li);
		build(ri);
	}
	void modify(int u,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return t[u]+=2,s[u]+=2,void();
		if(x<=mid) modify(li,x,y);
		if(mid<y) modify(ri,x,y);
		s[u]=max(s[ls],s[rs]);
	}
	ll query(int u,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return s[u];
		if(y<=mid) return query(li,x,y)+t[u];
		if(mid<x) return query(ri,x,y)+t[u];
		return max(query(li,x,y),query(ri,x,y))+t[u];
	}
	void add(int u,int l,int r,int x,ll v) {
		if(l==r) {
			s[u]=v+2+t[u];
			return ;
		}
		if(x<=mid) add(li,x,v);
		else add(ri,x,v);
		s[u]=max(s[ls],s[rs])+t[u];
	}
}
int main() {
	freopen("jyrg.in","r",stdin);
	freopen("jyrg.out","w",stdout);
	int T;
	read(T);
	while(T--) {
		read(n);
		for(int i=1; i<=n; ++i) read(a[i]),v[i]=b[i]=a[i]-i;
		sort(v+1,v+n+1);
		if(unique(v+1,v+n+1)!=v+n+1) {
			write(-1,'\n');
			continue;
		}
		ll ans=0;
		segtree::build(1,1,n);
		for(int i=1; i<=n; ++i) {
			int id=lower_bound(v+1,v+n+1,b[i])-v;
			if(id>1) {
				ans=max(ans,segtree::query(1,1,n,1,id-1)+b[i]+1);
				segtree::modify(1,1,n,1,id-1);
			}
			segtree::add(1,1,n,id,b[i]);
		}
		write(ans,'\n');
	}
	return 0;
}