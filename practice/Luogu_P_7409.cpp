#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
using ll = long long;
const int N(5e5), LOG_N(22);
int n,m,p[N + 2];
char s[N + 2];
namespace sam {
	const int S(N * 2 + 2), A(26);
	int ch[S][A],len[S],fa[S],las=1,tot=1;
	void insert(int c) {
		int p=las,np=++tot;
		las=np;
		len[np]=len[p]+1;
		for(; p&&!ch[p][c]; p=fa[p]) ch[p][c]=np;
		if(!p) fa[np]=1;
		else {
			int q=ch[p][c];
			if(len[q]==len[p]+1) fa[np]=q;
			else {
				int nq=++tot;
				fa[nq]=fa[q];
				memcpy(ch[nq],ch[q],sizeof(ch[nq]));
				len[nq]=len[p]+1;
				fa[q]=fa[np]=nq;
				for(; p&&ch[p][c]==q; p=fa[p]) ch[p][c]=nq;
			}
		}
	}
	namespace tree {
		const ll P(23333333333333333ll);
		int anc[S][LOG_N],dfn[S],dfc,dep[S],f[S],tag;
		ll ans;
		vector<int> e[S];
		void dfs(int u) {
			dfn[u]=++dfc;
			for(int i=1; i<LOG_N; ++i)
				anc[u][i]=anc[anc[u][i-1]][i-1];
			for(int v:e[u])
				dep[v]=dep[u]+1,
				dfs(v);
		}
		void maketree() {
			for(int i=2; i<=tot; ++i)
				anc[i][0]=fa[i],
				e[fa[i]].push_back(i);
			anc[1][0]=1;
			dfs(1);
		}
		int lca(int x,int y) {
			if(dep[x]<dep[y]) swap(x,y);
			for(int i=LOG_N-1; i>=0; --i)
				if(dep[anc[x][i]]>=dep[y])
					x=anc[x][i];
			if(x==y) return x;
			for(int i=LOG_N-1; i>=0; --i)
				if(anc[x][i]!=anc[y][i])
					x=anc[x][i],y=anc[y][i];
			return anc[x][0];
		}
		vector<int> ve[S];
		int dp(int u) {
			int sz=(f[u]==tag);
			for(int v : ve[u]) {
				int siz=dp(v);
				ans=(siz*sz%P*len[u]%P+ans)%P;
				sz+=siz;
			}
			return sz;
		}
		void link(int x,int y) {
			ve[x].push_back(y);
		}
		ll solve(vector<int> node) {
			sort(node.begin(),node.end(),[](int x,int y){ return dfn[x]<dfn[y]; });
			node.erase(unique(node.begin(),node.end()),node.end());
			static int stk[S],tp;
			stk[tp=1]=1;
			ve[1].clear();
			++tag;
			for(auto u : node)
				if(u!=1) {
					int l=lca(u,stk[tp]);
					if(l!=stk[tp]) {
						while(dfn[l]<dfn[stk[tp-1]]) {
							// ve[stk[tp-1]].push_back(stk[tp]);
							link(stk[tp-1],stk[tp]);
							--tp;
						}
						if(l==stk[tp-1]) {
							// ve[l].push_back(stk[tp]);
							link(l,stk[tp]);
							--tp;
						} else {
							ve[l].clear();
							// ve[l].push_back(stk[tp]);
							link(l,stk[tp]);
							stk[tp]=l;
						}
					}
					ve[u].clear();
					f[u]=tag;
					stk[++tp]=u;
				}
			for(int i=1; i<tp; ++i)
				ve[stk[i]].push_back(stk[i+1]);
			return ans=0,dp(1),ans;
		}
	}
}
vector<int> read() {
	vector<int> a;
	int k;
	scanf("%d",&k);
	a.resize(k);
	for(auto &i : a)
		scanf("%d",&i),i=p[i];
	return a;
}
int main() {
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=n; i>=1; --i) {
		sam::insert(s[i]-'a');
		p[i]=sam::las;
	}
	sam::tree::maketree();
	for(int i=1; i<=m; ++i)
		printf("%lld\n",sam::tree::solve(read()));
	return 0;
}