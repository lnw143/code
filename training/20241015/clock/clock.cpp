#include <cstdio>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>
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
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
const int N = 2e6;
int n,m,k,a[N + 2],b[N + 2],c[N + 10];
int main() {
	freopen("clock.in","r",stdin);
	freopen("clock.out","w",stdout);
	read(n,k);
	for(int i=1; i<=n; ++i) read(a[i]);
	for(int i=1; i<=n; ++i) read(b[i]);
	for(int i=1; i<=n; ++i) c[i]=(a[i]+k-b[i])%k;
	for(int i=n+1; i>=1; --i) c[i]=(c[i]+k-c[i-1])%k;
	heap<int> hp;
	ll x=0,ans=0;
	for(int i=1; i<=n+1; ++i) {
		if(c[i]<=x) x-=c[i],hp.push(k-c[i]);
		else if(hp.size()&&hp.top()<k-c[i]) {
			ans+=hp.top();
			x+=k-c[i];
			hp.pop();
			hp.push(k-c[i]);
		} else {
			ans+=k-c[i];
			x+=k-c[i];
		}
	}
	write(ans);
	return 0;
}