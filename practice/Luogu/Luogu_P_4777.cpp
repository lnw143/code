#include<cstdio>
using namespace std;
using ll = long long;
int n;
ll u,v,a,b;
ll exgcd(ll a,ll b,ll &x,ll &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
int main() {
	scanf("%d",&n);
	u=1,v=0;
	for(int i=1; i<=n; ++i) {
		scanf("%lld%lld",&a,&b);
		ll x,y,d=exgcd(u,a,x,y);
		u=u/d*a;
		v=((b-(__int128)a/d*y%u*(b-v)%u)%u+u)%u;
	}
	printf("%lld",v);
	return 0;
}