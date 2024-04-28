#include<cstdio>
#include<cstring>
#define fd(i,l,r) for(int i(l); i<(r); ++i)
#define USE_FWT
using ll = long long;
using namespace std;
constexpr int N = 17, M = 1 << N, P = 998244353, Pi2 = (P + 1)/2;
int n,m;
ll a[M],b[M];
void fmtOr(ll *a,int n,int type) {
	fd(i,0,n) fd(j,0,1<<n) if(j&(1<<i)) (a[j]+=type*a[j^(1<<i)])%=P;
}
void fmtAnd(ll *a,int n,int type) {
	fd(i,0,n) fd(j,0,1<<n) if(!(j&(1<<i))) (a[j]+=type*a[j^(1<<i)])%=P;
}
void fwtOr(ll *a,int n,int type) {
	for(int i=1; i<(1<<n); i<<=1)
		for(int j=0; j<(1<<n); j+=(i<<1))
			for(int k=0; k<i; ++k)
				(a[j+k+i]+=type*a[j+k])%=P;
}
void fwtAnd(ll *a,int n,int type) {
	for(int i=1; i<(1<<n); i<<=1)
		for(int j=0; j<(1<<n); j+=(i<<1))
			for(int k=0; k<i; ++k)
				(a[j+k]+=type*a[j+k+i])%=P;
}
void fwtXor(ll *a,int n,int type) {
	for(int i=1; i<(1<<n); i<<=1)
		for(int j=0; j<(1<<n); j+=(i<<1))
			for(int k=0; k<i; ++k) {
				ll u=a[j+k],v=a[j+k+i];
				a[j+k]=(u+v)%P;
				a[j+k+i]=(u-v)%P;
				if(type==-1) {
					(a[j+k]*=Pi2)%=P;
					(a[j+k+i]*=Pi2)%=P;
				}
			}
}
template <typename F> void solve(ll *a,ll *b,int n,F trans) {
	static ll a_[M],b_[M];
	memcpy(a_,a,sizeof(a_));
	memcpy(b_,b,sizeof(b_));
	trans(a_,n,1);
	trans(b_,n,1);
	for(int i=0; i<(1<<n); ++i) a_[i]=(ll)a_[i]*b_[i]%P;
	trans(a_,n,-1);
	for(int i=0; i<(1<<n); ++i) printf("%lld ",(a_[i]%P+P)%P);
	putchar('\n');
}
int main() {
	scanf("%d",&n);
	m=1<<n;
	fd(i,0,m) scanf("%lld",&a[i]);
	fd(i,0,m) scanf("%lld",&b[i]);
#if defined(USE_FWT)
	solve(a,b,n,fwtOr);
	solve(a,b,n,fwtAnd);
#else
	solve(a,b,n,fmtOr);
	solve(a,b,n,fmtAnd);
#endif
	solve(a,b,n,fwtXor);
	return 0;
}