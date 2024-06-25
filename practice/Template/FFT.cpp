#define _USE_MATH_DEFINES
#include <cstdio>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
const int N = 1 << 21;
using comp = complex<double>;
int n,m,r[N + 2];
comp a[N + 2],b[N + 2];
void FFT(comp *a,const int n,const int t) {
	for(int i=0; i<n; ++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(int i=1; i<n; i<<=1) {
		const comp omg_n{cos(M_PI/i),t*sin(M_PI/i)};
		for(int j=0; j<n; j+=(i<<1)) {
			comp omg{1,0};
			for(int k=0; k<i; ++k,omg*=omg_n) {
				const comp u=a[j+k],v=omg*a[j+k+i];
				a[j+k]=u+v;
				a[j+k+i]=u-v;
			}
		}
	}
/*
	if(n==1) return ;
	const int m=n>>1;
	comp a0[m],a1[m];
	for(int i=0; i<n; i+=2)
		a0[i>>1]=a[i],
		a1[i>>1]=a[i+1];
	FFT(a0,m,t);
	FFT(a1,m,t);
	const comp omg_n{cos(2*M_PI/n),t*sin(2*M_PI/n)};
	comp omg={1,0};
	for(int i=0; i<m; ++i,omg*=omg_n) {
		const comp u=a0[i],v=omg*a1[i];
		a[i]=u+v;
		a[i+m]=u-v;
	}
*/
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0; i<=n; ++i) {
		int x;
		scanf("%d",&x);
		a[i]=x;
	}
	for(int i=0; i<=m; ++i) {
		int x;
		scanf("%d",&x);
		b[i]=x;
	}
	int k=1,s=0;
	while(k<=n+m) k<<=1,++s;
	for(int i=0; i<k; ++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(s-1));
	FFT(a,k,1);
	FFT(b,k,1);
	for(int i=0; i<k; ++i)
		a[i]*=b[i];
	FFT(a,k,-1);
	for(int i=0; i<=n+m; ++i)
		printf("%.0lf ",floor(a[i].real()/k+0.5));
	return 0;
}