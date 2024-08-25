#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int n,m,w,h,cnt;
struct segment {
	int x1,y1,x2,y2;
} a[N + 2];
#define mid (l+r>>1)
#define ls (u<<1)
#define rs (ls|1)
#define li ls,l,mid
#define ri rs,mid+1,r
namespace segtree {
	const int S = N * 2 << 2;
	int sum[S];
	void modify(int u,int l,int r,int x,int k) {
		if(l==r) return sum[u]+=k,void();
		if(x<=mid) modify(li,x,k);
		else modify(ri,x,k);
		sum[u]=sum[ls]+sum[rs];
	}
	int query(int u,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return sum[u];
		if(y<=mid) return query(li,x,y);
		if(mid<x) return query(ri,x,y);
		return query(li,x,y)+query(ri,x,y);
	}
}
namespace dsu {
	int fa[N + 2];
	void init() {
		for(int i=1; i<=n; ++i) fa[i]=i;
	}
	int find(int u) {
		return fa[u]==u?u:fa[u]=find(fa[u]);
	}
	void merge(int u,int v) {
		fa[find(u)]=find(v);
	}
}
namespace dseg {
	const int S = N * 2 << 2;
	int s[S];
	void pushup(int u) {
		using namespace dsu;
		if(!s[ls]||!s[rs]) s[u]=s[ls]|s[rs];
		else if(s[ls]==-1||s[rs]==-1||find(s[ls])!=find(s[rs])) s[u]=-1;
		else s[u]=find(s[ls]);
	}
	void modify(int u,int l,int r,int x,int k) {
		if(l==r) return s[u]=k,void();
		if(x<=mid) modify(li,x,k);
		else modify(ri,x,k);
		pushup(u);
	}
	void merge(int u,int l,int r,int x,int y,int k) {
		if(x<=l&&r<=y&&s[u]!=-1) {
			if(!s[u]) return ;
			dsu::merge(s[u],k);
			s[u]=dsu::find(s[u]);
			return ;
		}
		if(x<=mid) merge(li,x,y,k);
		if(mid<y) merge(ri,x,y,k);
		pushup(u);
	}
}
#undef mid
#undef ls
#undef rs
#undef li
#undef ri
vector<int> row;
struct operation {
	int x,y,type;
} op[2 * N + 2];
int tot;
void discrete() {
	vector<int> v;
	for(int i=1; i<=n; ++i) {
		auto &[x1,y1,x2,y2]=a[i];
		v.push_back(x1);
		v.push_back(x2);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	m=v.size();
	for(int i=1; i<=n; ++i) {
		auto &[x1,y1,x2,y2]=a[i];
		x1=lower_bound(v.begin(),v.end(),x1)-v.begin()+1;
		x2=lower_bound(v.begin(),v.end(),x2)-v.begin()+1;
	}
	v.clear();
	for(int i=1; i<=n; ++i) {
		auto &[x1,y1,x2,y2]=a[i];
		v.push_back(y1);
		v.push_back(y2+1);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1; i<=n; ++i) {
		auto &[x1,y1,x2,y2]=a[i];
		y1=lower_bound(v.begin(),v.end(),y1)-v.begin()+1;
		y2=lower_bound(v.begin(),v.end(),y2+1)-v.begin()+1;
	}
}
int main() {
	freopen("plane.in","r",stdin);
	freopen("plane.out","w",stdout);
	scanf("%d%d%d",&n,&w,&h);
	for(int i=1; i<=n; ++i) {
		auto &[x1,y1,x2,y2]=a[i];
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1>x2) swap(x1,x2);
		if(y1>y2) swap(y1,y2);
	}
	a[++n]={0,0,0,h};
	a[++n]={w,0,w,h};
	a[++n]={0,0,w,0};
	a[++n]={0,h,w,h};
	discrete();
	for(int i=1; i<=n; ++i)
		if(a[i].x1==a[i].x2)
			op[++tot]={a[i].x1,a[i].y1,i},
			op[++tot]={a[i].x1,a[i].y2,-1};
		else
			row.push_back(i);
	sort(row.begin(),row.end(),[](int x,int y) { return a[x].y1<a[y].y1; });
	sort(op+1,op+tot+1,[](auto a,auto b) { return a.y<b.y; });
	int j=1;
	long long sum=0;
	dsu::init();
	for(auto i : row) {
		auto [x1,y,x2,tmp]=a[i];
		while(j<=tot&&op[j].y<=y) {
			if(op[j].type==-1) {
				segtree::modify(1,1,m,op[j].x,-1);
				dseg::modify(1,1,m,op[j].x,0);
			} else {
				segtree::modify(1,1,m,op[j].x,1);
				dseg::modify(1,1,m,op[j].x,op[j].type);
			}
			++j;
		}
		sum+=segtree::query(1,1,m,x1,x2);
		dseg::merge(1,1,m,x1,x2,i);
	}
	for(int i=1; i<=n; ++i)
		if(dsu::find(i)==i)
			++sum;
	printf("%lld",sum-n);
	return 0;
}