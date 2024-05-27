#include<cstdio>
#include<cstring>
using namespace std;
using ll = long long;
const int N = 1e6 + 2;
int x1,y1,x2,y2,x3,y3;
ll r1;
bool bz[N];
ll find(ll a,ll b,ll x,ll y) {
	memset(bz,0,sizeof(bz));
	while(!bz[a%x]) {
		if(a%x==y) return a;
		bz[a%x]=true;
		a+=b;
	}
	return -1;
}
ll gcd(ll x,ll y) {
	ll r=x%y;
	while(r) {
		x=y,y=r;
		r=x%y;
	}
	return y;
}
int main() {
	freopen("min.in","r",stdin);
	freopen("min.out","w",stdout);
	scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
	r1=find(x1,y1,y2,x2);
	if(r1==-1)
		printf("-1");
	else
		printf("%lld",find(r1,(ll)y1*y2/gcd(y1,y2),y3,x3));
	return 0;
}