#include<cstdio>
using namespace std;
using ll = long long;
int T;
ll n;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%lld",&n);
		printf("%lld\n",n&1?n:(n>>1)^n);
	}
	return 0;
}