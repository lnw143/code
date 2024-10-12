#include <cstdio>
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
const int N = 5e4, logN = 16, S = 1 << logN, inf = 1 << 30;
int n,m,a[S + 2],s[S + 2];
namespace msegtree {
	int dep[(S << 2) + 2],maxn[logN + 2][S + 2],minn[logN + 2][S + 2],t[logN + 2][S + 2];
	int pos[S + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r,int _dep) {
		dep[u]=_dep;
		if(l==r) {
			pos[l]=u;
			maxn[dep[u]][l]=minn[dep[u]][l]=s[l];
			return ;
		}
		build(li,_dep+1);
		build(ri,_dep+1);
		minn[_dep][mid]=maxn[_dep][mid]=s[mid];
		t[_dep][mid]=-inf;
		for(int i=mid-1; i>=l; --i) {
			maxn[_dep][i]=max(maxn[_dep][i+1],s[i]);
			minn[_dep][i]=min(minn[_dep][i+1],s[i]);
			t[_dep][i]=max(t[_dep][i+1],maxn[_dep][i+1]-s[i]);
		}
		minn[_dep][mid+1]=maxn[_dep][mid+1]=s[mid+1];
		t[_dep][mid+1]=-inf;
		for(int i=mid+2; i<=r; ++i) {
			maxn[_dep][i]=max(maxn[_dep][i-1],s[i]);
			minn[_dep][i]=min(minn[_dep][i-1],s[i]);
			t[_dep][i]=max(t[_dep][i-1],s[i]-minn[_dep][i-1]);
		}
	}
	int query(int l,int r) {
		int d=dep[pos[l]>>__lg(pos[l]^pos[r])+1];
		return max({t[d][l],t[d][r],maxn[d][r]-minn[d][l]});
	}
}
int main() {
	read(n);
	for(int i=1; i<=n; ++i) read(a[i]),s[i]=s[i-1]+a[i];
	msegtree::build(1,0,(1<<__lg(n)+1)-1,1);
	read(m);
	for(int i=1; i<=m; ++i) {
		int l,r;
		read(l,r);
		write(msegtree::query(l-1,r),'\n');
	}
	return 0;
}