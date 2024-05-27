#include<cstdio>
using namespace std;
using ll = long long;
const int N = 43;
int s[N];
ll a,b,sum,s1,s2,s3,i;
int g(ll x) {
	for(int i=2; i<=x; ++i)
		if(x%i!=0)
			return i;
}
int main() {
	// freopen("strength.out","w",stdout);
	// scanf("%lld%lld",&a,&b);
	// a=1e16,b=a+1e9;
	a=1e10,b=a+1e8;
	s[2]=1;
	for(i=3; i<N; ++i)
		s[i]=s[g(i)]+1;
	for(i=12; ; i+=12)
		if(s[g(i)]+1!=3) printf("%lld\n",i);
	return 0;
}