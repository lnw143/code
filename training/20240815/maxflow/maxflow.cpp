#include <cstdio>
#include <vector>
#include <chrono>
#include <random>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
namespace IO {
	static const int BUF = 1<<20;
	static char pbuf[BUF],*p=pbuf,*ch;
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
		char c=*ch++;
		T f=1;
		for(; c<'0'||c>'9'; c=*ch++) if(c=='-') f=-1;
		for(; c>='0'&&c<='9'; c=*ch++) x=(x<<3)+(x<<1)+(c^48);
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
	inline void init(const char* filein, const char* fileout) {
		if(*filein) freopen(filein,"r",stdin);
		if(*fileout) freopen(fileout,"w",stdout);
    	ch=(char*)mmap(NULL,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);
	}
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
const int N = 5.5e5;
int n,m,w[N + 2];
bool vis[N + 2],cir[N + 2];
struct edge {
	int v,id;
};
vector<edge> e[N + 2];
int dfs(int u,int p) {
	int c=0;
	vis[u]=true;
	for(auto [v,id] : e[u]) {
		if(v==p) continue;
		if(vis[v]) {
			if(cir[id]) continue;
			c=v,cir[id]=true;
		}
		else {
			int r=dfs(v,u);
			if(r) c=r,cir[id]=true;
		}
	}
	if(c==u) c=0;
	return c;
}
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
template<int S> struct treap {
	int tot,rt,ls[S + 2],rs[S + 2],val[S + 2],sz[S + 2];
	ll sum[S + 2];
	unsigned int pri[S + 2];
	int newnode(int _val) {
		int u=++tot;
		ls[u]=rs[u]=0;
		sz[u]=1;
		sum[u]=val[u]=_val;
		pri[u]=rnd();
		return u;
	}
	void pushup(int u) {
		sz[u]=sz[ls[u]]+sz[rs[u]]+1;
		sum[u]=sum[ls[u]]+sum[rs[u]]+val[u];
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(pri[u]<pri[v]) return rs[u]=merge(rs[u],v),pushup(u),u;
		else return ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	void spval(int u,int &x,int &y,ll k) {
		if(!u) return x=y=0,void();
		if(val[u]<=k) x=u,spval(rs[u],rs[u],y,k);
		else y=u,spval(ls[u],x,ls[u],k);
		pushup(u);
	}
	void sprnk(int u,int &x,int &y,int k) {
		if(!u) return x=y=0,void();
		if(k<=sz[ls[u]]) y=u,sprnk(ls[u],x,ls[u],k);
		else x=u,sprnk(rs[u],rs[u],y,k-sz[ls[u]]-1);
		pushup(u);
	}
	void insert(int _val) {
		int x,y;
		spval(rt,x,y,_val);
		rt=merge(merge(x,newnode(_val)),y);
	}
	void del(int _val) {
		int x,y,z;
		spval(rt,x,z,_val);
		spval(x,x,y,_val-1);
		y=merge(ls[y],rs[y]);
		rt=merge(merge(x,y),z);
	}
	ll calc(ll _val) {
		int x,y;
		spval(rt,x,y,_val);
		ll res=_val*sz[x]-sum[x];
		rt=merge(x,y);
		return res;
	}
	ll calc2(ll _val) {
		int x,y,z;
		sprnk(rt,x,y,2);
		if(sum[x]>=_val) return rt=merge(x,y),0;
		sprnk(x,x,z,1);
		if((_val+1)/2<=val[z]) {
			ll res=_val-val[z]-val[x];
			rt=merge(merge(x,z),y);
			return res;
		}
		rt=merge(merge(x,z),y);
		spval(rt,x,y,_val/2);
		if(!x) return rt=y,0;
		ll res=(_val+1)/2*sz[x]-sum[x]-_val%2;
		rt=merge(x,y);
		return res;
	}
	void clean() {
		tot=rt=0;
	}
};
treap<N * 2> f,g;
ll cost(ll x) {
	return g.calc(x)+f.calc2(x);
}
int main() {
	IO::init("maxflow.in","maxflow.out");
	int T;
	read(T);
	while(T--) {
		read(n,m);
		for(int i=1; i<=n; ++i) {
			int u,v;
			read(u,v,w[i]);
			e[u].push_back(edge{v,i});
			e[v].push_back(edge{u,i});
		}
		dfs(1,1);
		for(int i=1; i<=n; ++i)
			(cir[i]?f:g).insert(w[i]);
		for(int i=1; i<=m; ++i) {
			int op;
			read(op);
			if(op==1) {
				int x,y;
				read(x,y);
				auto &tr=cir[x]?f:g;
				tr.del(w[x]);
				tr.insert(y);
				w[x]=y;
			} else {
				ll z;
				read(z);
				ll l=1,r=1e12;
				while(l<=r) {
					ll mid=(l+r)/2;
					if(cost(mid)<=z) l=mid+1;
					else r=mid-1;
				}
				write(l-1,'\n');
			}
		}
		for(int i=1; i<=n; ++i) cir[i]=vis[i]=0,e[i].clear();
		f.clean();
		g.clean();
	}
	return 0;
}