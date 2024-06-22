#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 18, M = 1 << N;
int n,m,ans;
struct val {
	int x,y;
	void upd(int u) {
		if(u>x) y=x,x=u;
		else if(u>y) y=u;
	}
} a[M + 2];
int main() {
	scanf("%d",&n);
	m=1<<n;
	for(int i=0; i<m; ++i)
		scanf("%d",&a[i].x),a[i].y=-1e9;
	for(int j=0; j<n; ++j)
		for(int i=0; i<m; ++i)
			if(i&(1<<j)) {
				a[i].upd(a[i^(1<<j)].x);
				a[i].upd(a[i^(1<<j)].y);
			}
	for(int i=1; i<m; ++i) {
		ans=max(ans,a[i].x+a[i].y);
		printf("%d\n",ans);
	}
	return 0;
}