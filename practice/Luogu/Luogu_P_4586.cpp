#define _USE_MATH_DEFINES
#include <cstdio>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
using namespace std;
const int N = 1e3;
const double eps = 1e-12;
int n;
double ans;
struct point {
	double x,y;
	point turn(double theta) {
		double c=cos(theta),s=sin(theta);
		return {x*c-y*s,x*s+y*c};
	}
} p[N + 2];
inline double sqr(double x) { return x*x; }
inline bool operator<(const point& a,const point &b) { return a.x<b.x; }
inline double operator-(const point& x,const point& y) { return sqrt(sqr(x.x-y.x)+sqr(x.y-y.y)); }
namespace MCC {
	mt19937 rnd(random_device{}());
	inline int rint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
	point getO(const point& a,const point& b,const point& c) {
		double u1=2*(a.x-b.x),v1=2*(a.y-b.y),w1=sqr(a.x)+sqr(a.y)-sqr(b.x)-sqr(b.y);
		double u2=2*(a.x-c.x),v2=2*(a.y-c.y),w2=sqr(a.x)+sqr(a.y)-sqr(c.x)-sqr(c.y);
		return {(w2*v1-v2*w1)/(u2*v1-u1*v2),(w2*u1-u2*w1)/(v2*u1-v1*u2)};
	}
	double solve(int L,int R) {
		if(L>R) return 0;
		const int m=R-L+1;
		vector<point> q;
		for(int i=L; i<=R; ++i) q.push_back(p[i]);
		for(int i=1; i<m; ++i) swap(q[i],q[rint(0,i)]);
		point o=q[0];
		double r=0;
		for(int i=0; i<m; ++i) {
			if(o-q[i]<r+eps) continue;
			o={(q[i].x+q[0].x)/2,(q[i].y+q[0].y)/2};
			r=(q[i]-q[0])/2;
			for(int j=0; j<i; ++j) {
				if(o-q[j]<r+eps) continue;
				o={(q[i].x+q[j].x)/2,(q[i].y+q[j].y)/2};
				r=(q[i]-q[j])/2;
				for(int k=0; k<j; ++k) {
					if(o-q[k]<r+eps) continue;
					o=getO(q[i],q[j],q[k]);
					r=q[i]-o;
				}
			}
		}
		return r;
	}
}
void solve() {
	sort(p+1,p+n+1);
	int l=1,r=n;
	while(l<=r) {
		int mid=(l+r)/2;
		double r1=MCC::solve(1,mid),r2=MCC::solve(mid+1,n);
		if(ans<min(r1,r2)+eps) return ;
		ans=min(ans,max(r1,r2));
		if(r1>r2) r=mid-1;
		else l=mid+1;
	}
}
int main() {
	while(scanf("%d",&n),n) {
		ans=1e20;
		for(int i=1; i<=n; ++i) scanf("%lf%lf",&p[i].x,&p[i].y);
		for(int d=0; d<180; ++d) {
			solve();
			for(int i=1; i<=n; ++i) p[i]=p[i].turn(M_PI/180);
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}