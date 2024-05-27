#include<cstdio>
using namespace std;
using ll = long long;
ll a,b,odd,otr;
ll gt(ll x,ll y) {
	ll fir=(a-y+x-1)/x*x+y,las=(b-y)/x*x+y;
	return fir<=las&&a<=fir&&las<=b?(las-fir)/x+1:0;
}
int main() {
	scanf("%lld%lld",&a,&b);
	odd=(b-a+1)/2+((b&1)==(a&1)&&(a&1));
	otr=gt(12,6)+gt(840,420)+gt(720720,360360)+gt(144403552893600,72201776446800);
	printf("%lld",odd*2+otr*4+(b-a+1-odd-otr)*3);
	return 0;
}