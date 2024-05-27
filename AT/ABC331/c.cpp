#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2e5 + 2;
int n,i;
long long ans[N],sum,maxn,maxv;
struct Node {
	int x,v;
	bool operator<(const Node t) const {
		return x>t.x;
	}
} a[N];
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i].x),a[i].v=i;
	stable_sort(a+1,a+n+1);
	for(i=1; i<=n; ++i) {
		if(a[i].x!=maxn) {
			sum+=maxn*maxv;
			maxn=a[i].x;
			maxv=1;
		} else
			++maxv;
		ans[a[i].v]=sum;
	}
	for(i=1; i<=n; ++i)
		printf("%lld ",ans[i]);
	return 0;
}