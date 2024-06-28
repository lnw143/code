#include <cstdio>
#include <vector>
using namespace std;
const int N = 5e4, Q = 5e5;
using ll = long long;
int n,m,q;
inline char gc() {
	static char buf[1<<16],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin))?-1:*l++;
}
template <class T> void read(T& x) {
	x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c^48);
}
template <class T,class ...Args> void read(T& x,Args &...args) {
	read(x);
	read(args...);
}
struct {
	int l1,r1;
	int l2,r2;
} p[N + 2];
#define mid ((l+r)>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
namespace segtr {
	struct modi {
		int l,r;
		ll x;
	};
	const int S = N << 2;
	vector<modi> s[S + 2];
	void modify(int u,int l,int r,int x,int y,modi f) {
		if(r<x||y<l) return ;
		if(x<=l&&r<=y) {
			s[u].push_back(f);
			return ;
		}
		modify(li,x,y,f);
		modify(ri,x,y,f);
	}

}
int main() {
	read(n,m,q);
	for(int i=1; i<=m; ++i) {
		int l1,r1,l2,r2;
		ll x;
		read(l1,l2,r1,r2,x);
		segtr::modify(1,1,n,l1,r1,{l2,r2,x});
	}
	for(int i=1; i<=q; ++i) read(p[i].l1,p[i].l2,p[i].r1,p[i].r2);
	return 0;
}