#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
using ll = long long;
const int N = 2e4, K = 7;
const vector<vector<ll>> D = {
	{},
	{},
	{2},
	{3,4},
	{4,6,10},
	{5,6,8,9,14,21},
	{6,8,10,14,44,52},
	{7,8,9,10,12,15,22,33,39,52,55,68,102,114,138},
};
int T,k;
ll a,b;
map<ll,int> mp,S[K + 2];
void dfs(int u,ll l,int s) {
	if(u==D[k].size()) {
		if(l>1) mp[l]+=s;
		return ;
	}
	dfs(u+1,l,s);
	dfs(u+1,l/__gcd(l,D[k][u])*D[k][u],-s);
}
ll solve(ll x) {
	ll res=0;
	for(auto [i,j] : S[k])
		res+=x/i*j;
	return res;
}
int main() {
	for(k=2; k<=K; ++k) {
		mp.clear();
		dfs(0,1,-1);
		for(auto [i,j] : mp)
			if(j!=0)
				S[k][i]=j;
	}
	scanf("%d",&T);
	while(T--) {
		scanf("%lld%lld%x",&a,&b,&k);
		printf("%lld\n",solve(b)-solve(a-1));
	}
	return 0;
}