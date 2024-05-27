#include<cstdio>
#include<algorithm>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
const int N(1e4), inf((1<<31) - 1);
namespace BST {
	int tot;
	int ls[N + 5],rs[N + 5];
	int val[N + 5],cnt[N + 5],sz[N + 5];
	int newnode(int x) {
		++tot;
		val[tot]=x;
		cnt[tot]=sz[tot]=1;
		return tot;
	}
	void init() {
		newnode(inf);
		ls[1]=newnode(-inf);
	}
	void insert(int &u,int v) {
		if(!u) {
			u=newnode(v);
			return ;
		}
		if(v<val[u]) insert(ls[u],v);
		else if(v>val[u]) insert(rs[u],v);
		else ++cnt[u];
		sz[u]=sz[ls[u]]+sz[rs[u]]+cnt[u];
	}
	int findRnk(int u,int v) {
		if(!u) return 1;
		if(v==val[u]) return sz[ls[u]]+1;
		if(v>val[u]) return sz[ls[u]]+cnt[u]+findRnk(rs[u],v);
		return findRnk(ls[u],v);
	}
	int findVal(int u,int rnk) {
		if(sz[ls[u]]>=rnk) return findVal(ls[u],rnk);
		rnk-=sz[ls[u]];
		if(cnt[u]>=rnk) return val[u];
		return findVal(rs[u],rnk-cnt[u]);
	}
	int findPre(int u,int v,int ans=-inf) {
		if(!u) return ans;
		if(val[u]>=v) return findPre(ls[u],v,ans);
		return findPre(rs[u],v,val[u]);
	}
	int findNxt(int u,int v,int ans=inf) {
		if(!u) return ans;
		if(val[u]<=v) return findNxt(rs[u],v,ans);
		return findNxt(ls[u],v,val[u]);
	}
}
int q,rt=1;
int main() {
	scanf("%d",&q);
	BST::init();
	rep(i,1,q) {
		int op,x;
		scanf("%d%d",&op,&x);
		using namespace BST;
		if(op==1) printf("%d\n",findRnk(1,x)-1);
		else if(op==2) printf("%d\n",findVal(1,x+1));
		else if(op==3) printf("%d\n",findPre(1,x));
		else if(op==4) printf("%d\n",findNxt(1,x));
		else insert(rt,x);
	}
	return 0;
}