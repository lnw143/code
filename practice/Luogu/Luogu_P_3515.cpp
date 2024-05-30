#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 5e5, inf = 1 << 30;
int n,a[N + 2];
double sq[N + 2],ans[N + 2],tmp[N + 2];
void solve(int l,int r,int x,int y) {
	if(l>r) return ;
	int mid=(l+r)/2,p=-1;
	ans[mid]=-inf;
	for(int i=x; i<=min(y,mid); ++i) {
		double cost=a[i]+sq[mid-i];
		if(cost>ans[mid]) {
			ans[mid]=cost;
			p=i;
		}
	}
	solve(l,mid-1,x,p);
	solve(mid+1,r,p,y);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	for(int i=0; i<n; ++i)
		sq[i]=sqrt(i);
	solve(1,n,1,n);
	for(int i=1; i<=n; ++i)
		tmp[i]=ans[i];
	reverse(a+1,a+n+1);
	solve(1,n,1,n);
	for(int i=1; i<=n; ++i)
		printf("%d\n",(int)ceil(max(tmp[i],ans[n-i+1]))-a[n-i+1]);
	return 0;
}