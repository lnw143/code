#include <cstdio>
using namespace std;
using ll = long long;
ll qpow(ll a,ll n,ll p) {
	ll x=1;
	for(; n; n>>=1,a=a*a%p) if(n&1) x=x*a%p;
	return x;
}
FILE *in=fopen("foe.in","r"),*out=fopen("foe.out","r");
int main() {
	int T;
	fscanf(in,"%d",&T);
	int nores=0;
	while(T--) {
		int a,n;
		fscanf(in,"%d%d",&a,&n);
		ll ans;
		fscanf(out,"%lld",&ans);
		if(ans==-1) ++nores;
		else if(ans%n!=qpow(a,ans,n))
			printf("Error (%d,%d,%lld)\n",a,n,ans);
	}
	printf("Finished, No Result: %d\n",nores);
	return nores;
}