#include<cstdio>
#include<algorithm>
#include<utility>
using namespace std;
using pII = pair<int,int>;
const int N(2e5), logN(20);
int n,q,f[N + 2][logN],g[N + 2][logN],s[2],a[N + 2],b[N + 2];
pII query(int x,int y,int d) {
	int u=lower_bound(a+1,a+*a+1,y)-a,
		v=lower_bound(b+1,b+*b+1,x)-b,t=0;
	if(v>*b) return pII(x+d,y);
	if(u>*a) return pII(x,y+d);
	if(x<b[v]) {
		if(x+d<=b[v]) return pII(x+d,y);
		t=(b[v]^x)&1;
		d-=b[v]-x;
	}
	if(y<a[u]) {
		if(y+d<=a[u]) return pII(x,y+d);
		t=(a[u]^y)&1;
		d-=a[u]-y;
	}
	for(int i=logN-1; i>=0; --i)
		if(f[u][i]<=*a&&g[v][i]<=*b&&a[f[u][i]]-a[u]+b[g[v][i]]-b[v]<=d) {
			d-=a[f[u][i]]-a[u]+b[g[v][i]]-b[v];
			u=f[u][i];
			v=g[v][i];
		}
	if(!t&&f[u][0]<=*a&&a[f[u][0]]-a[u]<=d) {
		d-=a[f[u][0]]-a[u];
		u=f[u][0];
		t^=1;
	} else if(t&&g[v][0]<=*b&&b[g[v][0]]-b[v]<=d) {
		d-=b[g[v][0]]-b[v];
		v=g[v][0];
		t^=1;
	}
	return t?pII(b[v]+d,a[u]):pII(b[v],a[u]+d);
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i) {
		int x;
		char c;
		scanf(" %c %d",&c,&x);
		(c=='H'?a[++*a]:b[++*b])=x;
	}
	auto preProcess=[](int f[][logN],int a[]) {
		sort(a+1,a+*a+1);
		s[0]=s[1]=*a+1;
		for(int i=0; i<logN; ++i)
			f[*a+1][i]=*a+1;
		for(int i=*a; i>=1; --i) {
			f[i][0]=s[(a[i]&1)^1];
			s[a[i]&1]=i;
			for(int j=1; j<logN; ++j)
				f[i][j]=f[f[i][j-1]][j-1];
		}
	};
	preProcess(f,a);
	preProcess(g,b);
	for(int i=1; i<=q; ++i) {
		int x,y,d;
		scanf("%d%d%d",&x,&y,&d);
		auto [u,v]=query(x,y,d);
		printf("%d %d\n",u,v);
	}
	return 0;
}