#include<cstdio>
#include<cassert>
#include<cctype>
using namespace std;
const int N = 1e4, M = 1e4, K = 4 * 2, S = 1 << K, inf = 1e9;
struct Pair {
	int x,y;
	Pair()=default;
	Pair(int x,int y):x(x),y(y) {}
	bool operator<(const Pair& t) const {
		return x<t.x||x==t.x&&y<t.y;
	}
};
int n,m,k,w[N + 2],f[N + 2][S + 2],g[S + 2],h[S + 2];
int em,e[M * 2 + 2],ls[N + 2],nx[M * 2 + 2],cs[M * 2 + 2];
bool bz[S + 2];
void insert(int u,int v,int w) {
	e[++em]=v;
	nx[em]=ls[u];
	ls[u]=em;
	cs[em]=w;
}
int min(int x,int y) {
	return x<y?x:y;
}
template<typename T> void swap(T& x,T& y) {
	T z=x;
	x=y;
	y=z;
}
namespace heap {
	int sz;
	Pair hp[M + 2];
	void push(const Pair& x) {
		hp[++sz]=x;
		int u=sz;
		while(u>1&&hp[u]<hp[u>>1]) {
			swap(hp[u],hp[u>>1]);
			u>>=1;
		}
	}
	Pair pop() {
		Pair ans=hp[1];
		hp[1]=hp[sz--];
		int u=1;
		while((u<<1)<=sz&&hp[u<<1]<hp[u]||(u<<1|1)<=sz&&hp[u<<1|1]<hp[u]) {
			int v=u<<1;
			if((v|1)<=sz&&hp[v|1]<hp[v]) v|=1;
			swap(hp[u],hp[v]);
			u=v;
		}
		return ans;
	}
}
void dij(const int s) {
	using namespace heap;
	for(int i=1; i<=n; ++i)
		push(Pair(f[i][s],i));
	while(sz) {
		const auto [d,u]=pop();
		if(d!=f[u][s]) continue;
		for(int j=ls[u],v=e[j],w=cs[j]; j; j=nx[j],v=e[j],w=cs[j])
			if(d+w<f[v][s]) {
				f[v][s]=d+w;
				push(Pair(f[v][s],v));
			}
	}
	return ;
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1; i<=m; ++i) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		insert(u,v,w);
		insert(v,u,w);
	}
	for(int i=1; i<=k; ++i)
		w[i]=1<<(i-1),w[i+n-k]=1<<(i+k-1);
	const int s=1<<(2*k);
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<s; ++j)
			f[i][j]=inf;
		f[i][w[i]]=0;
	}
	for(int i=1; i<s; ++i) {
		for(int j=i; j; j=(j-1)&i)
			for(int l=1; l<=n; ++l)
				f[l][i]=min(f[l][i],f[l][j]+f[l][i^j]);
		dij(i);
		g[i]=inf;
		bz[i]=true;
		for(int j=1; j<=k; ++j)
			if(bool(w[j]&i)!=bool(w[n-j+1]&i)) {
				bz[i]=false;
				break;
			}
		if(bz[i]) for(int j=1; j<=n; ++j)
			g[i]=min(g[i],f[j][i]);
	}
	for(int i=1; i<s; ++i) {
		h[i]=g[i];
		if(!bz[i]) continue;
		for(int j=i; j; j=(j-1)&i)
			h[i]=min(h[i],h[j]+h[j^i]);
	}
	printf("%d",h[s-1]==inf?-1:h[s-1]);
	return 0;
}