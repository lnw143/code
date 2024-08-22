#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
const int N = 50;
int n,k,a[N + 2],s[N + 2],cnt[N + 2];
vector<pair<int,int>> ans;
void sub2() {
	int maxh=0;
	for(int i=n%k; i<k; ++i)
		maxh=max(maxh,a[i]);
	for(int i=n%k; i<k; ++i)
		for(int &j=a[i]; j+k<=maxh; j+=k)
			ans.emplace_back(1,i);
	for(int i=0; i<n%k; ++i)
		for(int &j=a[i]; j<maxh; j+=k)
			ans.emplace_back(1,i);
	for(int i=k; i<n; ++i)
		for(int j=1; j<=maxh/k; ++j)
			ans.emplace_back(1,i);
	for(int j=1; j<=a[0]-maxh; ++j)
		for(int i=n%k; i<n; i+=k)
			ans.emplace_back(2,i);
}
void solve() {
	for(int i=1; i<n; ++i)
		for(; a[i]<a[i-1]; a[i]+=k)
			ans.emplace_back(1,i);
	for(int i=k; i<n; ++i)
		for(int j=a[i-1]; j<a[i]; ++j) {
			for(int p=i-k; p>=0; p-=k)
				ans.emplace_back(2,p);
			++cnt[i%k];
		}
	for(int i=1; i<n; ++i) a[i]-=a[0];
	a[0]=0;
	int h=a[n-1]-cnt[0];
	for(int i=1; i<k; ++i) {
		for(int &j=a[i-1]; j<h; j+=k)
			ans.emplace_back(1,i-1);
		for(int p=0; p<i; ++p)
			a[p]-=cnt[i];
		h-=cnt[i];
	}
	int minh=*min_element(a,a+n);
	for(int i=0; i<n; ++i) a[i]-=minh;
	for(int i=k-1; i<n; ++i)
		a[i]=0;
}
int main() {
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=0; i<n; ++i) scanf("%d",&a[i]),(s[i%k]+=a[i])%=k;
	for(int i=0; i<n%k; ++i)
		if(s[i]!=s[0])
			return printf("-1\n"),0;
	for(int i=n%k; i<k; ++i)
		if(s[i]!=s[k-1])
			return printf("-1\n"),0;
	solve();
	sub2();
	printf("%d\n",ans.size());
	for(auto [i,j] : ans)
		printf("%d %d\n",i,j+1);
	return 0;
}