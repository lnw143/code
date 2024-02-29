#include<cstdio>
#include<cstring>
#include<vector>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
using ll = long long;
const int N(11), M(10);
ll l,r,a[N + 2],f[N + 2][M][M][2][2][2][2];
void split(ll n) {
	per(i,1,N)
		a[i]=n%10,n/=10;
}
ll dp(ll n) {
	split(n);
	memset(f,0,sizeof(f));
	f[0][0][0][0][0][0][0]=1;
	rep(i,1,N) rep(j,0,9) rep(k,0,9) rep(l,0,9)
	for(int u:{0,1}) for(int v:{0,1}) for(int w:{0,1}) for(int e:{0,1}) {
		if(!e&&l>a[i]) continue;
		f[i][k][l][u|(j==k&&k==l)][v|(l==4)][w|(l==8)][e|(l<a[i])]+=f[i-1][j][k][u][v][w][e];
	}
	ll ans=0;
	rep(j,0,9) rep(k,0,9)
	for(int v:{0,1}) for(int w:{0,1}) for(int e:{0,1}) {
		if(v&w) continue;	
		ans+=f[N][j][k][1][v][w][e];
	}
	return ans;
}
int main() {
	scanf("%lld%lld",&l,&r);
	printf("%lld",dp(r)-dp(l-1));
	return 0;
}