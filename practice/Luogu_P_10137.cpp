#include<cstdio>
#include<algorithm>
#include<utility>
#include<vector>
using namespace std;
using pII = pair<int,int>;
const int N(2e5), logN(20);
int n,q,f[N + 2][logN],g[N + 2][logN],s[2],h[N + 2],v[N + 2];

pII query(int x,int y,int d) {
	int a=lower_bound(h+1,h+*h+1,y)-h,
		b=lower_bound(v+1,v+*v+1,x)-v,t;
	if(v[b]==x) {
		if(a>=*h||y+d<=h[a+1]) return pII(x,y+d);
		t=(h[a]^y)&1;
		d-=h[a]-y;
	} else if(h[a]==y) {
		if(b>=*v||x+d<=v[b+1]) return pII(x+d,y);
		t=(v[b]^x)&1;
		d-=v[b]-x;
	}
	for(int i=logN-1; i>=0; --i)
		if(f[a][i]<=*h&&g[b][i]<=*v&&h[f[a][i]]-h[a]+v[g[b][i]]-v[b]<=d) {
			d-=h[f[a][i]]-h[a]+v[g[b][i]]-v[b];
			a=f[a][i];
			b=g[b][i];
		}
	if(t&&f[a][0]<=*h&&h[f[a][0]]-h[a]<=d) {
		d-=h[f[a][0]]-h[a];
		t^=1;
	} else if(!t&&g[b][0]<=*v&&v[g[b][0]]-v[b]<=d) {
		d-=v[g[b][0]]-v[b];
		t^=1;
	}
	return t?pII(v[b]+d,h[a]):pII(v[b],h[a]+d);
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i) {
		int x;
		char c;
		scanf(" %c %d",&c,&x);
		(c=='H'?h[++*h]:v[++*v])=x;
	}
	auto preProcess=[](int f[][logN],int h[]) {
		sort(h+1,h+*h+1);
		s[0]=s[1]=*h+1;
		for(int i=0; i<logN; ++i)
			f[*h+1][i]=*h+1;
		for(int i=*h; i>=1; --i) {
			f[i][0]=s[h[i]&1^1];
			s[h[i]&1]=i;
			for(int j=1; j<logN; ++j)
				f[i][j]=f[f[i][j-1]][j-1];
		}
	};
	preProcess(f,h);
	preProcess(g,v);
	for(int i=1; i<=q; ++i) {
		int x,y,d;
		scanf("%d%d%d",&x,&y,&d);
		auto [u,v]=query(x,y,d);
		printf("%d %d\n",u,v);
	}
	return 0;
}