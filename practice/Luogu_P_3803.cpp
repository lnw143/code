#include<cstdio>
#define _USE_MATH_DEFINES
#include<cmath>
#include<algorithm>
using namespace std;
using db = double;
const int N = 1 << 21;
const db PI = M_PI;
struct complex {
	db x,y;
	complex(db x_=0,db y_=0):x(x_),y(y_) {}
} a[N + 2],b[N + 2];
complex operator+(const complex &x,const complex &y) { return {x.x+y.x,x.y+y.y}; }
complex operator-(const complex &x,const complex &y) { return {x.x-y.x,x.y-y.y}; }
complex operator*(const complex &x,const complex &y) { return {x.x*y.x-x.y*y.y,x.x*y.y+x.y*y.x}; }
int n,m,r[N + 2];
void fft(complex *a,int n,int e) {
	for(int i=0; i<n; ++i)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	for(int i=1; i<n; i<<=1) {
		const complex wn(cos(PI/i),e*sin(PI/i));
		const int len=i<<1;
		for(int j=0; j<n; j+=len) {
			complex w(1,0);
			for(int k=0; k<i; ++k,w=w*wn) {		
				complex x=a[j+k],y=w*a[j+k+i];
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
		a[i].x=x;
	}
	for(int i=0; i<=m; ++i) {
		int x=0;
		scanf("%d",&x);
		b[i].x=x;
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
		printf("%d ",int(a[i].x/k+0.5));
	return 0;
}