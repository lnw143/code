#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
using ll = long long;
const int N = 1e5;
int n;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct triangle {
	int a,b,c;
	triangle()=default;
	triangle(int a,int b,int c):a(a),b(b),c(c) {}
};
bool check(ll a,ll b,ll c) {
	return a+b>c&&a*a+b*b<c*c;
}
vector<triangle> dfs(int n) {
	if(n<=10) {
		vector<int> p(3*n);
		for(int i=0; i<3*n; ++i) p[i]=i+2;
		while(true) {
			shuffle(p.begin(),p.end(),rnd);
			for(int i=0; i<n; ++i)
				sort(p.begin()+i*3,p.begin()+(i+1)*3);
			bool ok=true;
			for(int i=0; i<n; ++i)
				if(!check(p[i*3],p[i*3+1],p[i*3+2])) {
					ok=false;
					break;
				}
			if(ok) break;
		}
		vector<triangle> res(n);
		for(int i=0; i<n; ++i)
			res[i]=triangle(p[i*3],p[i*3+1],p[i*3+2]);
		return res;
	}
	if(n%2==1) {
		vector<triangle> res;
		while(true) {
			vector<triangle> ret=dfs((n-1)/2);
			bool ok=true;
			for(auto [i,j,k] : ret)
				if(!check(i*2,j*2,k*2)||!check(i*2-1,j*2-1,k*2-1)) {
					ok=false;
					break;
				}
			if(ok) {
				res.emplace_back(2,3*n,3*n+1);
				for(auto [i,j,k] : ret)
					res.emplace_back(i*2-1,j*2-1,k*2-1),
					res.emplace_back(i*2,j*2,k*2);
				break;
			}
		}
		return res;
	} else {
		vector<triangle> res;
		while(true) {
			vector<triangle> ret=dfs(n/2-1);
			bool ok=true;
			for(auto [i,j,k] : ret)
				if(!check(i*2,j*2,k*2)||!check(i*2+1,j*2+1,k*2+1)) {
					ok=false;
					break;
				}
			if(ok) {
				res.emplace_back(2,3*n-2,3*n-1);
				res.emplace_back(3,3*n,3*n+1);
				for(auto [i,j,k] : ret)
					res.emplace_back(i*2+1,j*2+1,k*2+1),
					res.emplace_back(i*2,j*2,k*2);
				break;
			}
		}
		return res;
	}
}
int main() {
	freopen("wish.in","r",stdin);
	freopen("wish.out","w",stdout);
	scanf("%d",&n);
	for(auto [i,j,k] : dfs(n))
		printf("%d %d %d\n",i,j,k);
	return 0;
}