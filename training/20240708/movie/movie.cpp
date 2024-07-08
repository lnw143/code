#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
template<class T> using heap = priority_queue<T,vector<T>,greater<T>>;
const int N = 4e5, K = 3e5 + 5, M = (K + 1) / 2, inf = 1 << 30;
int n,k,m,a[N + 2];
namespace segtree {
	const int S = M << 2;
	struct node {
		int row,pos,len;
		inline int dis() const {
			return abs(row-m)-len;
		}
	} s[S + 2];
	const node INF{inf,inf,-inf};
	bool operator<(const node& x,const node& y) {
		if(x.dis()!=y.dis()) return x.dis()<y.dis();
		if(x.row!=y.row) return x.row<y.row;
		return x.pos<y.pos;
	}
	bool operator>(const node& x,const node& y) {
		return y<x;
	}
	heap<node> hp[M + 2];
#define mid ((l+r)>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void build(int u,int l,int r) {
		s[u]=INF;
		if(l==r) return ;
		build(li);
		build(ri);
	}
	void remove(int u,int l,int r,int x) {
		if(l==r) {
			hp[x].pop();
			s[u]=hp[x].empty()?INF:hp[x].top();
			return ;
		}
		if(x<=mid) remove(li,x);
		else remove(ri,x);
		s[u]=min(s[ls],s[rs]);
	}
	node query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return INF;
		if(x<=l&&r<=y) return s[u];
		return min(query(li,x,y),query(ri,x,y));
	}
	void modify(int u,int l,int r,int x,const node& y) {
		if(l==r) {
			hp[x].push(y);
			s[u]=hp[x].top();
			return ;
		}
		if(x<=mid) modify(li,x,y);
		else modify(ri,x,y);
		s[u]=min(s[ls],s[rs]);
	}
}
inline void put(int x,int p,int l) {
	if(1<=l&&l<=m) segtree::modify(1,1,m,l,{x,p,l});
}
int main() {
	freopen("movie.in","r",stdin);
	freopen("movie.out","w",stdout);
	scanf("%d%d",&n,&k);
	m=(k+1)>>1;
	segtree::build(1,1,m);
	for(int i=1,l=m,r=m+1; i<=n; ++i) {
		int x;
		scanf("%d",&x);
		if(x>k) {
			printf("-1\n");
			continue;
		}
		const int t = l<1&&r>k?-1:(r>k||(l>=1&&m-l<=r-m)), L = m-x/2, R = L+x-1;
		const int cost = t==-1?inf:x*(const int [2]){l,r}[t];
		printf("%d %d %d\n",t,L,R);
		put(t,0,L-1);
		put(t,1,k-R);
		auto res=segtree::query(1,1,m,x,m);
	}
	return 0;
}