#include<cstdio>
#include<vector>
using namespace std;
using ll = long long;
constexpr int N = 5e5, P = 998244353;
int n,q,p,s[N + 2],a[N + 2],fa[N + 2],sum;
ll ans=0;
vector<int> e[N + 2];
bool bz[N + 2];
void add(int x,int type) {
	if(x) (ans+=(ll)s[x]*s[x]%P*type)%=P;
}
void modify(int x,int y) {
	add(x,-1);
	s[x]+=y;
	add(x,1);
}
void set(int &x,int y) {
	modify(x,-1);
	modify(x=y,1);
}
void mark(int x) {
	for(auto i : e[x]) {
		if(!a[i]) ++sum;
		set(a[i],x);
	}
	e[x].clear();
	if(!a[x]) ++sum;
	if(x!=1&&a[x]==fa[x])
		e[fa[x]].push_back(x);
	if(fa[x]!=1&&a[fa[x]]==fa[fa[x]])
		e[fa[fa[x]]].push_back(fa[x]);
	if(x!=1) {
		if(!a[fa[x]]) ++sum;
		set(a[fa[x]],x);
	}
	set(a[x],x);
}
void dfs(int u,int p) {
	fa[u]=p;
	vector<int> son;
	for(auto v : e[u])
		if(v!=p) {
			son.push_back(v);
			dfs(v,u);
		}
	e[u]=son;
}
int main() {
	freopen("hope.in","r",stdin);
	freopen("hope.out","w",stdout);
	scanf("%d%d%d",&n,&q,&p);
	for(int i=1; i<n; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,1);
	s[0]=n;
	for(int i=1; i<=q; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x;
			scanf("%d",&x);
			mark(x);
		} else
			printf("%lld\n",((ans*p%P+((ll)sum*sum%P-ans)*p%P*p%P-(ll)sum*sum%P*p%P*p%P)%P+P)%P);
	}
	return 0;
}