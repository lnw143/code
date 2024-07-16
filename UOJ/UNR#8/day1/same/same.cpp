#include <cstdio>
#include <set>
using namespace std;
using ull = unsigned long long;
const int N = 3e5;
int n,q,a[N + 2];
ull solve(int l,int r) {
	int len=r-l+1;
	ull ans=0;
	for(int i=0; i<(1<<len); ++i) {
		set<int> s,t;
		for(int j=0; j<len; ++j)
			((i>>j)&1?s:t).insert(a[l+j]);
		if(s.size()==t.size()) ++ans;
	}
	return ans;
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	for(int i=1; i<=q; ++i) {
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%llu\n",solve(l,r));
	}
	return 0;
}