#include <cstdio>
#include <bitset>
#include <cmath>
using namespace std;
const int N = 5e3;
int T,n,h[N + 2];
bitset<N + 2> a[N + 2];
bool able(int x,int l,int r) {
	return l>=x-1&&r<=x+1;
}
int main() {
	freopen("counting.in","r",stdin);
	freopen("counting.out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i)
			scanf("%d",&h[i]);
		for(int i=1; i<=n; ++i)
			for(int j=i+1,l=h[j],r=h[j]; j<=n; ++j) {
				a[i][j]=(abs(h[i]-h[j])==1&&(able(h[i],l,r)||able(h[j],l,r)));
				l=min(l,h[j]),r=max(r,h[j]);
			}
		for(int i=1; i<=n; ++i,putchar('\n'))
			for(int j=1; j<i; ++j)
				printf("%d ",(int)a[j][i]);
		for(int i=1; i<=n; ++i) a[i].reset();
	}
	return 0;
}