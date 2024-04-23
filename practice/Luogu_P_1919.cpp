#include<cstdio>
#define _USE_MATH_DEFINES
#include<cstring>
#include<cmath>
#include<complex>
using namespace std;
const int N = 1 << 21;
int n,m,ans[N + 2];
complex<double> a[N + 2],b[N + 2];
int read(complex<double> a[]) {
	static char s[N + 2];
	scanf("%s",s);
	int n=strlen(s);
	for(int i=0; i<n; ++i)
		a[n-i-1]=s[i]-'0';
	return n;
}
void fft(complex<double> *a,int n,int e) {
	if(n==1) return ;
	const int m = n>>1;
	complex<double> a0[m],a1[m];
	for(int i=0; i<m; ++i)
		a0[i]=a[i*2],a1[i]=a[i*2+1];
	fft(a0,m,e);
	fft(a1,m,e);
	const complex<double> wn(cos(2*M_PI/n),e*sin(2*M_PI/n));
	complex<double> w(1,0);
	for(int i=0; i<m; ++i,w*=wn) {
		const complex<double> u=a0[i],v=w*a1[i];
		a[i]=u+v;
		a[i+m]=u-v;
	}
}
int main() {
	n=read(a);
	m=read(b);
	int k=1;
	while(k<=n+m) k<<=1;
	fft(a,k,1);
	fft(b,k,1);
	for(int i=0; i<k; ++i)
		a[i]*=b[i];
	fft(a,k,-1);
	for(int i=0; i<k; ++i)
		ans[i]=a[i].real()/k+0.5;
	for(int i=0; i<k; ++i)
		ans[i+1]+=ans[i]/10,
		ans[i]%=10;
	while(k>0&&!ans[k]) --k;
	while(ans[k]) ++k;
	for(int i=k-1; i>=0; --i)
		printf("%d",ans[i]);
	return 0;
}