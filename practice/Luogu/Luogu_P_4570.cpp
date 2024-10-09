#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 1e3, V = 64;
int n,ans;
struct Stone {
	ll x;
	int y;
} a[N + 2];
ll d[V + 2];
bool insert(ll x) {
	for(int i=V; i>=0; --i)
		if((x>>i)&1) {
			if(d[i]) x^=d[i];
			else return d[i]=x,true;
		}
	return false;
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,[](auto x,auto y) { return x.y>y.y; });
	for(int i=1; i<=n; ++i)
		if(insert(a[i].x))
			ans+=a[i].y;
	printf("%d",ans);
	return 0;
}