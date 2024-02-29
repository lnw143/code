#include<cstdio>
using namespace std;
const int N = 2e5;
using ll = long long;
int n,i,em,e[N * 2],ls[N + 2],nx[N * 2];
ll f[N + 2],g[N + 2],w[N + 2],ans[N + 2];
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
namespace BIT {
	int t[N + 2];
	void ad(int x,int f) {
		while(x<=n) {
			t[x]+=f;
			x+=x&-x;
		}
	}
	int qr(int x) {
		int r=0;
		while(x) {
			r+=t[x];
			x&=x-1;
		}
		return r;
	}
}
void dfs(int x,int fa) {
	int s=BIT::qr(x-1),sf=BIT::qr(fa-1);
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa) {
			dfs(e[i],x);
			f[x]+=f[e[i]];
		}
	int h=BIT::qr(x-1)-s;
	f[x]+=h;
	g[x]=x-1-h;
	BIT::ad(x,1);
	w[x]=BIT::qr(fa-1)-sf;
}
void dfs2(int x,int fa,ll s) {
	s+=g[x]-w[x];
	ans[x]=s;
	for(int i=ls[x]; i; i=nx[i])
		if(e[i]!=fa)
			dfs2(e[i],x,s);
}
int main() {
	scanf("%d",&n);
	for(i=1; i<n; ++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		insert(u,v);
		insert(v,u);
	}
	dfs(1,1);
	dfs2(1,0,f[1]);
	for(i=1; i<=n; ++i)
		printf("%lld ",ans[i]);
	return 0;
}