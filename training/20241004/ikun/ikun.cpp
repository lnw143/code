#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
const int N = 1e3, M = N * (N + 1);
int n,m,h[M + 2],p[M + 2];
bool bz[M + 2];
vector<int> num,a[N + 2];
int main() {
	freopen("ikun.in","r",stdin);
	freopen("ikun.out","w",stdout);
	scanf("%d",&n);
	m=n*(n+1);
	for(int i=1; i<=m; ++i)
		scanf("%d",&h[i]);
	num=vector<int>(h+1,h+m+1);
	sort(num.begin(),num.end());
	for(int i=1; i<=m; ++i)
		h[i]=lower_bound(num.begin(),num.end(),h[i])-num.begin()+1,
		p[h[i]]=i,
		a[(i-1)/(n+1)+1].push_back(h[i]);
	for(int i=1; i<=n; ++i)
		sort(a[i].begin(),a[i].end(),greater<int>());
	heap<pair<int,int>> hp;
	for(int i=1; i<=n; ++i)
		hp.emplace(a[i][a[i].size()-2],i);
	int cur=0;
	for(int i=1; i<=n; ) {
		auto [val,id]=hp.top();
		hp.pop();
		if(a[id].back()<cur) {
			a[id].pop_back();
			hp.emplace(a[id][a[id].size()-2],id);
			continue;
		}
		++i;
		bz[p[a[id].back()]]=true;
		bz[p[val]]=true;
		cur=val;
	}
	for(int i=1; i<=m; ++i)
		if(bz[i])
			printf("%d ",num[h[i]-1]);
	return 0;
}