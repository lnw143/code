#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
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
namespace solution {
	const int N = 2e2, M = N * N * N;
	int n,m,p;
	int x1,y1,z1;
	int x2,y2,z2;
#define vec vector
	vec<vec<vec<int>>> id;
	tuple<int,int,int> pos[M + 2];
	vector<int> e[M + 2];
	void cut(int u,int v) {
		e[u].erase(find(e[u].begin(),e[u].end(),v));
		e[v].erase(find(e[v].begin(),e[v].end(),u));
	}
	void add_edge(int u,int v) {
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	void link(int n,int m,int p,int (*vex)(int,int,int)) {
		for(int i=1; i<=n; ++i) {
			for(int k=1; k<p; ++k)
				add_edge(vex(i,1,k),vex(i,1,k+1));
			if(m==1) continue;
			for(int k=1; k<=p; ++k)
				for(int j=2; j<m; ++j)
					add_edge(vex(i,j,k),vex(i,j+1,k));
			add_edge(vex(i,1,1),vex(i,2,1));
			add_edge(vex(i,1,p),vex(i,2,p));
			for(int k=1; k<p; ++k)
				if(k&1) add_edge(vex(i,m,k),vex(i,m,k+1));
				else add_edge(vex(i,2,k),vex(i,2,k+1));
		}
		for(int i=1; i<n; ++i)
			if(i&1) {
				cut(vex(i,1,1),vex(i,2,1));
				cut(vex(i+1,1,1),vex(i+1,2,1));
				add_edge(vex(i,1,1),vex(i+1,1,1));
				add_edge(vex(i,2,1),vex(i+1,2,1));
			} else {
				cut(vex(i,1,1),vex(i,1,2));
				cut(vex(i+1,1,1),vex(i+1,1,2));
				add_edge(vex(i,1,1),vex(i+1,1,1));
				add_edge(vex(i,1,2),vex(i+1,1,2));
			}
	}
	bool bz[M + 2];
	int t[M + 2];
	void dfs(int u,int c) {
		bz[u]=true;
		for(auto v : e[u])
			if(!bz[v]) {
				dfs(v,c^1);
				if(c) {
					t[u]=v;
					t[v]=u;
				}
			}
	}
	void clean(int n) {
		id.clear();
		for(int i=1; i<=n; ++i) e[i].clear(),bz[i]=t[i]=0;
	}
	void solve() {
		read(n,m,p);
		read(x1,y1,z1);
		read(x2,y2,z2);
		if(((x1^y1^z1^x2^y2^z2)&1)==0||n*m*p%2==1) {
			write("No\n");
			return ;
		}
		int cnt=0;
		id=vec<vec<vec<int>>>(n+1,vec<vec<int>>(m+1,vec<int>(p+1,0)));
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				for(int k=1; k<=p; ++k) {
					id[i][j][k]=++cnt;
					pos[cnt]=make_tuple(i,j,k);
				}
		if(!(p&1)) {
			if(m!=1) link(n,m,p,[](int x,int y,int z) { return id[x][y][z]; });
			else link(m,n,p,[](int y,int x,int z) { return id[x][y][z]; });
		} else if(!(m&1)) {
			if(p!=1) link(n,p,m,[](int x,int z,int y) { return id[x][y][z]; });
			else link(p,n,m,[](int z,int x,int y) { return id[x][y][z]; });
		} else {
			if(m!=1) link(p,m,n,[](int z,int y,int x) { return id[x][y][z]; });
			else link(m,p,n,[](int y,int z,int x) { return id[x][y][z]; });
		}
		bz[id[x1][y1][z1]]=bz[id[x2][y2][z2]]=true;
		dfs(id[x1][y1][z1],0);
		dfs(id[x2][y2][z2],0);
		for(int i=1; i<=cnt; ++i)
			if(i!=id[x1][y1][z1]&&i!=id[x2][y2][z2]&&(!bz[i]||!t[i])) {
				clean(cnt);
				write("No\n");
				return ;
			}
		write("Yes\n");
		for(int i=1; i<=n; ++i) {
			for(int j=1; j<=m; ++j,write('\n'))
				for(int k=1; k<=p; ++k) {
					int u=id[i][j][k];
					if(!t[u]) {
						write('0');
						continue;
					}
					int v=t[u];
					if(pos[u]<pos[v]) {
						auto [ux,uy,uz]=pos[u];
						auto [vx,vy,vz]=pos[v];
						if(ux!=vx) write('1');
						else if(uy!=vy) write('2');
						else write('3');
					} else
						write('0');
				}
		}
		clean(cnt);
	}
}
int main() {
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	int T;
	read(T);
	while(T--) solution::solve();
	return 0;
}