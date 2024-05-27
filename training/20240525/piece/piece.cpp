#include <cstdio>
#include <map>
#include <cmath>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5, M = 10;
int n,k,a[N + 2],t[N + 2];
ll pow10[M + 2],ans;
vector<int> e[M + 2];
int main() {
	freopen("piece.in","r",stdin);
	freopen("piece.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) {
		t[i]=floor(log10(a[i]))+1;
		e[t[i]].push_back(i);
	}
	pow10[0]=1;
	for(int i=1; i<=M; ++i)
		pow10[i]=pow10[i-1]*10%k;
	for(int i=1; i<=M; ++i) {
		map<int,int> mp;
		for(auto u : e[i])
			++mp[(-a[u]%k+k)%k];
		for(int j=1; j<=n; ++j) {
			ans+=mp[a[j]*pow10[i]%k];
			if(t[j]==i&&(a[j]*pow10[i]%k+a[j])%k==0) --ans;
		}
	}
	printf("%lld",n*(n-1ll)-ans);
	return 0;
}