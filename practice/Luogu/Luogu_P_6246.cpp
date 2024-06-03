#include <cstdio>
using namespace std;
using ll = long long;
const int N = 5e5;
int n,m,a[N + 2];
ll s[N + 2];
namespace dp {
	ll f[N + 2];
	int g[N + 2],lt[N + 2],rt[N + 2],q[N + 2];
	ll cost(int l,int r) {
		int mid=(l+r)/2;
		return ll(mid-l+1)*a[mid]-(s[mid]-s[l-1])+(s[r]-s[mid])-ll(r-mid)*a[mid];
	}
	ll c(int l,int r) {
		return f[l]+cost(l+1,r);
	}
	void dp(const ll S) {
		f[0]=g[0]=0;
		int h=1,t=1;
		q[1]=0;
		lt[0]=1,rt[0]=n;
		for(int i=1; i<=n; ++i) {
			while(h<=t&&rt[q[h]]<i) ++h;
			f[i]=c(q[h],i)+S;
			g[i]=g[q[h]]+1;
			while(h<=t&&c(i,lt[q[t]])<c(q[t],lt[q[t]])) --t;
			if(h>t) {
				lt[i]=i+1;
				rt[i]=n;
				q[++t]=i;
			} else if(c(i,rt[q[t]])<c(q[t],rt[q[t]])) {
				int l=lt[q[t]],r=rt[q[t]];
				while(l<=r) {
					int mid=(l+r)/2;
					if(c(i,mid)<c(q[t],mid)) r=mid-1;
					else l=mid+1;
				}
				rt[q[t]]=r;
				lt[i]=r+1;
				rt[i]=n;
				q[++t]=i;
			} else if(rt[q[t]]<n) {
				lt[i]=rt[q[t]]+1;
				rt[i]=n;
				q[++t]=i;
			}
		}
	}
}
namespace wqs {
	ll solve() {
		ll l=0,r=1e18;
		while(l<=r) {
			ll mid=(l+r)/2;
			dp::dp(mid);
			if(dp::g[n]<=m) r=mid-1;
			else l=mid+1;;
		}
		dp::dp(r+1);
		return dp::f[n]-(r+1)*m;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		s[i]=s[i-1]+a[i];
	}
	printf("%lld\n",wqs::solve());
	return 0;
}