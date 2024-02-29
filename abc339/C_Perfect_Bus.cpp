#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 2e5;
int n,x,i;
ll sum,minn;
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%d",&x);
		sum+=x;
		minn=min(minn,sum);
	}
	printf("%lld",sum-minn);
	return 0;
}