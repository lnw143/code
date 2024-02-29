#include<cstdio>
using namespace std;
const int N = 1e5;
int T,n,i,j,m,len[N + 2],ans;
char s[N + 2];
int main() {
	freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d%s",&n,s+1);
		m=0;
		for(i=1; i<=n; ++i)
			if(s[i]==s[i-1])
				++len[m];
			else
				len[++m]=1;
		ans=0;
		j=0;
		for(i=1; i<=m; ++i) {
			while(j<=i||len[j]==1) ++j;
			if(len[i]==1) {
				if(j<=m) --len[j];
				else ++i;
			}
			++ans;
		}
		printf("%d\n",ans);
	}
	return 0;
}