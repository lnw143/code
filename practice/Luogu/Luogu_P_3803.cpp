#include<cstdio>
#define _USE_MATH_DEFINES
#include<cmath>
#include<complex>
#include<algorithm>
using namespace std;
using db = double;
const int N = 1 << 21;
const db PI = M_PI;
complex<db> a[N + 2],b[N + 2];
int n,m,r[N + 2];
void fft(complex<db> *a,int n,int e) {
	for(int i=0; i<n; ++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(int i=1; i<n; i<<=1) {
		const complex<db> wn(cos(PI/i),e*sin(PI/i));
		const int len=i<<1;
		for(int j=0; j<n; j+=len) {
			complex<db> w(1,0);
			for(int k=0; k<i; ++k,w=w*wn) {
				complex<db> x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;
				a[j+k+i]=x-y;
			}
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0; i<=n; ++i) {
		int x=0;
		scanf("%d",&x);
		a[i]=x;
	}
	for(int i=0; i<=m; ++i) {
		int x=0;
		scanf("%d",&x);
		b[i]=x;
	}
	int k=1,l=0;
	while(k<=n+m) k<<=1,++l;
	for(int i=1; i<k; ++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fft(a,k,1);
	fft(b,k,1);
	for(int i=0; i<k; ++i)
		a[i]=a[i]*b[i];
	fft(a,k,-1);
	for(int i=0; i<=n+m; ++i)
		printf("%d ",int(a[i].real()/k+0.5));
	return 0;
}