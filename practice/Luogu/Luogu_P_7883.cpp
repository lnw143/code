// haven't finished yet
#include <cstdio>
#include <random>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <utility>
#include <vector>
#include <cassert>
#include <map>
using namespace std;
using ll = long long;
const int N = 4e5;
const ll inf = 1ll << 60;
int n;
struct point { ll x,y; } p[N + 2];
ll sqr(ll x) { return x*x; }
ll operator-(const point& a,const point &b) { return sqr(a.x-b.x)+sqr(a.y-b.y); }
ll ans=inf;
double dis=sqrt(ans);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
map<pair<ll,ll>,vector<int>> mp;
pair<ll,ll> get_pos(int u) { return {floor(p[u].x/dis),floor(p[u].y/dis)}; }
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lld%lld",&p[i].x,&p[i].y);
	for(int i=1; i<=n; ++i) swap(p[i],p[rint(1,i)]);
	for(int i=1; i<=n; ++i) {
		pair<ll,ll> pos=get_pos(i);
		ll res=inf;
		for(int x=-1; x<=1; ++x)	
			for(int y=-1; y<=1; ++y) {
				pair<ll,ll> q{pos.first+x,pos.second+y};
				int sum=0;
				if(mp.count(q)) for(const auto& u : mp[q]) res=min(res,p[i]-p[u]),++sum;
				assert(sum<=36);
			}
		if(res<ans) {
			ans=res;
			dis=sqrt(ans);
			mp.clear();
			for(int j=1; j<=i; ++j) mp[get_pos(j)].push_back(j);
		} else mp[pos].push_back(i);
	}
	printf("%lld",ans);
	return 0;
}