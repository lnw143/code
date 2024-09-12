#include <cstdio>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
const int M = 1e5, P = 1e9 + 7, inv2 = (P+1)/2, inv6 = (P+1)/6;
ll n;
int m;
int prime[M + 2],pcnt;
namespace linear_sieve {
	bool bz[M * 2 + 2];
	void solve() {
		prime[0]=1;
		for(int i=2; ; ++i) {
			if(!bz[i]) {
				prime[++pcnt]=i;
				if(i>=m) break;
			}
			for(int j=1; j<=pcnt&&i*prime[j]<=m; ++j) {
				bz[i*prime[j]]=true;
				if(prime[j]%i==0) break;
			}
		}
	}
}
namespace min_25 {
	namespace FirstStep {
		int pos(ll x) {
			return x<=m?x:n/x+m;
		}
		vector<ll> num;
		struct FirstStep {
			ll g[M * 2 + 2];
			ll G(ll n) {
				return g[pos(n)];
			}
			void solve(ll (*func)(ll),ll (*sum)(ll)) {
				int tot=0;
				for(auto i : num) {
					g[pos(i)]=sum(i);
					++tot;
				}
				for(int i=1; i<=pcnt; ++i) {
					for(auto j : num) {
						if(prime[i]>j/prime[i]) break;
						g[pos(j)]=(g[pos(j)]-func(prime[i])*(g[pos(j/prime[i])]-g[prime[i-1]])%P)%P;
					}
				}
			}
		} s1,s2;
		void solve() {
			for(ll i=1; i<=n; i=n/(n/i)+1) num.push_back(n/i);
			s1.solve(
				[](ll x) { return x%P; },
				[](ll x) {
					x%=P;
					return x*(x+1)%P*inv2%P;
				});
			s2.solve(
			[](ll x) {
				x%=P;
				return x*x%P;
			},
			[](ll x) {
				x%=P;
				return x*(x+1)%P*(2*x+1)%P*inv6%P;
			});
		}
		ll G(ll n) {
			return (s2.G(n)-s1.G(n)+P)%P;
		}
	}
	using FirstStep::G;
	ll S(ll n,int j,ll (*func)(ll)) {
		if(n<=prime[j]) return 0;
		ll res=(G(n)-G(prime[j])+P)%P;
		for(int k=j+1; k<=pcnt&&prime[k]<=n/prime[k]; ++k) {
			for(ll s=prime[k]; s<=n; s*=prime[k])
				(res+=func(s)*(S(n/s,k,func)+(s!=prime[k]))%P)%=P;
		}
		return res;
	}
}
int main() {
	scanf("%lld",&n);
	for(; (ll)m*m<n; ++m);
	linear_sieve::solve();
	min_25::FirstStep::solve();
	printf("%lld",(min_25::S(n,0,
	[](ll x) {
		x%=P;
		return x*(x-1)%P;
	})+P+1)%P);
	return 0;
}