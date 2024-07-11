#include <cstdio>
#include <set>
using namespace std;
const int N = 1e5, M = 1e6;
int n,m,a[N + 2],c[M + 2],ans=1;
set<int> st[M + 2];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=2; i<=n; ++i) if(a[i]!=a[i-1]) ++ans;
	for(int i=1; i<=n; ++i) st[a[i]].insert(i);
	for(int i=1; i<=m; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x,y,f=0;
			scanf("%d%d",&x,&y);
			if(x==y) continue;
			if(st[x].size()>st[y].size()) {
				f=1;
				swap(x,y);
			}
			for(auto i : st[x])
				ans-=st[y].count(i-1)+st[y].count(i+1);
			for(auto i : st[x]) st[y].insert(i);
			st[x].clear();
			if(f) st[x].swap(st[y]);
		} else
			printf("%d\n",ans);
	}
	return 0;
}