#include<cstdio>
using namespace std;
using ll = long long;
const int N(18);
ll l,r,a[N + 2],f[N + 2][N + 2][2];
void split() {
	
}
ll dp(ll n) {
	
}
int main() {	
	scanf("%lld%lld",&l,&r);
	printf("%lld",dp(r)-dp(l-1));
	return 0;
}