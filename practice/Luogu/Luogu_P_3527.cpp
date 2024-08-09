#include <cstdio>
#include <vector>
using namespace std;
using ll = __int128;
const int N = 3e5;
int n,m,k,a[N + 2],p[N + 2],ans[N + 2];
vector<int> pos[N + 2];
struct oper {
	int l,r,k;
} op[N + 2];
namespace fenwick {
	int cur;
	ll s[N + 2];
	void add(int x,int v) {
		for(int i=x; i<=m; i+=i&-i) s[i]+=v;
	}
	void add(int l,int r,int v) {
		if(l<=r) add(l,v),add(r+1,-v);
		else add(l,v),add(1,r,v);
	}
	ll sum(int x) {
		ll res=0;
		for(int i=x; i; i&=i-1) res+=s[i];
		return res;
	}
	void update(int x) {
		for(int i=cur+1; i<=x; ++i)
			add(op[i].l,op[i].r,op[i].k);
		for(int i=cur; i>x; --i)
			add(op[i].l,op[i].r,-op[i].k);
		cur=x;
	}
}
void solve(int l,int r,vector<int> Q) {
	if(Q.empty()) return ;
	if(l==r) {
		for(auto i : Q)
			ans[i]=l;
		return ;
	}
	int mid=(l+r)/2;
	vector<int> Ql,Qr;
	fenwick::update(mid);
	for(auto i : Q) {
		ll sum=0;
		for(auto j : pos[i])
			sum+=fenwick::sum(j);
		(p[i]<=sum?Ql:Qr).push_back(i);
	}
	solve(l,mid,Ql);
	solve(mid+1,r,Qr);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i) scanf("%d",&a[i]),pos[a[i]].push_back(i);
	for(int i=1; i<=n; ++i)
		scanf("%d",&p[i]);
	scanf("%d",&k);
	for(int i=1; i<=k; ++i)
		scanf("%d%d%d",&op[i].l,&op[i].r,&op[i].k);
	vector<int> Q;
	for(int i=1; i<=n; ++i) Q.push_back(i);
	solve(1,k+1,Q);
	for(int i=1; i<=n; ++i)
		if(ans[i]>k)
			printf("NIE\n");
		else
			printf("%d\n",ans[i]);
	return 0;
}