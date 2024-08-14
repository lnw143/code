#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
namespace IO {
	static const int BUF = 1<<20;
	static char pbuf[BUF],*p=pbuf,*ch;
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
		char c=*ch++;
		T f=1;
		for(; c<'0'||c>'9'; c=*ch++) if(c=='-') f=-1;
		for(; c>='0'&&c<='9'; c=*ch++) x=(x<<3)+(x<<1)+(c^48);
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
	inline void init(const char* filein, const char* fileout) {
		if(*filein) freopen(filein,"r",stdin);
		if(*fileout) freopen(fileout,"w",stdout);
    	ch=(char*)mmap(NULL,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);
	}
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
const int N = 2e5, P = 998244353, inv2 = (P + 1) / 2;
int n,x[N + 2],y[N + 2],mx,my;
ll ans;
pair<int,int> a[N + 2];
struct segtree {
	ll s[N << 2],t[N << 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		t[u]=1;
		if(l==r) {
			s[u]=y[l+1]-y[l];
			return ;
		}
		build(li);
		build(ri);
		s[u]=(s[ls]+s[rs])%P;
	}
	void pushdown(int u,int l,int r) {
		if(l<r) {
			(s[ls]*=t[u])%=P;
			(t[ls]*=t[u])%=P;
			(s[rs]*=t[u])%=P;
			(t[rs]*=t[u])%=P;
		}
		t[u]=1;
	}
	void modify(int u,int l,int r,int x,int y,int f) {
		if(r<x||y<l) return ;
		if(t[u]>1) pushdown(u,l,r);
		if(x<=l&&r<=y) {
			(s[u]*=f)%=P;
			(t[u]*=f)%=P;
			return ;
		}
		modify(li,x,y,f);
		modify(ri,x,y,f);
		s[u]=(s[ls]+s[rs])%P;
	}
#undef mid
#undef ls
#undef rs
#undef li
#undef ri
} up,le,dn,ri,ul,ur,dl,dr;
const vector<segtree*>
UR = {&up, &ri, &ur},
UL = {&up, &le, &ul},
DR = {&dn, &ri, &dr},
DL = {&dn, &le, &dl};
ll get_all() {
	ll res=y[my]-y[1];
	for(auto segt : {&up, &le, &dn, &ri})
		(res+=segt->s[1])%=P;
	for(auto segt : {&ul, &ur, &dl, &dr})
		(res-=segt->s[1])%=P;
	return res;
}
int main() {
	IO::init("complex.in","complex.out");
	read(n);
	for(int i=1; i<=n; ++i) read(x[i],y[i]),a[i]=make_pair(x[i],y[i]);
	sort(a+1,a+n+1);
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	mx=unique(x+1,x+n+1)-x-1;
	my=unique(y+1,y+n+1)-y-1;
	for(auto segt : {&up, &le, &dn, &ri, &ul, &ur, &dl, &dr})
		segt->build(1,1,my-1);
	for(int i=1; i<=n; ++i) {
		auto &[u,v]=a[i];
		u=lower_bound(x+1,x+mx+1,u)-x;
		v=lower_bound(y+1,y+my+1,v)-y;
		for(auto segt : UR) segt->modify(1,1,my-1,1,v-1,2);
		for(auto segt : DR) segt->modify(1,1,my-1,v,my-1,2);
	}
	ans=ll(y[my]-y[1])*(x[mx]-x[1])%P;
	for(int i=1; i<=n; ++i) ans=ans*2%P;
	for(int i=1,cur=1; i<mx; ++i) {
		for(; cur<=n&&a[cur].first==i; ++cur) {
			auto [u,v]=a[cur];
			for(auto segt : UR) if(segt!=&up&&segt!=&dn) segt->modify(1,1,my-1,1,v-1,inv2);
			for(auto segt : DR) if(segt!=&up&&segt!=&dn) segt->modify(1,1,my-1,v,my-1,inv2);
			for(auto segt : UL) if(segt!=&up&&segt!=&dn) segt->modify(1,1,my-1,1,v-1,2);
			for(auto segt : DL) if(segt!=&up&&segt!=&dn) segt->modify(1,1,my-1,v,my-1,2);
		}
		(ans-=(x[i+1]-x[i])*get_all()%P)%=P;
	}
	write((ans%P+P)%P);
	return 0;
}