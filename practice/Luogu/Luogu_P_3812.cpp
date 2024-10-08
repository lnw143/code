#include <cstdio>
using namespace std;
using ll = long long;
const int N = 50, M = 50;
int n;
ll a[N + 2];
namespace linear_basis {
	ll d[M + 2];
	bool insert(ll x) {
		for(int i=M-1; i>=0; --i)
			if((x>>i)&1) {
				if(d[i]) x^=d[i];
				else return d[i]=x,true;
			}
		return false;
	}
	ll get_max() {
		ll x=0;
		for(int i=M-1; i>=0; --i)
			if(!((x>>i)&1)&&d[i])
				x^=d[i];
		return x;
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	for(int i=1; i<=n; ++i) linear_basis::insert(a[i]);
	printf("%lld",linear_basis::get_max());
	return 0;
}