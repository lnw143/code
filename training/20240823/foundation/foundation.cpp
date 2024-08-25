#include <cstdio>
#include <algorithm>
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
const int N = 1e5;
int n,q;
namespace treap {
	mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
	int tot,rt,val[N + 2],sz[N + 2],ls[N + 2],rs[N + 2];
	unsigned int pri[N + 2];
	int rep[N + 2],rev[N + 2],inv[N + 2]; // tags
	struct node {
		int sum;
		int premax,premin;
		int sufmax,sufmin;
		void invert() {
			sum=-sum;
			premax=-premax;
			premin=-premin;
			sufmax=-sufmax;
			sufmin=-sufmin;
			swap(premax,premin);
			swap(sufmax,sufmin);
		}
		node()=default;
		node(int v):sum(v),premax(max(0,v)),premin(min(0,v)),sufmax(max(0,v)),sufmin(min(0,v)) {}
		node(int a,int b,int c,int d,int e):
		sum(a),
		premax(b),premin(c),
		sufmax(d),sufmin(e) {}
	} s[N + 2];
	node operator+(const node& a,const node& b) {
		return node(a.sum+b.sum,
		max(a.premax,a.sum+b.premax),min(a.premin,a.sum+b.premin),
		max(b.sufmax,b.sum+a.sufmax),min(b.sufmin,b.sum+a.sufmin)
		);
	}
	int newnode(int _val) {
		int u=++tot;
		val[u]=_val;
		sz[u]=1;
		ls[u]=rs[u]=0;
		pri[u]=rnd();
		rep[u]=rev[u]=inv[u]=0;
		return u;
	}
	void set(int u,int _val) {
		val[u]=_val;
		s[u].sum=sz[u]*_val;
		if(_val<0) {
			s[u].premax=s[u].sufmax=0;
			s[u].premin=s[u].sufmin=s[u].sum;
		} else {
			s[u].premin=s[u].sufmin=0;
			s[u].premax=s[u].sufmax=s[u].sum;
		}
	}
	void pushdown(int u) {
		if(rep[u]) {
			if(ls[u]) {
				int v=ls[u];
				set(v,rep[u]);
				val[v]=rep[v]=rep[u];
				if(inv[v]) inv[v]=0;
			}
			if(rs[u]) {
				int v=rs[u];
				set(v,rep[u]);
				val[v]=rep[v]=rep[u];
				if(inv[v]) inv[v]=0;
			}
			rep[u]=0;
		}
		if(rev[u]) {
			if(ls[u]) {
				int v=ls[u];
				swap(ls[v],rs[v]);
				swap(s[v].premax,s[v].sufmax);
				swap(s[v].premin,s[v].sufmin);
				rev[v]^=1;
			}
			if(rs[u]) {
				int v=rs[u];
				swap(ls[v],rs[v]);
				swap(s[v].premax,s[v].sufmax);
				swap(s[v].premin,s[v].sufmin);
				rev[v]^=1;
			}
			rev[u]=0;
		}
		if(inv[u]) {
			if(ls[u]) {
				int v=ls[u];
				s[v].invert();
				val[v]=-val[v];
				inv[v]^=1;
			}
			if(rs[u]) {
				int v=rs[u];
				s[v].invert();
				val[v]=-val[v];
				inv[v]^=1;
			}
			inv[u]=0;
		}
	}
	void pushup(int u) {
		s[u]=s[ls[u]]+node(val[u])+s[rs[u]];
		sz[u]=sz[ls[u]]+sz[rs[u]]+1;
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(pri[u]<pri[v]) return pushdown(u),rs[u]=merge(rs[u],v),pushup(u),u;
		return pushdown(v),ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	void split(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		pushdown(u);
		if(k<=sz[ls[u]]) y=u,split(ls[u],x,ls[u],k);
		else x=u,split(rs[u],rs[u],y,k-sz[ls[u]]-1);
		pushup(u);
	}
	void append(int _val) {
		int u=newnode(_val);
		set(u,_val);
		rt=merge(rt,u);
	}
	void Replace(int l,int r,int c) {
		int x,y,z;
		split(rt,y,z,r);
		split(y,x,y,l-1);
		val[y]=rep[y]=c;
		set(y,c);
		if(inv[y]) inv[y]=0;
		rt=merge(merge(x,y),z);
	}
	void Reverse(int l,int r) {
		int x,y,z;
		split(rt,y,z,r);
		split(y,x,y,l-1);
		rev[y]^=1;
		swap(ls[y],rs[y]);
		swap(s[y].premax,s[y].sufmax);
		swap(s[y].premin,s[y].sufmin);
		rt=merge(merge(x,y),z);
	}
	void Invert(int l,int r) {
		int x,y,z;
		split(rt,y,z,r);
		split(y,x,y,l-1);
		inv[y]^=1;
		val[y]=-val[y];
		s[y].invert();
		rt=merge(merge(x,y),z);
	}
	int Query(int l,int r) {
		int x,y,z;
		split(rt,y,z,r);
		split(y,x,y,l-1);
		int sum=s[y].sum,minn=s[y].premin;
		int res=sum/2+(1-minn)/2*2;
		rt=merge(merge(x,y),z);
		return res;
	}
}
int main() {
	freopen("foundation.in","r",stdin);
	freopen("foundation.out","w",stdout);
	read(n,q);
	for(int i=1; i<=n; ++i) {
		char c;
		for(c=IO::gc(); c!='('&&c!=')'; c=IO::gc());
		treap::append(c=='('?1:-1);
	}
	for(int i=1; i<=q; ++i) {
		char op;
		int l,r;
		for(op=IO::gc(); op<'A'||op>'Z'; op=IO::gc());
		read(l,r);
		switch(op) {
			case 'R': { // Replace
				char c;
				for(c=IO::gc(); c!='('&&c!=')'; c=IO::gc());
				treap::Replace(l,r,c=='('?1:-1);
				break;
			}
			case 'S': { // Reverse
				treap::Reverse(l,r);
				break;
			}
			case 'I': { // Invert
				treap::Invert(l,r);
				break;
			}
			case 'Q': { // Query
				write(treap::Query(l,r),'\n');
				break;
			}
		}
	}
	return 0;
}