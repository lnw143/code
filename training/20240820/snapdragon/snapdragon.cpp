#include <cstdio>
#include <algorithm>
namespace IO {
	inline char gc() {
		static char *l,*r,buf[1<<16];
		return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
	}
	template<class T> inline void read(T &x) {
		x=0;
		char c=gc();
		for(; c<'0'||c>'9'; c=gc());
		for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c&15);
	}
	template<class T,class ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	char puf[1<<16],*p=puf;
	inline void pc(char c) {
		*p++=c;
		if(p-puf==1<<16) fwrite(puf,1,1<<16,stdout),p=puf;
	}
	inline void writeYN(bool f) {
		if(f) pc('Y'),pc('E'),pc('S'),pc('\n');
		else pc('N'),pc('O'),pc('\n');
	}
	struct Flush {
		~Flush() {
			fwrite(puf,1,p-puf,stdout);
		}
	} f;
}
using IO::read;
using IO::writeYN;
using namespace std;
const int N = 5e5, inf = 1 << 30;
int n,m,q,cur=1;
struct interval {
	int l,r,id;
} a[N + 2],b[N + 2];
namespace segtree {
	const int S = N << 2;
	int s[S + 2],t[S + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void modify(int u,int l,int r,int x,int y,int k) {
		if(x<=l&&r<=y) {
			s[u]=max(s[u],k);
			t[u]=max(t[u],k);
			return ;
		}
		if(x<=mid) modify(li,x,y,k);
		if(mid<y) modify(ri,x,y,k);
		s[u]=max(t[u],min(s[ls],s[rs]));
	}
	int query(int u,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return s[u];
		if(mid<x) return max(t[u],query(ri,x,y));
		if(y<=mid) return max(t[u],query(li,x,y));
		return max(t[u],min(query(li,x,y),query(ri,x,y)));
	}
#undef mid
#undef ls
#undef rs
#undef li
#undef ri
}
void solve(int x) {
	for(int &i=cur; i<=m&&a[i].r<=x; ++i)
		segtree::modify(1,1,n,a[i].l,a[i].r,a[i].l);
}
bool ans[N + 2];
int main() {
	freopen("snapdragon.in","r",stdin);
	freopen("snapdragon.out","w",stdout);
	read(n,m,q);
	for(int i=1; i<=m; ++i)
		read(a[i].l,a[i].r);
	for(int i=1; i<=q; ++i)
		read(b[i].l,b[i].r),b[i].id=i;
	sort(a+1,a+m+1,[](auto x,auto y) { return x.r<y.r; });
	sort(b+1,b+q+1,[](auto x,auto y) { return x.r<y.r; });
	for(int i=1; i<=q; ++i) {
		solve(b[i].r);
		ans[b[i].id]=(segtree::query(1,1,n,b[i].l,b[i].r)>=b[i].l);
	}
	for(int i=1; i<=q; ++i)
		writeYN(ans[i]);
	return 0;
}