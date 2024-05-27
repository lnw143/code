#include<cstdio>
#include<cmath>
#include<random>
using namespace std;
const int N = 2e5 + 2;
using ll = long long;
random_device rd;
mt19937_64 rnd(rd());
int R(int a,int b) {
	return rnd()%(b-a+1)+a;
}
double Rnd() {
	uniform_real_distribution<double> ds(0,1);
	return ds(rnd);
}
int n,x[N],y[N],i,l,r,md;
double sx,sy;
ll k;
ll g(int l,int r,int x) {
	return x<l?l-x:x>r?x-r:0;
}
ll f(int a,int b) {
	ll sum=0;
	for(i=1; i<=n; ++i)
		sum+=g(a,a+md,x[i])+g(b,b+md,y[i]);
	return sum;
}
bool ck() {
	double temp=1e6;
	int xx=R(0,1e9),yy=R(0,1e9);
	ll h=f(xx,yy);
	while(temp>.003) {
		int nx=xx+R(-temp,temp),ny=yy+R(-temp,temp);
		ll dt=f(nx,ny);
		if(exp(-dt/temp)>Rnd()) {
			xx=nx;
			yy=nx;
			h=dt;
		}
		temp*=.998;
		if(h<=k) return true;
		// else printf("%lld\n",h);
	}
	return false;
}
int main() {
	scanf("%d%lld",&n,&k);
	for(i=1; i<=n; ++i)
		scanf("%d%d",&x[i],&y[i]),sx+=x[i],sy+=y[i];
	l=0,r=1e9;
	while(l<=r) {
		md=(l+r)/2;
		if(ck())
			r=md-1;
		else
			l=md+1;
	}
	printf("%d",r+1);
	return 0;
}