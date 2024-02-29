#include<cstdio>
using namespace std;
const int N = 2e5 + 2, M = N * 2, P = 1e4 + 7;
int n,i,u,v,w[N],ans,maxn;
struct Graph {
	int em,e[M],ls[N],nx[M];
	void insert(int x,int y) {
		e[++em]=y;
		nx[em]=ls[x];
		ls[x]=em;
	}
} G;
template<typename T> T max(T a,T b) {
	return a<b?b:a;
}
void ad(int &x,int y) {
	x=(x+y)%P;
}
int ms(int x,int y) {
	return ((x-y)%P+P)%P;
}
void dfs(int x,int fa) {
	int sum=0,max1=0,max2=0;
	for(int i=G.ls[x],v=G.e[i]; i; i=G.nx[i],v=G.e[i])
		if(v!=fa) {
			dfs(v,x);
			ad(sum,w[v]);
			if(w[v]>max1) {
				max2=max1;
				max1=w[v];
			} else if(w[v]>max2)
				max2=w[v];
		}
	maxn=max(maxn,max1*max2);
	for(int i=G.ls[x],v=G.e[i]; i; i=G.nx[i],v=G.e[i])
		if(v!=fa)
			ad(ans,ms(sum,w[v])*w[v]%P);
	if(~fa) maxn=max(maxn,max1*w[fa]),ad(ans,w[fa]*sum*2%P);
}
#undef ad
int main() {
	scanf("%d",&n);
	for(i=1; i<n; ++i) {
		scanf("%d%d",&u,&v);
		G.insert(u,v);
		G.insert(v,u);
	}
	for(i=1; i<=n; ++i)
		scanf("%d",&w[i]);
	dfs(1,-1);
	printf("%d %d",maxn,ans);
	return 0;
}