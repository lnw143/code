#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
namespace FAST_IO {
	const int BUF(1<<20);
	char buf[BUF],*p1=buf,*p2=buf;
	char pbuf[BUF],*p=pbuf;
	char gc() {
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,BUF,stdin),p1==p2)?EOF:*p1++;
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
}
using FAST_IO::read;
using FAST_IO::write;
using FAST_IO::flush;
using ll = long long;
const int N = 1e7;
const ll inf = 1ll << 60;
int n,fa[N + 2],w[N + 2],sz[N + 2],g[N + 2],dfn[N + 2];
ll pre[N + 2],suf[N + 2],oth[N + 2],h[N + 2];
int s[N + 2],t[N + 2],p[N + 2];
int main() {
	freopen("treeq.in","r",stdin);
	freopen("treeq.out","w",stdout);
	read(n);
	for(int i=2; i<=n; ++i)
		read(fa[i],w[i]);
	sz[1]=1;
	for(int i=n; i>=2; --i)
		sz[fa[i]]+=++sz[i];
	dfn[1]=1;
	for(int i=2; i<=n; ++i) {
		dfn[i]=dfn[fa[i]]+g[fa[i]]+1;
		g[fa[i]]+=sz[i];
	}
	for(int i=2; i<=n; ++i)
		pre[dfn[i]+sz[i]]=max(pre[dfn[i]+sz[i]],(ll)w[i]*sz[i]),
		suf[dfn[i]-1]=max(suf[dfn[i]-1],(ll)w[i]*sz[i]),
		oth[i]=(ll)w[i]*(n-sz[i]);
	for(int i=2; i<=n; ++i) pre[i]=max(pre[i],pre[i-1]);
	for(int i=n-1; i>=1; --i) suf[i]=max(suf[i],suf[i+1]);
	for(int i=1; i<=n; ++i) {
		if(i!=1) oth[i]=max(oth[i],oth[fa[i]]);
		h[i]=max({oth[i],suf[dfn[i]],pre[dfn[i]]});
	}
	for(int i=1; i<=n; ++i) pre[dfn[i]]=suf[dfn[i]]=h[i];;
	s[1]=1;
	for(int i=2; i<=n; ++i) {
		if(pre[i]<pre[i-1]) s[i]=1;
		else if(pre[i]==pre[i-1]) s[i]=s[i-1]+1;
		else pre[i]=pre[i-1],s[i]=s[i-1];
	}
	t[n]=1;
	for(int i=n-1; i>=1; --i) {
		if(suf[i]<suf[i+1]) t[i]=1;
		else if(suf[i]==suf[i+1]) t[i]=t[i+1]+1;
		else suf[i]=suf[i+1],t[i]=t[i+1];
	}
	for(int i=1; i<=n; ++i) oth[i]=inf;
	for(int i=n; i>=2; --i) {
		if(h[i]<oth[i]) p[i]=1,oth[i]=h[i];
		else if(h[i]==oth[i]) ++p[i];
		if(oth[i]<oth[fa[i]]) p[fa[i]]=p[i],oth[fa[i]]=oth[i];
		else if(oth[i]==oth[fa[i]]) p[fa[i]]+=p[i];
	}
	int ans=0;
	for(int i=2; i<=n; ++i) {
		int f=0;
		if(pre[dfn[i]-1]==(ll)w[i]*sz[i]) f+=s[dfn[i]-1];
		if(suf[dfn[i]+sz[i]]==(ll)w[i]*sz[i]) f+=t[dfn[i]+sz[i]];
		if(oth[i]==(ll)w[i]*(n-sz[i])) f+=p[i];
		ans^=f;
		// write(f,'\n');
	}
	write(ans);
	return 0;
}