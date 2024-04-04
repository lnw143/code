#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e5;
int T,n,a[N + 2];
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		int m=(n+1)/2,sum=0;
		for(int i=m; i<=n; ++i)
			if(a[m]==a[i])
				++sum;
		printf("%d\n",sum);
	}
	return 0;
}