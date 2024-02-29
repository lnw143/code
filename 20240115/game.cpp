#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 8, M = 1e6, P = 1e9 + 7;
const int Ans[7][7] = {
	{},
	{0,2,4,8,16,32},
	{0,4,12,36,108,324},
	{0,8,36,112,336,1008},
	{0,16,108,336,912,2688},
	{0,32,324,1008,2688,7136}
};
using ll = long long;
int n,m,i,len,num[2],ans[2];
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1) {
		if(n&1) (x*=a)%=P;
		(a*=a)%=P;
	}
	return x;
}
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n>m) n^=m^=n^=m;
	if(n<=5&&m<=5) return printf("%d",Ans[n][m]),0;
	if(n==2) return printf("%lld",4ll*qpow(3,m-1)%P),0;
	len=n+m-1;
	num[0]=len/2;
	num[1]=len-num[0];
	ad(ans[0],qpow(2,num[0]-n/2));
	ad(ans[1],qpow(2,num[1]-(n+1)/2+1));
	for(i=2; i<=n; ++i) {
		ad(ans[i&1],qpow(2,num[i&1]-(i+1)/2+1+(i>2)));
	}
	printf("%lld",(ll)ans[0]*ans[1]%P);
	return 0;
}