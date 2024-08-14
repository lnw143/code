#include <cstdio>
#include <utility>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
const int N = 1e5, M = 2e5;
int n,m,k,r[M + 2];
ll ans;
ll a[N + 2],w[M + 2];
vector<ll> tic[N + 2];
int solve(ll c) {
	heap<pair<ll,int>> hp;
	int sum=0;
	ans=0;
	for(int i=1; i<=n; ++i) {
		hp.emplace(a[i]+c,1);
		for(auto w : tic[i])
			if(-w+hp.top().first<=0) {
				ans+=-w+hp.top().first;
				sum+=hp.top().second;
				hp.pop();
				hp.emplace(w,0);
			}
	}
	while(hp.top().first<=0) {
		ans+=hp.top().first;
		sum+=hp.top().second;
		hp.pop();
	}
	return sum;
}
int main() {
	freopen("cof.in","r",stdin);
	freopen("cof.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%lld",&a[i]);
	for(int i=1; i<=m; ++i) scanf("%d%lld",&r[i],&w[i]),tic[r[i]].push_back(w[i]);
	scanf("%d",&k);
	ll l=-1e9,r=1e9;
	while(l<=r) {
		ll mid=(l+r)/2;
		if(solve(mid)>=k) l=mid+1;
		else r=mid-1;
	}
	solve(l-1);
	printf("%lld\n",ans-k*(l-1));
	return 0;
}