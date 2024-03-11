#include<cstdio>
#include<algorithm>
using namespace std;
const int N(3e5);
int n,p[N + 2],q[N + 2],a[N + 2],ans[N + 2];
int findl(int x) {
	for(int i=x-2; i>=1; --i)
		if(a[i]==a[i+1]) return i;
	return 0;
}
int findr(int x) {
	for(int i=x+2; i<=n; ++i)
		if(a[i]==a[i-1]) return i;
	return n+1;
}
int len(int l,int r) {
	return r-l+1+((l^r)&1);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&p[i]),q[p[i]]=i,a[i]=1;
	for(int i=1; i<=n; ++i) {
		a[q[i]]=-1;
		if(q[i]==1) {
			int s=0;
			ans[q[i]]=-1;
			for(int j=2; j<=n; ++j) {
				s+=a[j];
				if(j%2==1&&s) {
					ans[q[i]]=j;
					break;
				}
			}
			continue;
		} else if(q[i]==n) {
			int s=0;
			ans[q[i]]=-1;
			for(int j=n-1; j>=1; --j) {
				s+=a[j];
				if((n-j)%2==0&&s) {
					ans[q[i]]=n-j+1;
					break;
				}
			}
			continue;
		} else {
			if(1<q[i]&&q[i]<n&&a[q[i]-1]==a[q[i]+1]) {
				ans[q[i]]=3;
				continue;
			}
			ans[q[i]]=n+1;
			int l=findl(q[i]),r=findr(q[i]);
			if(1<=l) ans[q[i]]=min(ans[q[i]],len(l,q[i]));
			if(r<=n) ans[q[i]]=min(ans[q[i]],len(q[i],r));
		}
	}
	for(int i=1; i<=n; ++i)
		printf("%d ",ans[i]<=n?ans[i]:-1);
	return 0;
}