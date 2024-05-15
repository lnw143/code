#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int N = 2e5, Q = 5e5, A = 26;
int n,q;
char s[N + 2];
vector<int> d[N + 2];
namespace acam {
	int tot,tr[N + 2][A + 2],fail[N + 2];
	vector<int> insert(const char *s) {
		int u=0;
		vector<int> p;
		for(int i=0; s[i]; ++i) {
			p.pop_back(u);
			if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
			u=tr[u][s[i]-'a'];
		}
		p.push_back(u);
		return p;
	}
	void build() {
		static int que[N + 2];
		int h=0,t=0;
		for(int i=0; i<A; ++i)
			if(tr[0][i])
				que[++t]=tr[0][i];
		while(h<t) {
			int u=que[++h];
			for(int i=0; i<A; ++i)
				if(tr[u][i])
					fail[tr[u][i]]=tr[fail[u]][i],que[++t]=tr[u][i];
				else
					tr[u][i]=tr[fail[u]][i];
		}
	}
}
namespace tree {
	const int logN = 20;
	using namespace acam;
	int anc[N + 2][logN],dep[N + 2];
	vector<int> e[N + 2];
	void dfs(int u) {
		anc[u][0]=fail[u];
		for(int i=1; i<logN; ++i)
			anc[u][i]=anc[anc[u][i-1]][i-1];
		for(auto v : e[u]) {
			dep[v]=dep[u]+1;
			dfs(v);
		}
	}
	void init() {
		for(int i=1; i<=tot; ++i)
			e[fail[i]].push_back(i);
		dfs(0);
	}
	int lca(int x,int y) {
		if(dep[x]>dep[y]) swap(x,y);
		for(int i=logN-1; i>=0; --i)
			if(dep[anc[y][i]]>=dep[x])
				y=anc[y][i];
		if(x==y) return x;
		for(int i=logN-1; i>=0; --i)
			if(anc[x][i]!=anc[y][i])
				x=anc[x][i],y=anc[y][i];
		return anc[x][0];
	}
}
namespace segtree {
	int tot,tr[N << 5],ls[N << 5],rs[N << 5];
	int build(int l,int r) {
		int u=++tot;
		if(l==r) return u;
		int mid=(l+r)/2;
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		return u;
	}
	int modify(int u,int l,int r,int x,int y) {
		
	}
}
int main() {
	scanf("%d%d",&n,&q);
	using namespace acam;
	for(int i=1; i<=n; ++i) {
		scanf("%s",s);
		d[i]=insert(s);
	}
	build();
	tree::init();

	return 0;
}