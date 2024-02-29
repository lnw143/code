#include<cstdio>
#include<algorithm>
using namespace std;
const int N(1e5);
int T,n,m,a[N + 2];
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; ++i)
			scanf("%d%*d",&a[i]);
		stable_sort(a+1,a+n+1);
		int t=0,s=0;
		for(int i=1; i<=n&&a[i]<=m; ++i) {
			++t,s+=a[i];
			m-=a[i];
		}
		printf("%d %d\n",t,s);
	}
	return 0;
}