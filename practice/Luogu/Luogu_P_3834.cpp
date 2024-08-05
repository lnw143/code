#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2e5;
int n,m,a[N + 2],ans[N + 2];
vector<int> num,p[N + 2];
struct query {
	int l,r,k;
} q[N + 2];
namespace fenwick {
	int cur,s[N + 2];
	void add(int x,int v) {
		for(; x<=n; x+=x&-x) s[x]+=v;
	}
	int sum(int x) {
		int r=0;
		for(; x; x&=x-1) r+=s[x];
		return r;
	}
	int sum(int l,int r) {
		return sum(r)-sum(l-1);
	}
	void update(int x) {
		for(int i=cur; i>x; --i)
			for(auto j : p[i])
				add(j,-1);
		for(int i=cur+1; i<=x; ++i)
			for(auto j : p[i])
				add(j,1);
		cur=x;
	}
}
void solve(int l,int r,vector<int> Q) {
	if(Q.empty()) return ;
	if(l==r) {
		for(auto i : Q) ans[i]=l;
		return ;
	}
	int mid=(l+r)/2;
	fenwick::update(mid);
	vector<int> Ql,Qr;
	for(auto i : Q)
		(fenwick::sum(q[i].l,q[i].r)>=q[i].k?Ql:Qr).push_back(i);
	solve(l,mid,Ql);
	solve(mid+1,r,Qr);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]),num.push_back(a[i]);
	sort(num.begin(),num.end());
	num.erase(unique(num.begin(),num.end()),num.end());
	for(int i=1; i<=n; ++i) {
		a[i]=lower_bound(num.begin(),num.end(),a[i])-num.begin()+1;
		p[a[i]].push_back(i);
	}
	vector<int> Q;
	for(int i=1; i<=m; ++i)
		scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k),
		Q.push_back(i);
	solve(1,num.size(),Q);
	for(int i=1; i<=m; ++i)
		printf("%d\n",num[ans[i]-1]);
	return 0;
}