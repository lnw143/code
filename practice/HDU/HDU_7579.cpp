#include <cstdio>
#include <algorithm>
using namespace std;
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
const int N = 5e5, S = N * 2, V = 30;
int n,m,a[N + 2];
struct LinearBasis {
	int d[V + 2],p[V + 2];
	void insert(int x,int pos) {
		for(int i=V; i>=0; --i)
			if((x>>i)&1) {
				if(!d[i]) return d[i]=x,p[i]=pos,void();
				if(pos>p[i]) {
					swap(pos,p[i]);
					swap(x,d[i]);
				}
				x^=d[i];
			}
	}
} s[S + 2];
int query(int l,int r) {
	int res=0;
	for(int i=V; i>=0; --i)
		if(!((res>>i)&1)&&s[r].p[i]>=l)
			res^=s[r].d[i];
	return res;
}
void solve() {
	read(n,m);
	for(int i=1; i<=n; ++i) read(a[i]);
	for(int i=1; i<=n; ++i) {
		s[i]=s[i-1];
		s[i].insert(a[i],i);
	}
	for(int i=1,last_ans=0; i<=m; ++i) {
		int op;
		read(op);
		if(op==0) {
			int l,r;
			read(l,r);
			l=(l^last_ans)%n+1;
			r=(r^last_ans)%n+1;
			if(l>r) swap(l,r);
			write(last_ans=query(l,r),'\n');
		} else {
			int x;
			read(x);
			x^=last_ans;
			++n;
			s[n]=s[n-1];
			s[n].insert(x,n);
		}
	}
}
int main() {
	int T;
	read(T);
	for(; T; --T) solve();
	return 0;
}