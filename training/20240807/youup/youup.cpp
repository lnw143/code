#include <cstdio>
#include <vector>
using namespace std;
using ll = long long;
const int N = 3e5, P = 998244353;
int tid,n,m;
vector<int> e[N + 2];
ll fac[N + 2],inv[N + 2],ifac[N + 2];
ll C(int n,int m) {
	return fac[n]*ifac[n-m]%P*ifac[m]%P;
}
int main() {
	freopen("youup.in","r",stdin);
	freopen("youup.out","w",stdout);
	scanf("%d%d%d",&tid,&n,&m);
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
	for(int i=2; i<=n; ++i) {
		fac[i]=fac[i-1]*i%P;
		inv[i]=(P-P/i)*inv[P%i]%P;
		ifac[i]=ifac[i-1]*inv[i]%P;
	}
	for(int i=1; i<=n; ++i) {
		if(i==1) printf("%d ",n);
		else if(m==0) printf("0 ");
		else if(i==2) printf("%d ",m==1?n-1:C(n,2));
		else if(m==1) printf("0 ");
		else printf("%lld ",C(n,i));
	}
	return 0;
}