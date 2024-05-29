#include<cstdio>
#include<random>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
mt19937 rnd(random_device{}());
const int N(1e5 + 1e6);
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
namespace fhq_treap {
	int rt,tot;
	int ls[N + 2],rs[N + 2],val[N + 2],siz[N + 2],pri[N + 2];
	int newnode(int v) {
		++tot;
		val[tot]=v;
		siz[tot]=1;
		pri[tot]=rnd();
		return tot;
	}
	void pushup(int u) {
		siz[u]=siz[ls[u]]+siz[rs[u]]+1;
	}
	void splitVal(int u,int v,int &x,int &y) {
		if(!u) return x=y=0,void();
		if(val[u]<=v) x=u,splitVal(rs[u],v,rs[u],y);
		else y=u,splitVal(ls[u],v,x,ls[u]);
		pushup(u);
	}
	void splitRnk(int u,int v,int &x,int &y) {
		if(!u) return x=y=0,void();
		if(v<=siz[ls[u]]) y=u,splitRnk(ls[u],v,x,ls[u]);
		else x=u,splitRnk(rs[u],v-siz[ls[u]]-1,rs[u],y);
		pushup(u);
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(pri[u]<pri[v]) return rs[u]=merge(rs[u],v),pushup(u),u;
		return ls[v]=merge(u,ls[v]),pushup(v),v;
	}
	void insert(int v) {
		int x,y;
		splitVal(rt,v,x,y);
		rt=merge(merge(x,newnode(v)),y);
	}
	void remove(int v) {
		int x,y,z;
		splitVal(rt,v,x,z);
		splitVal(x,v-1,x,y);
		y=merge(ls[y],rs[y]);
		rt=merge(merge(x,y),z);
	}
	int getRnk(int v) {
		int x,y,ans;
		splitVal(rt,v-1,x,y);
		ans=siz[x]+1;
		rt=merge(x,y);
		return ans;
	}
	int getVal(int v) {
		int x,y,z,ans;
		splitRnk(rt,v,x,z);
		splitRnk(x,v-1,x,y);
		ans=val[y];
		rt=merge(merge(x,y),z);
		return ans;
	}
	int getPre(int u,int v,int ret=0) {
		if(!u) return ret;
		return val[u]<v?getPre(rs[u],v,val[u]):getPre(ls[u],v,ret);
	}
	int getNxt(int u,int v,int ret=0) {
		if(!u) return ret;
		return val[u]>v?getNxt(ls[u],v,val[u]):getNxt(rs[u],v,ret);
	}
}
int n,m,ans,sum;
int main() {
	using namespace fhq_treap;
	read(n,m);
	rep(i,1,n) {
		int x;
		read(x);
		insert(x);
	}
	rep(i,1,m) {
		int op,x;
		read(op,x);
		x^=ans;
		switch(op) {
			case 1:insert(x);break;
			case 2:remove(x);break;
			case 3:ans=getRnk(x);break;
			case 4:ans=getVal(x);break;
			case 5:ans=getPre(rt,x);break;
			case 6:ans=getNxt(rt,x);break;
		}
		if(op>2) sum^=ans;
	}
	printf("%d",sum);
	return 0;
}