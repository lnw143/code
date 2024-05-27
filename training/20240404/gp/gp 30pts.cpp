#include<cstdio>
#include<map>
using namespace std;
using ll = long long;
const int N = 2e5;
int n,m,c[N + 2],v[N + 2];
int main() {
	freopen("gp.in","r",stdin);
	freopen("gp.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&c[i],&v[i]);
	for(int i=1; i<=m; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int x;
			scanf("%d",&x);
			scanf("%d%d",&c[x],&v[x]);
		} else {
			int s,k;
			scanf("%d%d",&s,&k);
			map<int,int> mp;
			for(int j=s; j<=n; ++j)
				if(mp.count(c[j])) {
					if(k==0) break;
					--k;
					auto &x=mp[c[j]];
					x=max(x,v[j]);
				} else
					mp[c[j]]=v[j];
			ll ans=0;
			for(const auto& [u,v] : mp)
				ans+=v;
			printf("%lld\n",ans);
		}
	}

	return 0;
}