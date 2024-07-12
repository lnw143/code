#include <cstdio>
using namespace std;
using ll = long long;
const int N = 1e6;
int n,q;
namespace fenwick {
	struct ftree {
		ll s[N + 2];
		void add(int u,ll x) {
			for(; u<=n; u+=u&-u) s[u]+=x;
		}
		ll sum(int u) {
			ll r=0;
			for(; u; u&=u-1) r+=s[u];
			return r;
		}
	} t1,t2;
	void add(int u,ll x) {
		t1.add(u,x);
		t2.add(u,u*x);
	}
	void add(int l,int r,ll x) {
		add(l,x);
		add(r+1,-x);
	}
	ll sum(int u) {
		return (u+1)*t1.sum(u)-t2.sum(u);
	}
	ll sum(int l,int r) {
		return sum(r)-sum(l-1);
	}	
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i) {
		int a;
		scanf("%d",&a);
		fenwick::add(i,i,a);
	}
	for(int i=1; i<=q; ++i) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			fenwick::add(l,r,x);
		} else {
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",fenwick::sum(l,r));
		}
	}
	return 0;
}