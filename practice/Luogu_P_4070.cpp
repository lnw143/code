#include<cstdio>
using namespace std;
constexpr int N = 1e5;
int n,a[N + 2],y[N + 2],sa[N + 2],rk[2][N + 2],cnt[N + 2];

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&x[i]),y[i]=x[i];
	sort(y+1,y+n+1)
	for(int i=1; i<=n; ++i)
		rk[0][i]=x[i];
	
	return 0;
}