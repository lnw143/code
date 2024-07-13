#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
const int N = 3e5;
int n,m,tp,stk[N + 2];
struct light {
	int l,r,x;
} a[N + 2];
vector<int> e[N + 2];
priority_queue<ll> f[N + 2];
int merge(int x,int y) {
	if(!x||!y) return x|y;
	if(f[x].size()>f[y].size()) swap(x,y);
	vector<ll> t;
	while(!f[x].empty())
		t.push_back(f[x].top()+f[y].top()),
		f[x].pop(),f[y].pop();
	for(auto i : t)
		f[y].push(i);
	return y;
}
int dfs(int u) {
	int t=u;
	for(auto v : e[u])
		t=merge(t,dfs(v));
	f[t].push(a[u].x);
	return t;
}
int main() {
	freopen("cover.in","r",stdin);
	freopen("cover.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].x);
	sort(a+1,a+m+1,[](auto x,auto y) { return x.l!=y.l?x.l<y.l:x.r>y.r; });
	for(int i=1; i<=m; ++i) {
		while(tp>0&&a[stk[tp]].r<a[i].r) --tp;
		e[stk[tp]].push_back(i);
		stk[++tp]=i;
	}
	int t=dfs(0);
	ll sum=0;
	for(int i=1; i<=m; ++i) {
		if(!f[t].empty()) {
			sum+=f[t].top();
			f[t].pop();
		}
		printf("%lld ",sum);
	}
	return 0;
}