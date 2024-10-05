#include <cstdio>
using namespace std;
using ll = long long;
inline char gc() {
	static char buf[1<<20],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<20,stdin),l==r)?-1:*l++;
}
inline int read() {
	int x=0;
	bool f=false;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc()) if(c=='-') f=true;
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c&15);
	return f?-x:x;
}
const int N = 1e6, P = 1e9 + 7;
int n,m,q;
int a[N + 2],b[N + 2];

ll qpow(ll a,ll n) {
	ll x=1;
	for(; n; n>>=1,a=a*a%P) if(n&1) x=x*a%P;
	return x;
}
int main() {
	freopen("you.in","r",stdin);
	freopen("you.out","w",stdout);
	n=read(),m=read(),q=read();
	for(int i=0; i<=n+1; ++i) a[i]=1;
	for(int i=0; i<=m+1; ++i) b[i]=1;
	for(int i=1; i<=q; ++i) {
		int op=read(),l=read(),r=read(),v=read();
		if(op==1) {
			a[l]=ll(a[l])*v%P;
			a[r+1]=ll(a[r+1])*qpow(v,P-2)%P;
		} else {
			b[l]=ll(b[l])*v%P;
			b[r+1]=ll(b[r+1])*qpow(v,P-2)%P;
		}
	}
	ll cur=0,tot=0,ans=0;
	for(int i=1; i<=m; ++i) {
		b[i]=ll(b[i])*b[i-1]%P;
		tot=(tot+b[i])%P;
		cur=(cur+i*ll(b[i]))%P;
	}
	for(int i=1; i<=n; ++i,cur=(cur+m*tot%P)%P) {
		a[i]=ll(a[i])*a[i-1]%P;
		ans=(ans+a[i]*cur%P)%P;
	}
	printf("%lld",ans);
	return 0;
}