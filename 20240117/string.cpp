#include<cstdio>
using namespace std;
using llu = unsigned int;
const int N = 1 << 20, Base = 131, A = 26;
short T;
int i,j,n,f[N + 2],g[N + 2],t[A + 2];
bool c[A + 2];
char s[N + 2];
llu sum[N + 2],pw[N + 2];
long long ans;
char buf[1 << 20], *p1, *p2;
void read() {
	s[1]=getchar();
	while(s[1]<'a'||s[1]>'z') s[1]=getchar();
	n=1;
	do
		s[++n]=getchar();
	while(s[n]>='a'&&s[n]<='z');
	--n;
}
#define hash_str(l,r) (sum[r]-sum[(l)-1]*pw[(r)-(l)+1])
void ad(int x) {
	for(int i=x; i<=A+1; ++i)
		++t[i];
}
int qr(int x) {
	return t[x];
}
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%hd",&T);
	pw[0]=1;
	for(i=1; i<=N; ++i)
		pw[i]=pw[i-1]*Base;
	while(T--) {
		read();
		for(i=1; i<=n; ++i)
			sum[i]=sum[i-1]*Base+s[i];
		g[n+1]=0;
		for(i=n; i>=1; --i) {
			c[s[i]-'a']^=1;
			if(c[s[i]-'a']) g[i]=g[i+1]+1;
			else g[i]=g[i+1]-1;
		}
		for(i=0; i<=A; ++i)
			c[i]=0;
		f[0]=0;
		for(i=1; i<=n; ++i) {
			c[s[i]-'a']^=1;
			if(c[s[i]-'a']) f[i]=f[i-1]+1;
			else f[i]=f[i-1]-1;
		}
		for(i=0; i<=A+1; ++i)
			t[i]=c[i]=0;
		ans=0;
		for(i=2; i<n; ++i) {
			ad(f[i-1]+1);
			j=0;
			while(j+i<n&&hash_str(1,i)==hash_str(j+1,j+i)) {
				j+=i;
				ans+=qr(g[j+1]+1);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}