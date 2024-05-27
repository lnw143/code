#include<cstdio>
#include<vector>
#include<cctype>
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
	template<typename T,typename ...Args> void write(T x,Args ...args) {
		write(x);
		write(args...);
	}
	struct TMP { ~TMP() { flush(); } } tmp;
};
using FAST_IO::read;
using FAST_IO::write;
using FAST_IO::flush;
const int N(1e6), M(1e6);
int T,n,m,a,b,c,d,rt,fa[N + 2],tag,vis[N + 2],dep[N + 2];
bool in_stk[N + 2];
vector<int> e[N + 2];
void dfs(int u) {
	vis[u]=tag;
	in_stk[u]=true;
	if(a==c) {
		fa[u]=0;
		for(int v : e[u])
			if(in_stk[v])
				if(dep[v]<dep[fa[u]])
					fa[u]=v;
	} else {
		vector<int> anc;
		for(int v : e[u])
			if(v!=fa[u]&&in_stk[v])
				anc.push_back(v);
		if(c+anc.size()>a) {
			sort(anc.begin(),anc.end(),[](int x,int y){ return dep[x]<dep[y]; });
			fa[u]=anc[a-c];
			c=a;
		} else c+=anc.size();
	}
	for(int v : e[u])
		if(vis[v]!=tag) {
			dep[v]=dep[u]+1;
			fa[v]=u;
			dfs(v);
		}
	in_stk[u]=false;
}
void solve() {
	read(n,m,a,b,rt);
	rep(i,1,m) {
		int u,v;
		read(u,v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	c=d=0;
	dep[rt]=0;
	dep[0]=1<<30;
	fa[rt]=0;
	++tag;
	dfs(rt);
	rep(i,1,n) write(fa[i]," \n"[i==n]),e[i].clear();
}
int main() {
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	read(T);
	rep(i,1,T) solve();
	return 0;
}