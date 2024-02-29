#include<cstdio>
#include<algorithm>
#include<functional>
using namespace std;
const int N(2e5);
int n,q,a[N + 2];
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(int i=1; i<=n; ++i) {
		static int x;
		scanf("%d",&x);
		a[i]-=x;
	}
	stable_sort(a+1,a+n+1,[](int x,int y) {
		return x>y;
	});
	for(int i=1; i<=q; ++i) {
		static int v,s;
		scanf("%d%d",&v,&s);
		printf(lower_bound(a+1,a+n+1,s,greater<int>())-a>v?"YES\n":"NO\n");
	}
	return 0;
}