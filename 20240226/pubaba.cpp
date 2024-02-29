#include<cstdio>
#include<cctype>
#include<vector>
#define rep(i,l,r) for(int i=(l); i<=(r); ++i)
#define per(i,l,r) for(int i=(l); i>=(r); --i)
using namespace std;
using ll = long long;
const int N(5e6);
int n,m,f[N + 2],g[N + 2];
ll s,sum,h[N + 2],ans[N + 2],least,most;
inline char gc() {
	const int BUF = 1<<20;
	static char ch[BUF], *l, *r;
	return (l == r && (r = (l = ch) + fread(ch, 1, BUF, stdin), l == r)) ? EOF : *l++;
}
template <typename T> inline void read(T &x) {
	x = 0; int f = 1; char c = gc();
	for (; !isdigit(c); c = gc()) if (c == '-') f = -f;
	for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
int main() {
	freopen("pubaba.in","r",stdin);
	freopen("pubaba.out","w",stdout);
	read(n);
	read(m);
	read(s);
	rep(i,1,m) {
		int l,r;
		read(l);
		read(r);
		++g[r];
		++f[l];
		least+=l;
		most+=r;
	}
	if(s<least||most<s) {
		printf("-1");
		return 0;
	}
	per(i,n,1) {
		g[i]+=g[i+1];
		h[i]=h[i+1]+f[i+1];
		f[i]+=f[i+1];
	}
	rep(i,1,n) {
		ans[i]=min(s-h[i],ans[i-1]+g[i]);
		sum^=ll(n-i+1)*(ans[i]/i);
	}
	printf("%lld",sum);
	return 0;
}