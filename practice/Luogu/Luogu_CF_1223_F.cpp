#include<cstdio>
#include<map>
using namespace std;
const int N = 3e5;
int T,n,a[N + 2];
namespace trie {
	int tot,fa[N + 2],cnt[N + 2],t[N + 2];
	map<int,int> mp[N + 2];
	int son(int x,int c) {
		if(!mp[x].count(c)) {
			++tot;
			fa[tot]=x;
			t[tot]=c;
			mp[x][c]=tot;
		}
		return mp[x][c];
	}
	void clean() {
		for(int i=0; i<=tot; ++i)
			cnt[i]=fa[i]=0,mp[i].clear();
		tot=0;
	}
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)
			scanf("%d",&a[i]);
		int u=0;
		long long ans=0;
		using namespace trie;
		cnt[0]=1;
		for(int i=1; i<=n; ++i) {
			if(i>1&&a[i]==t[u])	
				u=fa[u];
			else
				u=son(u,a[i]);
			ans+=cnt[u]++;
		}
		printf("%lld\n",ans);
		clean();
	}
	return 0;
}