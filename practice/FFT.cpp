#include <cstdio>
#include <complex>
#include <cmath>
using namespace std;
const int N = 1 << 21;
using comp = complex<double>;
int n,m,k;
comp a[N + 2],b[N + 2];
void FFT(comp *a,const int n,const int t) {
	if(n==1) return ;
	const int m=n>>1;
	comp a0[m],a1[m];
	for(int i=0; i<n; i+=2)
		a0[i>>1]=a[i],
		a1[i>>1]=a[i+1];
	
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0; i<=n; ++i) {
		int x;
		scanf("%d",&x);
		a[i]=x;
	}
	for(int i=0; i<=n; ++i) {
		int x;
		scanf("%d",&x);
		b[i]=x;
	}
	k=1;
	while(k<=n+m) k<<=1;

	return 0;
}