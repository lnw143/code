#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 5e4, inf = 1e9;
int n,m,a[N + 2];
vector<int> num,pos[N + 2];
namespace psegtree {
	const int S = N << 6;
	int tot,ls[S],rs[S],rt[N + 2];
	struct node {
		int pre,suf,sum;
		node(int x=0):pre(x),suf(x),sum(x) {}
		node(int x,int y,int z):pre(x),suf(y),sum(z) {}
	} s[S];
#define mid (l+r>>1)
	node operator+(const node& x,const node& y) {
		return node(max(x.pre,x.sum+y.pre),max(y.suf,y.sum+x.suf),x.sum+y.sum);
	}
	int build(int l,int r) {
		int u=++tot;
		if(l==r) {
			s[u]=1;
			return u;
		}
		ls[u]=build(l,mid);
		rs[u]=build(mid+1,r);
		s[u]=s[ls[u]]+s[rs[u]];
		return u;
	}
	int modify(int u,int l,int r,int x) {
		int v=++tot;
		ls[v]=ls[u],rs[v]=rs[u];
		s[v]=s[u];
		if(l==r) {
			s[v]=-1;
			return v;
		}
		if(x<=mid) ls[v]=modify(ls[v],l,mid,x);
		else rs[v]=modify(rs[v],mid+1,r,x);
		s[v]=s[ls[v]]+s[rs[v]];
		return v;
	}
	node query(int u,int l,int r,int x,int y) {
		if(r<x||y<l) return node(-inf,-inf,0);
		if(x<=l&&r<=y) return s[u];
		return query(ls[u],l,mid,x,y)+query(rs[u],mid+1,r,x,y);
	}
#undef mid
}
bool check(int l,int r,int x,int y,int mid) {
	using namespace psegtree;
	const int t=rt[mid-1];
	return query(t,1,n,l,r).suf+query(t,1,n,r+1,x-1).sum+query(t,1,n,x,y).pre>=0;
}
int main() {
	freopen("middle.in","r",stdin);
	freopen("middle.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]),num.push_back(a[i]);
	sort(num.begin(),num.end());
	num.erase(unique(num.begin(),num.end()),num.end());
	for(int i=1; i<=n; ++i) a[i]=lower_bound(num.begin(),num.end(),a[i])-num.begin()+1;
	for(int i=1; i<=n; ++i) pos[a[i]].push_back(i);
	{
		using namespace psegtree;
		rt[0]=build(1,n);
		for(int i=1; i<=num.size(); ++i) {
			int tmp=rt[i-1];
			for(auto j : pos[i])
				tmp=modify(tmp,1,n,j);
			rt[i]=tmp;
		}
	}
	num.insert(num.begin(),0);
	scanf("%d",&m);
	for(int i=1; i<=m; ++i) {
		int s,t,x,y;
		scanf("%d%d%d%d",&s,&t,&x,&y);
		{
			int l=1,r=num.size();
			while(l<=r) {
				int mid=(l+r)/2;
				if(check(s,t,x,y,mid)) l=mid+1;
				else r=mid-1;
			}
			printf("%d\n",num[l-1]);
		}
	}
	return 0;
}