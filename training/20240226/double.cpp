#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#define rep(i,l,r) for(int i=(l),i##END=(r); i<=i##END; ++i)
#define per(i,l,r) for(int i=(r),i##END=(l); i>=i##END; --i)
using namespace std;
using ll = long long;
const int N(1e6), P(998244353);
struct Edge {
	int v,c;
	Edge(int v_,int c_):v(v_),c(c_) {}
};
int n,m;
map<int,int> e[N + 2];
struct Result {
	ll all,nol,nor;
	Result(ll all_,ll nol_,ll nor_):all(all_),nol(nol_),nor(nor_) {}
};
Result dfs(int l,int r) {
	int c=e[l][r];
	if(l+1==r) return Result(c*ll(c-1)%P,c,c);
	int r_=(*(--e[l].find(r))).first;
	vector<Result> res;
	res.push_back(dfs(l,r_));
	for(int i=r_; i<r; i=(*e[i].rbegin()).first)
		res.push_back(dfs(i,(*e[i].rbegin()).first));
	int n=res.size();
	ll mid_all=1;
	rep(i,1,n-2)
		mid_all=res[i].all*mid_all%P;
	ll all=res[0].all*res[n-1].all%P*mid_all%P,
	nol=res[0].nol*res[n-1].all%P*mid_all%P,
	nor=res[0].all*res[n-1].nor%P*mid_all%P,
	nolr=res[0].nol*res[n-1].nor%P*mid_all%P;
	return Result((all+(nol+nor)*c%P+nolr*c%P*(c-1)%P)%P,(nol+nolr*c%P)%P,(nor+nolr*c%P)%P);
}
int main() {
	freopen("double.in","r",stdin);
	freopen("double.out","w",stdout);
	scanf("%d%d",&n,&m);
	rep(i,1,m) {
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		e[x][y]=c;
	}
	printf("%d",(int)dfs(1,n).all);
	return 0;
}