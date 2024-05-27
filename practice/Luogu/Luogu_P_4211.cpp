#include<cstdio>
#include<vector>
#include<map>
using namespace std;
using ll = long long;
const int N = 5e4, P = 201314;
int n,m,fa[N + 2],l[N + 2],r[N + 2],z[N + 2];
vector<int> e[N + 2];
map<int,int> q[N + 2];
int wson[N + 2],sz[N + 2];
namespace gbt {
	int fa[N + 2],t[N + 2],s[N + 2];
	int ls[N + 2],rs[N + 2],sz[N + 2];
	int w[N + 2],a[N + 2];
	int build(int l,int r) {
		if(l>r) return 0;
		int rt=l;
		for(int i=r; i>l; --i)
			if((s[i]-s[l-1])*2<=(s[r]-s[l-1])) {
				rt=i;
				break;
			}
		ls[t[rt]]=build(l,rt-1);
		rs[t[rt]]=build(rt+1,r);
		fa[ls[t[rt]]]=fa[rs[t[rt]]]=t[rt];
		sz[t[rt]]=r-l+1;
		return t[rt];
	}
	int dfs(int u) {
		for(auto v : e[u])
			if(v!=wson[u])
				fa[dfs(v)]=u;
		int cnt=0,x=u;
		do {
			t[++cnt]=x;
			s[cnt]=s[cnt-1]+sz[x]-sz[wson[x]];
		} while(x=wson[x]);
		return build(1,cnt);
	}
	void add(int u,int f) {
		bool pl=true,g=true;
		while(u) {
			if(g) {
				if(!pl&&ls[u]) w[ls[u]]+=f;
				a[u]+=f;
			}
			pl=(u==ls[fa[u]]);
			if(!pl&&u!=rs[fa[u]]) g=false;
			else g|=(u==rs[fa[u]]);
			u=fa[u];
		}
	}
	int ask(int u) {
		int sum=0,ans=0;
		bool pl=true,pr=false;
		while(u) {
			if(!pl&&!pr) sum=0;
			else if(pr) sum+=sz[rs[u]];
			++sum;
			ans=(ans+a[u]+(ll)w[u]*sum%P)%P;
			pl=(u==ls[fa[u]]);
			pr=(u==rs[fa[u]]);
			u=fa[u];
		}
		return ans;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=2; i<=n; ++i)
		scanf("%d",&fa[i]),++fa[i],e[fa[i]].emplace_back(i);
	for(int i=1; i<=m; ++i) {
		scanf("%d%d%d",&l[i],&r[i],&z[i]);
		++r[i];
		q[l[i]].insert({z[i],0});
		q[r[i]].insert({z[i],0});
	}
	for(int i=n; i>=1; --i) {
		sz[i]+=1;
		sz[fa[i]]+=sz[i];
		if(sz[i]>sz[wson[fa[i]]])
			wson[fa[i]]=i;
	}
	gbt::dfs(1);
	for(int i=0; i<=n; ++i) {
		if(i) gbt::add(i,1);
		for(auto& [u,ans] : q[i]) {
			ans=gbt::ask(u);
			printf("%d %d %d\n",i,u,ans);
		}
	}
	for(int i=1; i<=m; ++i)
		printf("%d\n",q[r[i]][z[i]]-q[l[i]][z[i]]);
	return 0;
}