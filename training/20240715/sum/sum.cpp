#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int P = 19940417, P6 = 3323403;
ll n,m,ans;
ll S(ll n) {
	return n*(n+1)/2%P;
}
ll Sqr(ll n) {
	return n*(n+1)%P*(2*n+1)%P*P6%P;
}
int main() {
	scanf("%lld%lld",&n,&m);
	if(n>m) swap(n,m);
	{
		ll sum1=n*n%P,sum2=m*m%P;
		for(ll i=1; i<=n; i=n/(n/i)+1)
			(sum1-=n/i%P*(S(n/(n/i))-S(i-1))%P)%=P;
		for(ll i=1; i<=m; i=m/(m/i)+1)
			(sum2-=m/i%P*(S(m/(m/i))-S(i-1))%P)%=P;
		ans=sum1*sum2%P;
	}
	{
		ll tot=0;
		(tot+=n*n%P*m%P)%=P;
		ll sum=0;
		for(int i=1; i<=n; i=n/(n/i)+1)
			(sum+=n/i%P*(S(n/(n/i))-S(i-1))%P)%=P;
		(tot-=m*sum%P)%=P;
		sum=0;
		for(int i=1; i<=n; i=m/(m/i)+1)
			(sum+=m/i%P*(S(min(n,m/(m/i)))-S(i-1))%P)%=P;
		(tot-=n*sum%P)%=P;
		sum=0;
		for(int i=1; i<=n; i=min(n/(n/i),m/(m/i))+1)
			(sum+=((n/i%P)*(m/i%P)%P*(Sqr(min(n/(n/i),m/(m/i)))-Sqr(i-1))%P))%=P;
		(tot+=sum)%=P;
		(ans-=tot)%=P;
	}
	printf("%lld",(ans%P+P)%P);
	return 0;
}