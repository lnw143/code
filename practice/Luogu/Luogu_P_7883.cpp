#include <cstdio>
#include <ext/random>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <utility>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <map>
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
using llu = long long unsigned;
const int N = 4e5;
const ll inf = 1ll << 60;
int n;
struct point {
	ll x,y;
} p[N + 2];
inline ll sqr(ll x) {
	return x*x;
}
inline ll operator-(const point& a,const point &b) {
	return sqr(a.x-b.x)+sqr(a.y-b.y);
}
ll ans=inf;
double dis=sqrt(ans);
__gnu_cxx::sfmt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
__gnu_pbds::gp_hash_table<llu,vector<int>> mp;
llu get_pos(int u) {
	return llu(p[u].x/dis)<<30|(llu(p[u].y/dis));
}
int main() {
	read(n);
	for(int i=1; i<=n; ++i) {
		read(p[i].x,p[i].y);
		p[i].x+=10000000;
		p[i].y+=10000000;
	}
	shuffle(p+1,p+n+1,rnd);
	for(int i=1; i<=n; ++i) {
		llu pos=get_pos(i);
		ll res=inf;
		for(int x=-1; x<=1; ++x)
			for(int y=-1; y<=1; ++y) {
				llu q=pos+(ll(x)<<30)+y;
				if(mp.find(q)!=mp.end())
					for(const auto& u : mp[q])
						res=min(res,p[i]-p[u]);
			}
		if(res<ans) {
			ans=res;
			dis=sqrt(ans);
			mp.clear();
			for(int j=1; j<=i; ++j) mp[get_pos(j)].push_back(j);
		} else
			mp[pos].push_back(i);
	}
	write(ans);
	return 0;
}