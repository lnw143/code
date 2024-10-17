#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
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
		for(; !isdigit(c); c=gc()) if(c=='-') f=-1;
		for(; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48);
		x*=f;
	}
	inline void read(char &c) { c=gc(); }
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
	struct __Flusher { ~__Flusher() { flush(); } } __flusher;
};
using IO::read;
using IO::write;
using IO::flush;

using namespace std;
const int N = 5e5, M = N, Q = N;
int n,m,q,B,a[N + 2];
vector<int> e[N + 2],g[N + 2];
bool c[N + 2];
namespace solution {
	int stk[N + 2],tp;
	int clock;
	struct Tag {
		int time,color;
		Tag(int t,int c):time(t),color(c) {}
	};
	vector<Tag> s[N + 2],t[N + 2];
	bool operator<(const Tag& a,const Tag& b) {
		return a.time<b.time;
	}
	int get_color(int u) {
		Tag res{0,a[u]};
		if(t[u].size()) res=max(res,t[u].back());
		if(!c[u])
			for(auto v : e[u])
				if(s[v].size())
					res=max(res,s[v].back());
		return res.color;
	}
	void expand(int u) {
		stk[++tp]=u;
		++clock;
		int c=get_color(u);
		s[u].emplace_back(clock,c);
		for(auto v : g[u])
			t[v].emplace_back(clock,c);
	}
	void undo() {
		int u=stk[tp];
		--tp;
		--clock;
		s[u].pop_back();
		for(auto v : g[u])
			t[v].pop_back();
	}
}
namespace history_tree {
	int op[Q + 2],x[Q + 2],ans[Q + 2];
	vector<int> e[Q + 2];
	void init() {
		for(int i=1; i<=q; ++i) {
			int v;
			read(v,op[i],x[i]);
			e[v].emplace_back(i);
		}
	}
	using solution::get_color;
	using solution::expand;
	using solution::undo;
	void solve(int u=0) {
		if(op[u]==1) expand(x[u]);
		if(op[u]==2) ans[u]=get_color(x[u]);
		for(auto v : e[u])
			solve(v);
		if(op[u]==1) undo();
	}
	void output() {
		for(int i=1; i<=q; ++i)
			if(op[i]==2)
				write(ans[i],'\n');
	}
}
int main() {
	freopen("expand.in","r",stdin);
	freopen("expand.out","w",stdout);
	read(n,m,q);
	B=sqrt(m);
	for(int i=1; i<=n; ++i) read(a[i]);
	for(int i=1; i<=m; ++i) {
		int u,v;
		read(u,v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for(int i=1; i<=n; ++i) {
		sort(e[i].begin(),e[i].end());
		e[i].erase(unique(e[i].begin(),e[i].end()),e[i].end());
		c[i]=(e[i].size()>=B);
	}
	for(int i=1; i<=n; ++i)
		for(auto j : e[i])
			if(c[j])
				g[i].emplace_back(j);
	history_tree::init();
	history_tree::solve();
	history_tree::output();
	return 0;
}