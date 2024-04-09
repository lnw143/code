#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<string>
#include<vector>
using namespace std;
using ll = long long;
constexpr int N = 1e6, A = 26, P = 1e9 + 7;
int n,m,b,ans,u[N + 2],v[N + 2];
char ch[N + 2];
string s[N + 2];
void addAns(ll x) {
	ans+=x%P;
	if(ans>P) ans-=P;
}
namespace sub0 {
	constexpr int N_ = N << 1, logN_ = 22;
	int log2[N_ + 2];
	struct Trie {
		int tot,tr[N + 2][A + 2],pos[N + 2],dfn[N_ + 2],dfc,depth[N + 2],st[logN_][N_ + 2];
		int insert(const string &s) {
			int u=0;
			for(auto c : s) {
				if(!tr[u][c-'a']) tr[u][c-'a']=++tot;
				u=tr[u][c-'a'];
			}
			return u;
		}
		void dfs(int u,int dep) {
			depth[u]=dep;
			dfn[++dfc]=u;
			pos[u]=dfc;
			for(int i=0; i<A; ++i) {
				int v=tr[u][i];
				if(!v) continue;
				dfs(v,dep+1);
				dfn[++dfc]=u;
			}
		}
		int mindep(int u,int v) {
			return depth[u]<depth[v]?u:v;
		}
		void init() {
			dfs(0,0);
			for(int i=1; i<=dfc; ++i)
				st[0][i]=dfn[i];
			for(int j=1; j<logN_; ++j)
				for(int i=1; i+(1<<j)-1<=dfc; ++i)
					st[j][i]=mindep(st[j-1][i],st[j-1][i+(1<<(j-1))]);
		}
		int lca(int x,int y) {
			x=pos[x],y=pos[y];
			if(x>y) swap(x,y);
			int k=log2[y-x+1];
			return mindep(st[k][x],st[k][y-(1<<k)+1]);
		}
	} pre,suf;
	void solve(const int *a,int len) {
		static int p[N + 2],q[N + 2];
		for(int i=1; i<=len; ++i) {
			string t=s[a[i]];
			p[i]=pre.insert(t);
			reverse(t.begin(),t.end());
			q[i]=suf.insert(t);
		}
		pre.init();
		suf.init();
		for(int i=2; i<=pre.dfc||i<=suf.dfc; ++i)
			log2[i]=log2[i>>1]+1;
		for(int i=1; i<len; ++i)
			for(int j=i+1; j<=len; ++j)
				addAns((ll)pre.depth[pre.lca(p[i],p[j])]*suf.depth[suf.lca(q[i],q[j])]);
	}
}
namespace sub1 {
	namespace trie {
		int tot,now;
		vector<vector<int>> tr(1,vector<int>(A + 2,0));
		vector<int> cnt(1,0);
		int son(int u,int c) {
			if(tot>=now) {
				now=tot*2;
				tr.reserve(now);
				cnt.reserve(now);
			}
			if(!tr[u][c-'a']) {
				tr[u][c-'a']=++tot;
				tr.push_back(vector<int>(A + 2,0));
				cnt.push_back(0);
			}
			return tr[u][c-'a'];
		}
	}
	void solve(const int *u,int l1,const int *v, int l2) {
		for(int i=1; i<=l1; ++i) {
			const string &t=s[u[i]];
			int pre=0;
			for(int j=0; j<t.size(); ++j) {
				pre=trie::son(pre,t[j]);
				int now=trie::son(pre,'z'+1);
				for(int k=0; k<t.size(); ++k) {
					now=trie::son(now,t[t.size()-k-1]);
					addAns(trie::cnt[now]);
					++trie::cnt[now];
				}
			}
		}
		for(int i=1; i<=l2; ++i) {
			const string &t=s[v[i]];
			int pre=0;
			for(int j=0; j<b; ++j) {
				pre=trie::son(pre,t[j]);
				int now=trie::son(pre,'z'+1);
				for(int k=0; k<b; ++k) {
					now=trie::son(now,t[t.size()-k-1]);
					addAns(trie::cnt[now]);
				}
			}
		}
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%s",ch);
		s[i]=string(ch);
		m+=s[i].size();
	}
	b=max(1,(int)pow(m,1.0/3));
	for(int i=1; i<=n; ++i)
		(s[i].size()>b?u[++*u]=i:v[++*v]=i);
	sub0::solve(u,*u);
	sub1::solve(v,*v,u,*u);
	printf("%d",ans);
	return 0;
}