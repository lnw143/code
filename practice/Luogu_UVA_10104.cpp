#include<cstdio>
#include<tuple>
using namespace std;
using ll = long long;
ll exgcd(ll a,ll b,ll &x,ll &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,x,y);
	tie(x,y)=make_tuple(y,x-a/b*y);
	return d;
}
ll a,b;
int main() {
	while(scanf("%lld%lld",&a,&b)==2) {
		ll x,y,d=exgcd(a,b,x,y);
		ll u=b/d,v=a/d;
		ll t=
		x>0&&y<0?min(x/u,-y/v):
		x<0&&y>0?min(-x/u,y/v):
		0;
		printf("%lld %lld %lld\n",x+u*t,y+v*t,d);
	}
	return 0;
}