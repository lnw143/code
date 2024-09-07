#include <cstdio>
#include <set>
using namespace std;
const int N = 2e5;
using ll = long long;
int n,k,a[N + 2],b[N + 2],t[N + 2],cnt[N + 2];
ll ans;
namespace fenwick {
	int s[N + 2];
	void add(int x) {
		for(int i=x; i<=n; i+=i&-i) ++s[i];
	}
	int sum(int x) {
		int r=0;
		for(int i=x; i; i&=i-1) r+=s[i];
		return r;
	}
}
int main() {
	freopen("bsort.in","r",stdin);
	freopen("bsort.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) {
		b[i]=fenwick::sum(n-a[i]+1);
		fenwick::add(n-a[i]+1);
	}
	for(int i=1; i<=k; ++i)
		if(b[i]) {
			++ans;
			break;
		}
	for(int i=1; i<=k; ++i) b[i]=0;
	for(int i=1; i<=n; ++i) ans+=t[i]=(b[i]+k-2)/(k-1);
	for(int i=1; i<=n; ++i)
		if(i-(t[i]-1)*(k-1)<=k)
			++cnt[t[i]];
	for(int i=1; i<=n; ++i)
		if(cnt[i]>1)
			ans-=cnt[i]-1;
	printf("%lld",ans);
	return 0;
}