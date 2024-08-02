#include <cstdio>
using namespace std;
FILE* fin = freopen("eval.in","r",stdin);
FILE* fout = freopen("eval.out","w",stdout);
inline char gc() {
	static char buf[1<<16],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
inline int read() {
	char c=gc();
	int x=0;
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<3)+(x<<1)+(c^'0');
	return x;
}
const int N = 1e7;
const int T = read(), P = read();
int f[N + 2],fac[N * 2 + 2],inv[N + 2],ifac[N + 2];
inline int C(int n,int m) {
	return 1ll*fac[n]*ifac[n-m]%P*ifac[m]%P;
}
int main() {
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
	for(int i=2; i<=N+1; ++i) {
		fac[i]=1ll*fac[i-1]*i%P;
		inv[i]=1ll*(P-P/i)*inv[P%i]%P;
		ifac[i]=1ll*ifac[i-1]*inv[i]%P;
	}
	for(int i=N+2; i<=N*2+1; ++i)
		fac[i]=1ll*fac[i-1]*i%P;
	f[0]=1;
	for(int i=1; i<=N; ++i)
		f[i]=(2ll*f[i-1]%P+C(2*i+1,i))%P;
	for(int i=1; i<=T; ++i)
		printf("%d\n",f[read()]);
	return 0;
}