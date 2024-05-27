#include<cstdio>
using namespace std;
using ll = long long;
int T;
ll a,b,c;
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
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld%lld",&a,&b,&c);
		ll x,y,d=exgcd(a,b,x,y);
		if(c%d!=0) {
			printf("-1\n");
			continue;
		}
		ll u=b/d,v=a/d;
		ll x_=x*c/d%u;
		if(x_<=0) x_+=u;
		ll y_=(c-a*x_)/b;
		if(y_<=0) {
			y_=y*c/d%v;
			if(y_<=0) y_+=v;
			printf("%lld %lld\n",x_,y_);
			continue;
		}
		ll ans[5]={0,x_,0,0,y_};
		y_=y*c/d%v;
		if(y_<=0) y_+=v;
		x_=(c-b*y_)/a;
		ans[2]=y_;
		ans[3]=x_;
		ans[0]=(ans[3]-ans[1])/u+1;
		for(int i=0; i<5; ++i)
			printf("%d ",ans[i]);
		putchar('\n');
	}
	return 0;
}