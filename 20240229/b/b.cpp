#include<cstdio>
#include<cctype>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
namespace FAST_IO {
	const int BUF(1<<20);
	char buf[BUF],*p1=buf,*p2=buf;
	char pbuf[BUF],*p=pbuf;
	char gc() {
		return p1==p2?(p2=(p1=buf)+fread(buf,1,BUF,stdin),p1==p2?EOF:*p1++):*p1++;
	}
	void pc(char c) {
		*p++=c;
		if(p-pbuf==BUF) fwrite(pbuf,1,BUF,stdout),p=pbuf;
	}
	void flush() {
		fwrite(pbuf,1,p-pbuf,stdout);
		p=pbuf;
	}
	template<typename T> void read(T &x) {
		x=0;
		static char c;
		T f=1;
		do {
			c=gc();
			if(c=='-') f=-f;
		} while(!isdigit(c));
		do {
			x=(x<<3)+(x<<1)+(c^48);
			c=gc();
		} while(isdigit(c));
		x*=f;
	}
	template<typename T,typename ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	template<typename T> void write(T x) {
		if(x<0) {
			pc('-');
			x=-x;
		}
		static char stk[1<<8],*tp;
		tp=stk;
		do *tp++=(x%10)^48; while(x/=10);
		while(tp!=stk) pc(*--tp);
	}
	void write(char c) { pc(c); }
	template<typename T,typename ...Args> void write(T x,Args ...args) {
		write(x);
		write(args...);
	}
};
using FAST_IO::read;
using FAST_IO::write;
using FAST_IO::flush;
using ll = long long;
const int N(1e6), M(1e5);
namespace segtree {
	const int S((N << 2) + 2);
	int tr[S];
#define mid ((l+r)>>1)
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void maketree(int x,int l,int r) {
		if(l==r) {
			tr[x]=1;
			return ;
		}
		maketree(li);
		maketree(ri);
		tr[x]=tr[ls]+tr[rs];
	}
	int find(int x,int l,int r,int k) {
		if(l==r) return l;
		if(k<=tr[ls]) return find(li,k);
		return find(ri,k-tr[ls]);
	}
	void modify(int x,int l,int r,int u) {
		if(r<u||u<l) return ;
		if(l==r) {
			tr[x]=0;
			return ;
		}
		if(u<=mid) modify(li,u);
		else modify(ri,u);
		tr[x]=tr[ls]+tr[rs];
	}
}
ll n;
int m;
int main() {
	using namespace segtree;
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	read(m,n);
	maketree(1,1,n);
	rep(i,1,m) {
		ll l,r;
		read(l,r);
		write(find(1,1,n,l),' ',find(1,1,n,r),'\n');
		for(ll j=r; j>=l; j-=2)
			modify(1,1,n,find(1,1,n,j));
	}
	flush();
	return 0;
}