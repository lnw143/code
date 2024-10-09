#include <cstdio>
using namespace std;
using ll = long long;
const int N = 1e5, V = 50;
namespace linear_basis {
	ll d[V + 2],tot;
	bool zero;
	void insert(ll x) {
		for(int i=V; i>=0; --i)
			if((x>>i)&1) {
				if(d[i]) x^=d[i];
				else return d[i]=x,++tot,void();
			}
		zero=true;
	}
	void initMin() {
		for(int i=1; i<=V; ++i)
			for(int j=i-1; j>=0; --j)
				if((d[i]>>j)&1)
					d[i]^=d[j];
	}
	ll query(ll k) {
		k-=zero;
		if(k>=(1ll<<tot)) return -1;
		ll res=0;
		for(int i=0,j=-1; i<=V; ++i)
			if(d[i]) {
				++j;
				if((k>>j)&1) res^=d[i];
			}
		return res;
	}
}
int n,m;
ll a[N + 2];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	for(int i=1; i<=n; ++i) linear_basis::insert(a[i]);
	linear_basis::initMin();
	scanf("%d",&m);
	for(int i=1; i<=m; ++i) {
		ll x;
		scanf("%lld",&x);
		printf("%lld\n",linear_basis::query(x));
	}
	return 0;
}