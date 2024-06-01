#include <cstdio>
using namespace std;
const int N = 1e5;
using ll = long long;
int n,m,a[N + 2];
ll s[N + 2];
namespace slope_dp {
	int g[N + 2];
	ll f[N + 2];
	struct line {
		ll k,b,id;
		ll val(ll x) {
			return k*x+b;
		}
		line()=default;
		line(int i):id(i) {
			k=-2*s[i];
			b=f[i]+s[i]*s[i]-2*s[i];
		}
	} q[N + 2];
	void solve(const ll S) {
		f[0]=g[0]=0;
		int h=1,t=1;
		q[1]=0;
		for(int i=1; i<=n; ++i) {
			while(h<t&&q[h].val(s[i])>q[h+1].val(s[i])) ++h;
			f[i]=q[h].val(s[i])+s[i]*s[i]+2*s[i]+S+1;
			g[i]=g[q[h].id]+1;
			line p=i;
			while(h<t&&(q[t].b-p.b)*(q[t].k-q[t-1].k)<(q[t-1].b-q[t].b)*(p.k-q[t].k)) --t;
			q[++t]=p;
		}
	}
}
namespace wqs {
	bool check(ll x) {
		slope_dp::solve(x);
		return slope_dp::g[n]<=m;
	}
	ll solve() {
		ll l=0,r=1e16,mid;
		while(l<=r) {
			mid=(l+r)/2;
			if(check(mid)) r=mid-1;
			else l=mid+1;
		}
		check(r+1);
		return slope_dp::f[n]-m*(r+1);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	printf("%lld",wqs::solve());
	return 0;
}