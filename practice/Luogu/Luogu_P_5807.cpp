#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int N(1e2), S(2e5), P(1e6 + 3);
int T,n,degIn[N + 2],degOut[N + 2],lap[N + 2][N + 2];
ll fac[S + 2];
int det() {
	int sgn=0;
	ll ans=1;
	for(int i=1; i<n; ++i) {
		for(int j=i+1; j<n; ++j) {
			while(lap[j][i]) {
				ll d=lap[i][i]/lap[j][i];
				for(int k=i; k<n; ++k)
					lap[i][k]=(lap[i][k]-d*lap[j][k]%P)%P;
				swap(lap[i],lap[j]);
				sgn^=1;
			}
		}
		if(lap[i][i]) ans=ans*lap[i][i]%P;
	}
	return ((sgn?-ans:ans)%P+P)%P;
}
namespace dsu {
	int fa[N + 2];
	void init() {
		for(int i=1; i<=n; ++i)
			fa[i]=i;
	}
	int find(int x) {
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
}
int solve() {
	using namespace dsu;
	for(int i=1; i<=n; ++i)
		if(degIn[i]!=degOut[i]||degIn[i]&&find(i)!=find(1)) return 0;
	ll ans=(ll)det()*fac[degIn[1]]%P;
	for(int i=2; i<=n; ++i) if(degIn[i]) ans=(ans*fac[degIn[i]-1])%P;
	for(int i=2; i<=n; ++i) if(find(i)==find(1)) return ans;
	return fac[degIn[1]];
}
int main() {
	using namespace dsu;
	fac[0]=1;
	for(int i=1; i<=S; ++i)
		fac[i]=fac[i-1]*i%P;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)
			degIn[i]=degOut[i]=0;
		memset(lap,0,sizeof(lap));
		dsu::init();
		for(int i=1; i<=n; ++i) {
			int s;
			scanf("%d",&s);
			lap[i][i]=s;
			for(int j=1; j<=s; ++j) {
				int u;
				scanf("%d",&u);
				++degIn[u];
				++degOut[i];
				lap[i][u]=(lap[i][u]+P-1)%P;
				fa[find(i)]=find(u);
			}
		}
		printf("%d\n",solve());
	}
	return 0;
}