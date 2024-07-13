#include <cstdio>
#include <queue>
using namespace std;
using ll = long long;
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
const int N = 2e5;
const ll inf = 1ll << 60;
int T,n,a[N + 2],b[N + 2];
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
		for(int i=1; i<=n; ++i) scanf("%1d",&b[i]);
		heap<int> hp;
		ll ans=0;
		for(int i=n; i>=1; --i) {
			hp.push(a[i]);
			if(b[i]) ans+=hp.top(),hp.pop();
		}
		printf("%lld\n",ans);
	}
	return 0;
}