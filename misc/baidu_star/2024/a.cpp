#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e3;
using ll = long long;
int n,b,p[N + 2],s[N + 2],ans;
ll f[N + 2][N + 2][2];
int main() {
	scanf("%d%d",&n,&b);
	for(int i=1; i<=n; ++i)
		scanf("%d%d",&p[i],&s[i]);
	memset(f,0x3f,sizeof(f));
	f[0][0][0]=0;
	for(int i=1; i<=n; ++i) {
		f[i][0][0]=0;
		for(int j=1; j<=i; ++j) {
			f[i][j][0]=min(f[i-1][j][0],f[i-1][j-1][0]+p[i]+s[i]);
			f[i][j][1]=min({f[i-1][j][1],f[i-1][j-1][1]+p[i]+s[i],f[i-1][j-1][0]+p[i]/2+s[i]});
		}
	}
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=i; ++j)
			if(f[i][j][0]<=b||f[i][j][1]<=b)
				ans=max(ans,j);
	printf("%d",ans);
	return 0;
}