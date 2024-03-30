#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
using vi = vector<int>;
const int S(5e5), A(26), P(1e9 + 7);
using ll = long long;
int n,ans;
char s[S + 2];
struct Trie {
	int tr[S + 2][A + 2],len[S + 2],cnt[S + 2],tot;
	void insert(const char *s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!tr[u][s[i]-'a']) {
				len[++tot]=len[u]+1;
				tr[u][s[i]-'a']=tot;
			}
			u=tr[u][s[i]-'a'];
		}
		++cnt[u];
		return ;
	}
} pre,suf;
namespace SufTree {
	vi e[S + 2];
	const int LOG_S(22);
	int dep[S + 2],ord[S * 2 + 2],pos[S + 2],st[S + 2][LOG_S],log2[S + 2];
	auto& [tr,len,cnt,tot]=suf;
	void insert(int x,int y) { e[x].push_back(y); }
	void init() {
		for(int i=0; i<=tot; ++i)
			for(int j=0; j<A; ++j)
				if(tr[i][j])
					insert(i,tr[i][j]),insert(tr[i][j],i);
	}
	void dfs(int u) {
		ord[++*ord]=u;
		pos[u]=*ord;
		for(int v : e[u]) if(!pos[v]) {
			dfs(v);
			ord[++*ord]=u;
		}
	}
	int Min(int x,int y) { return dep[x]<dep[y]?x:y; }
#define pw2(x) (1<<(x))
	int lca(int x,int y) {
		static bool inited=false;
		if(!inited) {
			inited=true;
			for(int i=2; i<=*ord; ++i)
				log2[i]=log2[i>>1]+1;
			for(int i=1; i<=*ord; ++i)
				st[i][0]=ord[i];
			for(int j=1; j<LOG_S; ++j)
				for(int i=1; i+pw2(j)-1<=*ord; ++i)
					st[i][j]=Min(st[i][j-1],st[i+pw2(j-1)][j-1]);
		}
		y=pos[y],x=pos[x];
		if(x>y) swap(x,y);
		int k=log2[y-x+1];
		return Min(st[x][k],st[y-pw2(k)+1][k]);
	}
#undef pw2
}
namespace Virtree {
	using namespace SufTree;
	vi ev[S + 2];
#define dfn pos
	void ins(int x,int y) { ev[x].push_back(y); }
	void build(vi node) {
		stable_sort(node.begin(),node.end(),[](int x,int y){ return dfn[x]<dfn[y]; });
		static int stk[S + 2],tp;
		stk[tp=1]=0;
		for(int u : node) if(u!=0) {
			int l=lca(u,stk[tp]);
			if(l!=stk[tp]) {
				while(dfn[stk[tp-1]]>dfn[l]) {
					ins(stk[tp-1],stk[tp]);
					--tp;
				}
				if(l==stk[tp-1]) {
					ins(l,stk[tp]);
					--tp;
				} else {
					ev[l].clear();
					ins(l,stk[tp]);
					stk[tp]=l;
				}
			}
			ev[u].clear();
			stk[++tp]=u;
		}
		while(tp>1) {
			ins(stk[tp-1],stk[tp]);
			--tp;
		}
	}
	int sz[S + 2],sum;
	void dfs(int u) {
		sz[u]=pre.cnt[u];
		for(int v : ev[u]) {
			dfs(v);
			sz[u]+=sz[v];
		}
		for(int v : ev[u])
			sum=(sum+(ll)(sz[u]-sz[v])*sz[v]%P*pre.len[u]);
	}
	int solve() {
		sum=0;
		dfs(0);
		return sum;
	}
}
namespace Divide {
	int maxn,maxv,siz,f[S + 2];
	bool vis[S + 2];
	vi node;
	vi e[S + 2];
	auto& [tr,len,Cnt,tot]=pre;
	void insert(int x,int y) {
		e[x].push_back(y);
		e[y].push_back(x);
	}
	void init() {
		for(int i=0; i<=tot; ++i)
			for(int j=0; j<A; ++j)
				if(tr[i][j])
					insert(i,tr[i][j]),insert(tr[i][j],i);
	}
	int cnt(int u) {
		if(vis[u]) return 0;
		vis[u]=true;
		node.push_back(u);
		int sz=1;
		for(int v : e[u])
			sz+=cnt(v);
		vis[u]=false;
		return sz;
	}
	int dfs(int u) {
		if(vis[u]) return 0;
		vis[u]=true;
		int sz=1,maxsz=0;
		for(int v : e[u]) {
			int s=dfs(v);
			maxsz=max(maxsz,s);
			sz+=s;
		}
		maxsz=max(maxsz,siz-sz);
		if(maxsz<maxv) {
			maxv=maxsz;
			maxn=u;
		}
		vis[u]=false;
		return sz;
	}
	int findCent(int u) {
		maxn=u;
		maxv=1e9;
		siz=cnt(u);
		dfs(u);
		return maxn;
	}
	int solve(int u) {
		node.clear();
		int cent=findCent(u);
		vis[cent]=true;
		Virtree::build(node);
		int g=f[cent]=Virtree::solve();
		for(int v : e[cent])
			if(!vis[v])
				g=(g-f[solve(v)])%P;
		ans=(ans+pre.len[cent]*(ll)((g+P)%P)%P)%P;
		return cent;
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%s",s);
		pre.insert(s);
		reverse(s,s+strlen(s));
		suf.insert(s);
	}
	Divide::init();
	SufTree::init();
	SufTree::dfs(0);
	Divide::solve(0);
	printf("%d",ans);
	return 0;
}