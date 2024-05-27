#include <vector>
#include <utility>
#include <cassert>
#include "Bob.h"

using namespace std;
using LL = __int128;
using ll = long long;

LL exgcd(LL a,LL b,LL &x,LL &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	LL d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

ll CRT(const vector<pair<ll,ll>>& eq) {
	LL a=0,m=1;
	for(auto [n,b] : eq) {
		LL x,y,d=exgcd(m,n,x,y);
		assert(m*x+n*y==d);
		m=m/d*n;
		a=((b+y*(a-b)/d%m*n%m)%m+m)%m;
		if(m>1e18) break;
	}
	return a;
}

ll Bob(vector<pair<int,int>> V){
	vector<pair<ll,ll>> eq;
	for(auto [u,v] : V)
		eq.emplace_back(v-1,u-1);
    return CRT(eq);
}