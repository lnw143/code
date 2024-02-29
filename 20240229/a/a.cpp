#include<cstdio>
#include<vector>
#include<cctype>
#include<random>
#include<algorithm>
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
	template<typename T,typename ...Args> void write(T &x,Args &...args) {
		write(x);
		write(args...);
	}
};
using FAST_IO::read;
using FAST_IO::write;
using FAST_IO::flush;
mt19937 rnd(random_device{}());
const int N(1e6), M(1e6);
int T,n,m,a,b,rt,fa[N + 2],tag,vis[N + 2];
vector<int> e[N + 2];
struct Edge { int u,v; } edge[M + 2];
void dfs(int u) {
	vis[u]=tag;
	for(int v : e[u])
		if(vis[v]!=tag) {
			fa[v]=u;
			dfs(v);
		}
}
void bfs() {
	static int q[N + 2],h,t;
	h=0,t=1;
	q[1]=rt;
	vis[rt]=tag;
	while(h<t) {
		++h;
		int u=q[h];
		for(int v : e[u])
			if(vis[v]!=tag) {
				vis[v]=tag;
				fa[v]=u;
				q[++t]=v;
			}
	}
}
namespace RANDOM {
	namespace DSU {
		int fa[N + 2];
		void init(int n) {
			rep(i,1,n) fa[i]=i;
		}
		int find(int u) {
			return fa[u]==u?u:fa[u]=find(fa[u]);
		}
		void link(int u,int v) {
			fa[find(u)]=find(v);
		}
		bool check(int u,int v) {
			return find(u)==find(v);
		}
	}
	vector<int> e[N + 2],e_[N + 2];
	int c,d;
	bool in_stk[N + 2];
	void dfs(int u) {
		in_stk[u]=true;
		vis[u]=tag;
		for(int v : e_[u])
			if(vis[v]==tag)
				in_stk[v]?++c:++d;
		for(int v : e[u])
			if(v!=fa[u]) {
				fa[v]=u;
				dfs(v);
			}
		in_stk[u]=false;
	}
	bool check() {
		++tag;
		c=d=0;
		fa[rt]=0;
		dfs(rt);
		return a==c&&b==d;
	}
	void solve() {
		do {
			rep(i,1,m)
				swap(edge[i],edge[rnd()%i+1]);
			DSU::init(n);
			rep(i,1,n) e[i].clear(),e_[i].clear();
			rep(i,1,m) {
				const auto& [u,v]=edge[i];
				if(!DSU::check(u,v)) {
					DSU::link(u,v);
					e[u].push_back(v);
					e[v].push_back(u);
				} else {
					e_[u].push_back(v);
					e_[v].push_back(u);
				}
			}
		} while(!check());
	}
}
void solve() {
	read(n,m,a,b,rt);
	rep(i,1,m) {
		int u,v;
		read(u,v);
		e[u].push_back(v);
		e[v].push_back(u);
		edge[i].u=u;
		edge[i].v=v;
	}
	fa[rt]=0;
	if(b==0) {
		++tag;
		dfs(rt);
	} else if(a==0) {
		++tag;
		bfs();
	} else RANDOM::solve();
	rep(i,1,n) write(fa[i]," \n"[i==n]),e[i].clear();
}
int main() {
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	read(T);
	rep(i,1,T) solve();
	flush();
	return 0;
}