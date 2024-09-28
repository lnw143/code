#include <cstdio>
#include <algorithm>
#include <functional>
#include <set>
#include <vector>
#include <utility>
using namespace std;
const int N = 1e5;
int n;
int main() {
	scanf("%d",&n);
	vector<pair<int,int>> a(n);
	for(auto &[i,j] : a)
		scanf("%d%d",&j,&i),j=min(j,n);
	set<int> st;
	for(int i=1; i<=n; ++i) st.insert(i);
	sort(a.begin(),a.end(),greater<pair<int,int>>());
	long long ans=0;
	for(auto [i,j] : a) {
		if(st.empty()||*st.begin()>j) continue;
		st.erase(--st.upper_bound(j));
		ans+=i;
	}
	printf("%lld",ans);
	return 0;
}