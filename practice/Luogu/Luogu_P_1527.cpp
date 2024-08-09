#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 5e2, V = N * N, Q = 6e4;
int n,q,a[N + 2][N + 2],ans[Q + 2];
vector<int> num;
vector<pair<int,int>> pos[V + 2];
struct query {
	int x1,y1,x2,y2,k;
} qr[Q + 2];
namespace fenwick {
	int cur,s[N + 2][N + 2];
	void add(int x,int y,int v) {
		for(int i=x; i<=n; i+=i&-i)
			for(int j=y; j<=n; j+=j&-j)
				s[i][j]+=v;
	}
	int sum(int x,int y) {
		int res=0;
		for(int i=x; i; i&=i-1)
			for(int j=y; j; j&=j-1)
				res+=s[i][j];
		return res;
	}
	int sum(int x1,int y1,int x2,int y2) {
		return sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1);
	}
	void update(int x) {
		for(int i=cur+1; i<=x; ++i)
			for(auto [x,y] : pos[i])
				add(x,y,1);
		for(int i=cur; i>x; --i)
			for(auto [x,y] : pos[i])
				add(x,y,-1);
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
	fenwick::update(mid);
	vector<int> Ql,Qr;
	for(auto i : Q) {
		auto [x1,y1,x2,y2,k]=qr[i];
		(k<=fenwick::sum(x1,y1,x2,y2)?Ql:Qr).push_back(i);
	}
	solve(l,mid,Ql);
	solve(mid+1,r,Qr);
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			scanf("%d",&a[i][j]),
			num.push_back(a[i][j]);
	sort(num.begin(),num.end());
	num.erase(unique(num.begin(),num.end()),num.end());
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			a[i][j]=lower_bound(num.begin(),num.end(),a[i][j])-num.begin()+1,
			pos[a[i][j]].emplace_back(i,j);
	for(int i=1; i<=q; ++i)
		scanf("%d%d%d%d%d",&qr[i].x1,&qr[i].y1,&qr[i].x2,&qr[i].y2,&qr[i].k);
	vector<int> Q;
	for(int i=1; i<=q; ++i) Q.push_back(i);
	solve(1,num.size(),Q);
	for(int i=1; i<=q; ++i)
		printf("%d\n",num[ans[i]-1]);
	return 0;
}