#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5, M = 2 * 1e6;
int n,ans;
char s[M + 2];
namespace trie01 {
	int tot,ch[M + 2][2],s[M + 2],f[M + 2];
	void insert(const char *str) {
		int u=0;
		for(int i=1; str[i]; ++i) {
			if(!ch[u][str[i]-'0']) ch[u][str[i]-'0']=++tot;
			u=ch[u][str[i]-'0'];
		}
		++s[u];
	}
#define ls ch[u][0]
#define rs ch[u][1]
	void put(int u) {
		if(!ls&&!rs) {
			ls=++tot;
			rs=++tot;
			f[ls]=f[rs]=2;
			f[u]=3;
			return ;
		}
		if(!ls||!rs) {
			f[ch[u][!rs]=++tot]=2;
			f[u]=min(f[ls],f[rs])+1;
			return ;
		}
		put(ch[u][f[rs]<f[ls]]);
		f[u]=min(f[ls],f[rs])+1;
	}
	void dfs(int u) {
		f[u]=1e9;
		if(ls) dfs(ls),f[u]=min(f[u],f[ls]+1);
		else f[u]=1;
		if(rs) dfs(rs),f[u]=min(f[u],f[rs]+1);
		else f[u]=1;
		if(!ls&&!rs&&s[u]) --s[u],f[u]=2;
		while(s[u]--) ans+=f[u],put(u);
	}
}
int main() {
	freopen("theft.in","r",stdin);
	freopen("theft.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%s",s+1);
		trie01::insert(s);
	}
	trie01::dfs(0);
	printf("%d",ans);
	return 0;
}