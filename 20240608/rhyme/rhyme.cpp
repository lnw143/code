#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int M = 2e6, Sig = 26;
int n,ans;
char s[M + 2];
namespace trie {
	int tot,ch[M + 2][Sig + 2],t[M + 2],f[M + 2];
	void insert(const char* s) {
		int u=0;
		for(int i=0; s[i]; ++i) {
			if(!ch[u][s[i]-'a']) ch[u][s[i]-'a']=++tot;
			u=ch[u][s[i]-'a'];
		}
		++t[u];
	}
	void dfs(int u) {
		int max1=0,max2=0;
		f[u]=0;
		for(int i=0; i<Sig; ++i)
			if(ch[u][i]) {
				dfs(ch[u][i]);
				if(t[ch[u][i]]) {
					f[u]+=t[ch[u][i]];
					if(f[ch[u][i]]>max1) max2=max1,max1=f[ch[u][i]];
					else if(f[ch[u][i]]>max2) max2=f[ch[u][i]];
				}
			}
		f[u]+=max1;
		ans=max(ans,f[u]+max2+t[u]);
	}
}
int main() {
	freopen("rhyme.in","r",stdin);
	freopen("rhyme.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		scanf("%s",s);
		reverse(s,s+strlen(s));
		trie::insert(s);
	}
	trie::dfs(0);
	printf("%d\n",ans);
	return 0;
}