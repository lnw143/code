#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
const int N = 2e5;
int n,q,fa[N + 2];
char s[N + 2];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
vector<int> e[N + 2];
int dfc,dfn[N + 2],low[N + 2];
long long ans;
void dfs(int u) {
	dfn[u]=++dfc;
	for(auto v : e[u])
		dfs(v);
	low[u]=dfc;
}
struct fenwick {
	int s[N + 2];
	void add(int x,int v) {
		for(int i=x; i<=n; i+=i&-i) s[i]+=v;
	}
	void add(int l,int r,int v) {
		add(l,v);
		add(r+1,-v);
	}
	int query(int x) {
		int r=0;
		for(int i=x; i; i&=i-1) r+=s[i];
		return r;
	}
	int query(int l,int r) {
		return query(r)-query(l-1);
	}
} f,g;
int main() {
	freopen("partial.in","r",stdin);
	freopen("partial.out","w",stdout);
	scanf("%d%d%s",&n,&q,s+1);
	for(int i=2; i<=n; ++i)
		scanf("%d",&fa[i]);
	if(*max_element(fa+2,fa+n+1)==1) {
		int sum=n-1-count(s+2,s+n+1,'0');
		for(int i=1; i<=q; ++i) {
			int x;
			char c;
			scanf("%d %c",&x,&c);
			if(x!=1) sum+=(c!='0')-(s[x]!='0');
			s[x]=c;
			printf("%d\n",s[1]=='1'?0:sum);
		}
		return 0;
	}
	for(int i=2; i<=n; ++i) e[fa[i]].push_back(i);
	dfs(1);
	for(int i=1; i<=n; ++i) if(s[i]=='?') s[i]=randint('0','1');
	for(int i=1; i<=n; ++i)
		if(s[i]=='0')
			f.add(dfn[i],low[i],1);
		else
			g.add(dfn[i],1);
	for(int i=1; i<=n; ++i)
		if(s[i]=='1')
			ans+=f.query(dfn[i]);
	for(int i=1; i<=q; ++i) {
		int x;
		char c;
		scanf("%d %c",&x,&c);
		if(c=='?') c=randint('0','1');
		if(s[x]=='0') ans-=g.query(dfn[x],low[x]),f.add(dfn[x],low[x],-1);
		else ans-=f.query(dfn[x]),g.add(dfn[x],-1);
		s[x]=c;
		if(s[x]=='0') ans+=g.query(dfn[x],low[x]),f.add(dfn[x],low[x],1);
		else ans+=f.query(dfn[x]),g.add(dfn[x],1);
		printf("%lld\n",ans);
	}
	return 0;
}