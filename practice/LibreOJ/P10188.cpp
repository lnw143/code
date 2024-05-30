#include <cstdio>
using namespace std;
using ll = long long;
const int N = 5e4;
int n,k,a[N + 2];
int lt[N + 2],rt[N + 2];
int h,t,q[N + 2];
ll s[N + 2],f[N + 2];
ll cost(int l,int r) {
	ll x=r-l-1+s[r]-s[l]-k;
	return f[l]+x*x;
}
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	h=1,t=0;
	q[++t]=0;
	lt[0]=1,rt[0]=n;
	for(int i=1; i<=n; ++i) {
		while(h<=t&&rt[q[h]]<i) ++h;
		f[i]=cost(q[h],i);
		while(h<=t&&cost(i,lt[q[t]])<cost(q[t],lt[q[t]])) --t;
		if(h>t) {
			lt[i]=i+1;
			rt[i]=n;
			q[++t]=i;
		} else if(cost(i,rt[q[t]])<cost(q[t],rt[q[t]])) {
			int l=lt[q[t]],r=rt[q[t]],mid;
			while(l<=r) {
				mid=(l+r)/2;
				if(cost(i,mid)<cost(q[t],mid)) r=mid-1;
				else l=mid+1;
			}
			rt[q[t]]=r;
			lt[i]=r+1;
			rt[i]=n;
			q[++t]=i;
		} else {
			if(rt[q[t]]<n) {
				lt[i]=rt[q[t]]+1;
				rt[i]=n;
				q[++t]=i;
			}
		}
	}
	printf("%lld",f[n]);
	return 0;
}