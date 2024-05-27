#include<cstdio>
#include<random>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
mt19937 rnd(random_device{}());
const int N(1e5), inf(1<<30);
namespace treap {
	int tot;
	int son[N + 2][2],val[N + 2],siz[N + 2],cnt[N + 2],pri[N + 2];
	int newnode(int v) {
		++tot;
		val[tot]=v;
		siz[tot]=cnt[tot]=1;
		pri[tot]=rnd();
		return tot;
	}
	void upd(int &u) {
		siz[u]=siz[son[u][0]]+siz[son[u][1]]+cnt[u];
	}
	void rotate(int &u,int d) {
		int tmp=son[u][d];
		son[u][d]=son[tmp][!d];
		son[tmp][!d]=u;
		upd(u);
		upd(tmp);
		u=tmp;
	}
	void insert(int &u,int v) {
		if(!u) {
			u=newnode(v);
			return ;
		}
		if(val[u]==v) ++cnt[u];
		else {
			int d=val[u]<v;
			insert(son[u][d],v);
			if(pri[son[u][d]]<pri[u]) rotate(u,d);
		}
		upd(u);
	}
	void remove(int &u,int v) {
		if(!u) return ;
		if(v==val[u]) {
			if(cnt[u]>1) --cnt[u],upd(u);
			else {
				if(son[u][0]||son[u][1]) {
					if(!son[u][1]||son[u][0]&&pri[son[u][0]]<pri[son[u][1]])
						rotate(u,0),remove(son[u][1],v);
					else rotate(u,1),remove(son[u][0],v);
					upd(u);
				} else u=0;
			}
		} else {
			remove(son[u][v>val[u]],v);
			upd(u);
		}
	}
	int getRnk(int &u,int v) {
		if(!u) return 1;
		if(val[u]==v) return siz[son[u][0]]+1;
		if(val[u]<v) return siz[son[u][0]]+cnt[u]+getRnk(son[u][1],v);
		return getRnk(son[u][0],v);
	}
	int getVal(int &u,int v) {
		if(v<=siz[son[u][0]]) return getVal(son[u][0],v);
		v-=siz[son[u][0]];
		if(v<=cnt[u]) return val[u];
		return getVal(son[u][1],v-cnt[u]);
	}
	int getPre(int &u,int v,int ret=-inf) {
		if(!u) return ret;
		return val[u]<v?getPre(son[u][1],v,val[u]):getPre(son[u][0],v,ret);
	}
	int getNxt(int &u,int v,int ret=inf) {
		if(!u) return ret;
		return val[u]>v?getNxt(son[u][0],v,val[u]):getNxt(son[u][1],v,ret);
	}
}
int n,rt;
int main() {
	using namespace treap;
	scanf("%d",&n);
	rep(i,1,n) {
		int op,x,ans;
		scanf("%d%d",&op,&x);
		switch(op) {
			case 1:insert(rt,x);break;
			case 2:remove(rt,x);break;
			case 3:ans=getRnk(rt,x);break;
			case 4:ans=getVal(rt,x);break;
			case 5:ans=getPre(rt,x);break;
			case 6:ans=getNxt(rt,x);break;
		}
		if(op>2) printf("%d\n",ans);
	}
	return 0;
}