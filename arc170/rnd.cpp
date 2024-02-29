#include<cstdio>
#include<algorithm>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
const int N = 2e5, M = 100;
int T,n,i,a[N + 2],b[N + 2];
bool ck(int a,int b,int c) {
	return a<b+c&&b<a+c&&c<a+b;
}
bool fd(int y,int z) {
	int x=a[z],u=x<y?y-x:x-y,v=x+y,l=1,r=n,md;
	while(l<=r) {
		md=(l+r)/2;
		if(a[md]<=u) l=md+1;
		else r=md-1;
	}
	if(r<n&&r+1!=z&&a[r+1]<v) return true;
	l=1,r=n;
	while(l<=r) {
		md=(l+r)/2;
		if(v<=a[md]) r=md-1;
		else l=md+1;
	}
	return l>1&&l-1!=z&&a[l-1]>u;
}
int main() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		uniform_int_distribution<int> d(1,n);
		for(i=1; i<=n; ++i)
			scanf("%d",&a[i]);
		for(i=1; i<=n; ++i)
			scanf("%d",&b[i]);
		stable_sort(a+1,a+n+1);
		stable_sort(b+1,b+n+1);
		for(i=1; i<n; ++i) {
			if(fd(b[1],i)&&fd(b[n],i)) {
				bool f=true;
				for(int j=0; j<M; ++j) {
					int x=d(rnd);
					if(!fd(b[x],i)) {
						f=false;
						break;
					}
				}
				if(!f) continue;
				printf("Alice\n");
				break;
			}
		}
		if(i==n) printf("Bob\n");
	}
	return 0;
}