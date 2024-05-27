#include<cstdio>
#include<set>
#include<utility>
using namespace std;
const int N = 1e6;
int n,k,a[N + 2];
long long ans;
set<pair<int,int>> st[2];
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i)	
		scanf("%1d",&a[i]);
	for(int i=1; i<=n; ++i) {
		int x;
		scanf("%1d",&x);
		if(x!=a[i]) {
			if(st[x].empty()) st[!x].emplace(i%k,i);
			else {
				auto it=st[x].lower_bound(make_pair(i%k,0));
				if(it==st[x].end()) it=st[x].begin();
				ans+=(i-it->second-1)/k+1;
				st[x].erase(it);
			}
		}
	}
	printf("%lld",ans);
	return 0;
}