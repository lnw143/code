#include<cstdio>
#include<algorithm>
using namespace std;
constexpr int N = 2e5, M = 1e6;
int n,m,a[N + 2],f[N + 2],ans[M + 2];
struct query {
	int l,r,v;
} q[M + 2];
bool operator<(const query& x,const query& y) {
	return x.l!=y.l?x.l<y.l:x.r<y.r;
}
inline char gc() {
	static char buf[1<<16],*l,*r;
	return (l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r))?EOF:*l++;
}
template<typename Tp> void read(Tp &x) {
	x=0;
	char c=gc();
	while(c<'0'||c>'9') c=gc();
	for(; '0'<=c&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c^48);
}
int main() {
	read(n),read(m);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=n; ++i)
		for(int j=i,sum=0; j<=n; ++j) {
			sum^=a[i]+a[j];
			f[j]^=sum;
		}
	for(int i=1; i<=m; ++i) {
		read(q[i].l),read(q[i].r);
		q[i].v=i;
	}
	sort(q+1,q+m+1);
	for(int i=1,j=1; i<=m; ++i) {
		while(j<q[i].l) {
			for(int k=j,sum=0; k<=n; ++k) {
				sum^=a[k]+a[j];
				f[k]^=sum;
			}
			++j;
		}
		ans[q[i].v]=f[q[i].r];
	}
	for(int i=1; i<=m; ++i)
		printf("%d\n",ans[i]);
	return 0;
}