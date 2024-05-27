#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e6;
int T,n,i,a[N + 2],p[N + 2];
struct Node {
	int x,v;
	void init(int y) {
		x=y;
		v=a[x];
	}
	void upd(int y) {
		v=y;
	}
	bool operator<(const Node t) const {
		return v==t.v?x<t.x:v<t.v;
	}
};
template<Node g(Node,Node)>
struct Segment_Tree {
	Node tr[N * 4 + 2];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
	void mk(int x,int l,int r) {
		if(l==r) {
			tr[x].init(l);
			return ;
		}
		int mid=(l+r)/2;
		mk(li);
		mk(ri);
		tr[x]=g(tr[ls],tr[rs]);
	}
	void cg(int x,int l,int r,int y,int f) {
		if(r<y||y<l) return ;
		if(l==r) {
			tr[x].v=f;
			return ;
		}
		int mid=(l+r)/2;
		if(y<=mid) cg(li,y,f);
		else cg(ri,y,f);
		tr[x]=g(tr[ls],tr[rs]);
	}
	Node top() {
		return tr[1];
	}
#undef ls
#undef rs
#undef li
#undef ri
};
Node max(Node a,Node b) {
	return a<b?b:a;
}
Node min(Node a,Node b) {
	return a<b?a:b;
}
Segment_Tree<max> tmax;
Segment_Tree<min> tmin;
void del(int x) {
	tmax.cg(1,1,n,x,-1e9);
	tmin.cg(1,1,n,x,1e9);
}
int main() {
	freopen("snakes.in","r",stdin);
	freopen("snakes.out","w",stdout);
	scanf("%d%d",&T,&n);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	while(T--) {
		tmax.mk(1,1,n);
		tmin.mk(1,1,n);
		for(i=1; i<n; ++i) {
			Node maxt=tmax.top(),mint=tmin.top();
			if(p[mint.x]) {
				printf("%d\n",n-p[mint.x]+1);
				break;
			}
			p[maxt.x]=i;
			del(mint.x);
			tmax.cg(1,1,n,maxt.x,maxt.v-mint.v);
			tmin.cg(1,1,n,maxt.x,maxt.v-mint.v);
		}
		if(i==n) printf("1\n");
		if(T) {
			int k;
			scanf("%d",&k);
			for(i=1; i<=k; ++i) {
				int x,y;
				scanf("%d%d",&x,&y);
				a[x]=y;
			}
			memset(p+1,0,sizeof(*p)*n);
		}
	}
	return 0;
}