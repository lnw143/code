#include<cstdio>
#define pw2(x) (1<<(x))
using namespace std;
const int N = 1e4 + 2, K = 10 + 2, P = 998244353;
int n,k,i,j,l,x,a[N][K],b[N][K],f[N][1<<K],p,q;
int cnt(int x) {
	bool f=false;
	while(x) {
		f=!f;
		x&=x-1;
	}
	return f;
}
int read() {
	char ch=getchar();
	while(ch!='0'&&ch!='1') ch=getchar();
	return ch-'0';
}
int main() {
	freopen("adore.in","r",stdin);
	freopen("adore.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(l=0; l<k; ++l) {
		x=read();
		a[2][0]|=x<<l;
		b[2][l]=x;
	}
	for(i=3; i<n; ++i)
		for(j=0; j<k; ++j)
			for(l=0; l<k; ++l) {
				x=read();
				a[i][j]|=x<<l;
				b[i][l]|=x<<j;
			}
	for(l=0; l<k; ++l) {
		x=read();
		a[n][0]|=x<<l;
		b[n][l]=x;
	}
	f[2][a[2][0]]=1;
	for(i=2; i<n; ++i)
		for(j=0; j<pw2(k); ++j)
			if(f[i][j]) {
				p=q=0;
				for(l=0; l<k; ++l) {
					p|=cnt(a[i+1][l]&j)<<l;
					q|=cnt(b[i+1][l]&j)<<l;
				}
				(f[i+1][p]+=f[i][j])%=P;
				if(i<n-1) (f[i+1][q]+=f[i][j])%=P;
			}
	printf("%d",f[n][0]);
	return 0;
}