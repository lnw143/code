#include <cstdio>
using namespace std;
using ll = long long;
const int N = 5e4;
int n,k,a[N + 2];
namespace sum {
	ll f[N + 2],g[N + 2];
	void init() {
		for(int i=1; i<=n; ++i) f[i]=f[i-1]+a[i];
		for(ll i=1; i<=n; ++i) g[i]=g[i-1]+a[i]*i;
	}
	ll cost(int l,int r) {
		if(l==0) return r==n+1?1e18:r*f[r]-g[r];
		if(r>n) return g[n]-g[l]-l*(f[n]-f[l]);
		int mid=(l+r)/2;
		return g[mid]-g[l]-l*(f[mid]-f[l])-(g[r]-g[mid])+r*(f[r]-f[mid]);
	}
}
namespace dp {
	ll f[N + 2];
	int g[N + 2],lt[N + 2],rt[N + 2],q[N + 2];
	ll c(int l,int r) {
		return f[l]+sum::cost(l,r);
	}
	void solve(const ll L) {
		f[0]=g[0]=0;
		int h=1,t=1;
		q[1]=0;
		lt[0]=1,rt[0]=n+1;
		for(int i=1; i<=n+1; ++i) {
			while(h<=t&&rt[q[h]]<i) ++h;
			f[i]=c(q[h],i)+L;
			g[i]=g[q[h]]+1;
			while(h<=t&&c(i,lt[q[t]])<c(q[t],lt[q[t]])) --t;
			if(h>t) {
				lt[i]=i+1;
				rt[i]=n+1;
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
				rt[i]=n+1;
				q[++t]=i;
			} else if(rt[q[t]]<=n) {
				lt[i]=rt[q[t]]+1;
				rt[i]=n+1;
				q[++t]=i;
			}
		}
	}
}
namespace wqs {
	ll solve() {
		ll l=0,r=1e12;
		while(l<=r) {
			ll mid=(l+r)/2;
			dp::solve(mid);
			if(dp::g[n+1]<=k+1) r=mid-1;
			else l=mid+1;
		}
		dp::solve(r+1);
		return dp::f[n+1]-(k+1)*(r+1);
	}
}
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	sum::init();
	printf("%lld",wqs::solve());
	return 0;
}