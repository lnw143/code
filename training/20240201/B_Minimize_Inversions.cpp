#include<cstdio>
#include<algorithm>
#include<utility>
using namespace std;
using pii = pair<int,int>;
const int N = 2e5;
int T,n,i;
pii a[N + 2];
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
			scanf("%d",&a[i].first);
		for(i=1; i<=n; ++i)
			scanf("%d",&a[i].second);
		stable_sort(a+1,a+n+1);
		for(i=1; i<=n; ++i)
			printf("%d ",a[i].first);
		putchar('\n');
		for(i=1; i<=n; ++i)
			printf("%d ",a[i].second);
		putchar('\n');
	}
	return 0;
}