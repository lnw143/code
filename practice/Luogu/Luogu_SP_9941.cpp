#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
using ll = long long;
const int N = 2e4, S = 3e5, A = 26;
const ll inf = 1ll << 30;
int T,n,p[N + 2];
ll w[N + 2];
char s[S + 2];
namespace acam {
	int tot,tr[S + 2][A + 2],fail[S + 2],fa[S + 2];
	int dfc,dfn[S + 2],low[S + 2];
	vector<int> e[S + 2];
	int insert(const char *s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
			u=tr[u][s[i]-'a'];
		}
		return u;
	}
	void build() {
		static int que[S + 2];
		int h=0,t=0;
		for(int i=0; i<A; ++i)
			if(tr[0][i]) que[++t]=tr[0][i],fa[tr[0][i]]=fail[tr[0][i]]=0;
		while(h<t) {
			int u=que[++h];
			e[fail[u]].push_back(u);
			for(int i=0; i<A; ++i)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],que[++t]=tr[u][i],fa[tr[u][i]]=u;
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
	void dfs(int u) {
		dfn[u]=++dfc;
		for(auto v : e[u])
			dfs(v);
		low[u]=dfc;
	}
	void clean() {
		dfc=0;
		for(int i=0; i<=tot; ++i)
			e[i].clear(),memset(tr[i],0,sizeof(tr[i]));
		tot=0;
	}
}
namespace segtree {
	ll tr[S * 4 + 5];
#define ls (u<<1)
#define rs (ls|1)
#define mid (l+r>>1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		tr[u]=0;
		if(l==r) return ;
		build(li);
		build(ri);
	}
	ll query(int u,int l,int r,int x) {
		if(r<x||x<l) return -inf;
		if(l==r) return tr[u];
		return max(tr[u],x<=mid?query(li,x):query(ri,x));
	}
	void modify(int u,int l,int r,int x,int y,ll f) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			tr[u]=max(tr[u],f);
			return ;
		}
		modify(li,x,y,f);
		modify(ri,x,y,f);
	}
}
int main() {
	scanf("%d",&T);
	for(int id=1; id<=T; ++id) {
		scanf("%d",&n);
		using namespace acam;
		for(int i=1; i<=n; ++i) {
			scanf("%s%lld",s,&w[i]);
			p[i]=insert(s);
		}
		build();
		dfs(0);
		ll Ans=0;
		segtree::build(1,1,dfc);
		for(int i=1; i<=n; ++i) {
			using namespace segtree;
			ll ans=0;
			for(int j=p[i]; j; j=fa[j])
				ans=max(ans,query(1,1,dfc,dfn[j]));
			ans+=w[i];
			modify(1,1,dfc,dfn[p[i]],low[p[i]],ans);
			Ans=max(Ans,ans);
		}
		printf("Case #%d: %lld\n",id,Ans);
		clean();
	}
	return 0;
}