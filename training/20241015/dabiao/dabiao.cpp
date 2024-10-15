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
using ll = long long;
const int N = 3e6;
int n,m;
int x[N + 2],y[N + 2];
ll ans;
namespace linear_sieve {
	bool bz[N + 2];
	int prm[N + 2],cnt;
	void init(int n) {
		for(int i=2; i<=n; ++i) {
			if(!bz[i]) {
				prm[++cnt]=i;
				ans+=i;
				++m;
				x[m]=1,y[m]=i;
			}
			for(int j=1; j<=cnt&&i*prm[j]<=n; ++j) {
				ans+=prm[j];
				++m;
				x[m]=i,y[m]=i*prm[j];
				bz[i*prm[j]]=true;
				if(i%prm[j]==0) break;
			}
		}
	}
}
int main() {
	freopen("dabiao.in","r",stdin);
	freopen("dabiao.out","w",stdout);
	read(n);
	linear_sieve::init(n);
	write(ans,'\n');
	for(int i=1; i<=m; ++i)
		write(x[i],' ',y[i],'\n');
	return 0;
}