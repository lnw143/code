#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
const int N = 20;
int n,p;
struct fastmod {
	typedef unsigned long long u64;
	typedef __uint128_t u128;
	int m;
	u64 b;
	fastmod(int m) : m(m), b(((u128)1 << 64) / m) {}
	int reduce(u64 a) {
 		u64 q = ((u128)a * b) >> 64;
		int r = a - q * m;
		return r < m ? r : r - m;
		}
} z(2);
ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=z.reduce(a*a)) if(n&1) x=z.reduce(x*a);
	return x;
}
int dfs(vector<int> v) {
	if(count(v.begin(),v.end(),0)==0) return 0;
	int sum=0;
	for(int i=0; i<n; ++i) {
		vector<int> u=v;
		for(int j=0; j<n; ++j)
			if(v[j])
				u[(j+1)%n]=u[(j+n-1)%n]=1;
		u[i]=1;
		sum=z.reduce(sum+dfs(u)+1);
	}
	return z.reduce(sum*qpow(n,p-2));
} 
int main() {
	freopen("sleep.in","r",stdin);
	freopen("sleep.out","w",stdout);
	scanf("%d%d",&n,&p);
	z=fastmod(p);
	printf("%d",dfs(vector<int>(n,0)));
	return 0;
}