#include<cstdio>
#include<random>
using namespace std;
mt19937_64 rnd(random_device{}());
using ll = long long;
int n=5e3,q=1e7;
ll rand(ll l,ll r) {
	return uniform_int_distribution<ll>(l,r)(rnd);
}
int main() {
	freopen(".in","w",stdout);
	printf("%d\n",n);
	for(int i=1; i<=n; ++i)
		printf("%lld %lld\n",rand(-1e8,1e8),rand(-1e8,1e8));
	printf("%d\n%lld %lld %lld",q,rand(0,(1ll<<31)-1),rand(0,1e8),rand(0,1e16));
	return 0;
}