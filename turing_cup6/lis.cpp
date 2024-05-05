#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N = 2e4, M = 2e2, A = 26;
int n,m,cnt;
char s[N + 2];
struct interv { int lexi,l,r; } a[N * M + 2];
bool operator<(const interv& x,const interv& y) {
	return x.lexi!=y.lexi?x.lexi<y.lexi:x.l>y.l;
}
namespace trie {
	int tot,tr[N * M + 2][A + 2],dfn[N * M + 2],dfc;
	int ext(int x,int y) {
		if(!tr[x][y]) tr[x][y]=++tot;
		return tr[x][y];
	}
	void dfs(int u) {
		dfn[u]=++dfc;
		for(int i=0; i<A; ++i)
			if(tr[u][i])
				dfs(tr[u][i]);
	}
}
namespace fenwick {
	int f[N + 2];
	void add(int x,int v) {
		while(x<=n) {
			f[x]=max(f[x],v);
			x+=x&-x;
		}
	}
	int query(int p) {
		int r=0;
		while(p) {
			r=max(r,f[p]);
			p&=p-1;
		}
		return r;
	}
}
int main() {
	scanf("%d%s",&n,s+1);
	m=sqrt(2*n);
	for(int i=1; i<=n; ++i) {
		int d=0;
		for(int j=0; j<m&&i+j<=n; ++j)
			d=trie::ext(d,s[i+j]-'a');
	}
	trie::dfs(0);
	for(int i=1; i<=n; ++i) {
		int d=0;
		for(int j=0; j<m&&i+j<=n; ++j) {
			d=trie::ext(d,s[i+j]-'a');
			a[++cnt]=interv{trie::dfn[d],i,i+j};
		}
	}
	sort(a+1,a+cnt+1);
	for(int i=1; i<=cnt; ++i) {
		using namespace fenwick;
		add(a[i].r,query(a[i].l-1)+1);
	}
	printf("%d",fenwick::query(n));
	return 0;
}