#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 1e6, M = 1e6, INF = 1 << 30;
int n,m,i,j,a[N + 2],fa[N + 2],dfn[N + 2],low[N + 2],dep[N + 2],op[M + 2],x[M + 2],dfc;
vector<int> e[N + 2];
void dfs(int x) {
    dfn[x]=++dfc;
    for(int v : e[x]) 
	dfs(v);
    low[x]=dfc;
}
template<int max(int,int),int inf>
struct STree {
    int tr[(N << 2) + 2];
#define ls (x<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
    void mk(int x,int l,int r) {
		if(l==r) {
			tr[x]=a[l];
			return ;
		}
		int mid=(l+r)/2;
		mk(li);
		mk(ri);
		tr[x]=max(tr[ls],tr[rs]);
    }
    void cg(int x,int l,int r,int y,int f) {
		if(r<y||y<l) return ;
		if(l==r) {
			tr[x]=f;
			return ;
		}
		int mid=(l+r)/2;
		if(y<=mid) cg(li,y,f);
		else cg(ri,y,f);
		tr[x]=max(tr[ls],tr[rs]);
    }
    int qr(int x,int l,int r,int L,int R) {
		if(r<L||R<l) return inf;
		if(L<=l&&r<=R) return tr[x];
		int mid=(l+r)/2;
		return max(qr(li,L,R),qr(ri,L,R));
    }
};
int Max(int x,int y) {
    return x<y?y:x;
}
int Min(int x,int y) {
    return x<y?x:y;
}
STree<Max,-INF> mxt;
STree<Min,INF> mnt;
void wk(int x,int op) {
    int y=op?mxt.qr(1,1,n,dfn[x],low[x]):mnt.qr(1,1,n,dfn[x],low[x]);
    mxt.cg(1,1,n,x,y);
    mnt.cg(1,1,n,x,y);
}
int main() {
    freopen("spider.in","r",stdin);
    freopen("spider.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
    dep[1]=1;
    for(i=2; i<=n; ++i) {
		scanf("%d",&fa[i]);
		dep[i]=dep[fa[i]]+1;
		e[fa[i]].push_back(i);
    }
    dfs(1);
    mxt.mk(1,1,n);
    mnt.mk(1,1,n);
    for(i=1; i<=m; ++i)
		scanf("%d%d",&x[i],&op[i]);
    for(i=2; i<=m; ++i)
		if(op[i]!=op[1])
			break;
	if(i>m)
		for(i=1; i<=m; ++i)
			if(x[i]==1) {
				wk(1,op[1]);
				break;
			}
	else
		for(i=1; i<=m; ++i)
			for(j=1; j<=n; ++j)
				if(dep[j]==x[i])
					wk(j,op[i]);
    printf("%d",mnt.qr(1,1,n,1,1));
    return 0;
}