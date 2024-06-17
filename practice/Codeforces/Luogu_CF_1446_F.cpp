#define _USE_MATH_DEFINES
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;
const int N = 1e5;
const double eps = 1e-12;
int n;
ll k;
double ang[N + 2],dis[N + 2];
struct point { double x,y; } p[N + 2];
const point O{0,0};
inline double sqr(double x) { return x*x; }
inline double operator-(const point& a,const point& b) { return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)); }
namespace fenwick {
	int t[N * 2 + 2];
	void add(int x,int f) {
		while(x<=2*n) {
			t[x]+=f;
			x+=x&-x;
		}
	}
	int query(int u) {
		int r=0;
		while(u) {
			r+=t[u];
			u&=u-1;
		}
		return r;
	}
	int query(int l,int r) {
		return query(r)-query(l-1);
	}
	void clean(int m) {
		memset(t,0,sizeof(int)*(m+1));
	}
}
ll check(const double rad) {
	int sum=0;
	vector<pair<double,double>> p;
	for(int i=1; i<=n; ++i)
		if(dis[i]<rad+eps) ++sum;
		else {
			double theta=acos(rad/dis[i]),u=ang[i]+theta,v=ang[i]-theta;
			if(u>M_PI) u-=2*M_PI;
			if(v<-M_PI) v+=2*M_PI;
			if(u>v) swap(u,v);
			p.emplace_back(u,v);
		}
	ll res=sum*ll(n-sum)+sum*(sum-1ll)/2+(n-sum)*(n-sum-1ll)/2;
	vector<double> v;
	for(auto [i,j] : p)
		v.push_back(i),
		v.push_back(j);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end(),[](double x,double y) { return abs(x-y)<eps; }),v.end());
	vector<pair<int,int>> q;
	for(auto [i,j] : p)
		q.emplace_back(lower_bound(v.begin(),v.end(),i)-v.begin()+1,lower_bound(v.begin(),v.end(),j)-v.begin()+1);
	sort(q.begin(),q.end(),[](auto x,auto y) {
		return x.first!=y.first?x.first<y.first:x.second>y.second;
	});
	fenwick::clean(v.size());
	for(auto [i,j] : q) {
		res-=fenwick::query(i+1,j);
		fenwick::add(j,1);
	}
	return res;
}
double solve() {
	double l=0,r=1e5;
	for(int j=0; j<100; ++j) {
		double mid=(l+r)/2;
		if(check(mid)<k) l=mid;
		else r=mid;
	}
	return r;
}
int main() {
	scanf("%d%lld",&n,&k);
	for(int i=1; i<=n; ++i) scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=1; i<=n; ++i) ang[i]=atan2(p[i].y,p[i].x),dis[i]=p[i]-O;
	printf("%.15lf",solve());
	return 0;
}