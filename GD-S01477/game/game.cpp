#include<cstdio>
using namespace std;
const int N = 2e6 + 2;
int n,i,j,k,tot,fa[N],em,e[N],ls[N],nx[N],f[N];
char s[N],t[N];
long long ans;
void insert(int x,int y) {
	e[++em]=y;
	nx[em]=ls[x];
	ls[x]=em;
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%s",&n,s+1);
	f[0]=1;
	for(i=1; i<=n; ++i) {
		if(t[j]==s[i])
			j=fa[j];
		else {
			for(k=ls[j]; k; k=nx[k])
				if(t[e[k]]==s[i]) {
					j=e[k];
					goto et;
				}
			t[++tot]=s[i];
			fa[tot]=j;
			insert(j,tot);
			j=tot;
		}
et:
		ans+=f[j];
		++f[j];
	}
	printf("%lld",ans);
	return 0;
}
