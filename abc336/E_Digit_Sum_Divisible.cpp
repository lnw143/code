#include<atcoder/all>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace atcoder;
using namespace std;
using ll = long long;
const int N = 14;
ll n,m,a[N + 2],maxn,f[N + 2][N * 10 + 2][N * 10 + 2][2],ans;
ll lg10(ll x) {
	ll r=0;
	while(x) a[++r]=x%10,x/=10;
	return r;
}
ll dp(ll x) {
	memset(f,0,sizeof(f));
	for(int i=0; i<=a[1]; ++i)
		++f[1][i][i%x][i<a[1]];
	for(int i=1; i<m; ++i) {
		for(int j=0; j<10; ++j)
			for(int k=0; k+j<=x; ++k)
				for(int l=0; l<x; ++l) {
					if(j<a[i+1])
						f[i+1][k+j][(l*10+j)%x][1]+=f[i][k][l][0];
					else if(j==a[i+1])
						f[i+1][k+j][(l*10+j)%x][0]+=f[i][k][l][0];
					f[i+1][k+j][(l*10+j)%x][1]+=f[i][k][l][1];
				}
	}
	return f[m][x][0][0]+f[m][x][0][1];
}
int main() {
	scanf("%lld",&n);
	m=lg10(n);
	maxn=m*9;
	for(int i=1; i*2<=m; ++i)
		swap(a[i],a[m-i+1]);
	for(int i=1; i<=maxn; ++i)
		ans+=dp(i);
	printf("%lld",ans);
	return 0;
}