#include <cstdio>
#include <algorithm>
#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <unordered_set>
#include <cctype>
using namespace std;
using ll = long long;
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
const int N = 1e6;
int n,m,fa[N + 2],f[N + 2],g[N + 2];
ll ans;
pair<ll,int> a[N + 2];
unordered_set<int> e[N + 2];
heap<tuple<ll,int,int>> hp;
vector<pair<int,int>> cho;
inline int find(const int u) {
	return fa[u]==u?u:fa[u]=find(fa[u]);
}
inline void upd1(const int u,const int fir=0) {
	bool t=false;
	while(1<=f[u]&&f[u]<=n&&find(u)==find(f[u])) f[u]+=g[u],t=true;
	if((t||fir)&&1<=f[u]&&f[u]<=n) hp.emplace(a[f[u]].first*a[u].first,f[u],u);
}
inline void upd2(const int u,const int fir=0) {
	bool t=false;
	while(1<=f[u]&&f[u]<=n&&e[u].count(f[u])) f[u]+=g[u],t=true;
	if((t||fir)&&1<=f[u]&&f[u]<=n) hp.emplace(a[f[u]].first*a[u].first,f[u],u);
}
namespace FAST_IO {
	const int BUF(1<<25);
	char buf[BUF],*p1=buf,*p2=buf;
	char pbuf[BUF],*p=pbuf;
	inline char gc() {
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,BUF,stdin),p1==p2)?EOF:*p1++;
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
	template<typename T,typename ...Args> inline void read(T &x,Args &...args) {
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
	template<typename T,typename ...Args> inline void write(T x,Args ...args) {
		write(x);
		write(args...);
	}
	struct TMP { ~TMP() { flush(); } } tmp;
};
using FAST_IO::read;
using FAST_IO::write;
using FAST_IO::flush;
int main() {
	read(n,m);
	if(n==1) return write(0),0;
	m-=n-1;
	for(int i=1; i<=n; ++i) fa[i]=i,read(a[i].first),a[i].second=i;
	stable_sort(a+1,a+n+1);
	for(int i=1; i<=n; ++i) {
		if(a[i].first>=0) f[i]=1,g[i]=1;
		else f[i]=n,g[i]=-1;
		e[i].insert(i);
		upd1(i,1);
	}
	for(int i=1; i<n; ++i) {
		auto [w,u,v]=hp.top();
		hp.pop();
		if(find(u)!=find(v)) {
			ans+=w;
			e[u].insert(v);
			e[v].insert(u);
			upd1(v);
			upd1(u);
			fa[find(u)]=find(v);
			cho.emplace_back(a[u].second,a[v].second);
		} else
			--i;
	}
	for(int i=1; i<=n; ++i) {
		f[i]=a[i].first>=0?1:n;
		upd2(i,1);
	}
	for(int i=1; i<=m; ++i) {
		auto [w,u,v]=hp.top();
		hp.pop();
		if(!e[u].count(v)) {
			ans+=w;
			e[u].insert(v);
			e[v].insert(u);
			upd2(v);
			upd2(u);
			cho.emplace_back(a[u].second,a[v].second);
		} else
			--i;
	}
	write(ans,'\n');
	for(auto [u,v] : cho)
		write(u,' ',v,'\n');
	return 0;
}