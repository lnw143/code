#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <random>
#include <utility>
#include <algorithm>
using namespace std;
const int N = 1e3;
const double eps = 1e-12;
int w,h,n;
struct point {
	double x,y;
} p[N + 2];
inline double operator-(const point& a,const point& b) { return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
inline bool eq(double x,double y) { return abs(x-y)<eps; }
inline bool lt(double x,double y) { return x+eps<y; }
inline bool le(double x,double y) { return x<y+eps; }
inline bool gt(double x,double y) { return x>y+eps; }
inline bool ge(double x,double y) { return x+eps>y; }
inline double sqr(double x) { return x*x; }
inline double pAng(const point& o,const point& x) { return atan2(x.y-o.y,x.x-o.x); }
inline pair<double,double> interC(int i,int j,double r) {
	double g=pAng(p[i],p[j]),d=p[i]-p[j],theta=acos(sqr(d)/(2*d*r));
	double L=g-theta,R=g+theta;
	if(L<-M_PI) L+=2*M_PI;
	if(R>M_PI) R-=2*M_PI;
	return {L,R};
}
int cnt;
pair<double,int> t[N * 4 + 50];
bool check(int i,double r) {
	// process with other circles
	cnt=0;
	for(int j=1; j<=n; ++j) {
		double dis=p[i]-p[j];
		if(le(dis,0)||ge(dis,2*r)) continue;
		auto [x,y]=interC(i,j,r);
		if(x<y) t[++cnt]={x,1},t[++cnt]={y,-1};
		else {
			t[++cnt]={x,1},t[++cnt]={M_PI,-1};
			t[++cnt]={-M_PI,1},t[++cnt]={y,-1};
		}
	}
	// process with rectangle (w * h)
	if(lt(p[i].x,r)) { // x=0
		double theta=acos(p[i].x/r);
		t[++cnt]={M_PI-theta,2};
		t[++cnt]={-M_PI,2};
		t[++cnt]={-M_PI+theta,-2};
	}
	if(lt(w,p[i].x+r)) { // x=w
		double theta=acos((w-p[i].x)/r);
		t[++cnt]={-theta,2};
		t[++cnt]={theta,-2};
	}
	if(lt(p[i].y,r)) { // y=0
		double theta=acos(p[i].y/r);
		t[++cnt]={-M_PI_2-theta,2};
		t[++cnt]={-M_PI_2+theta,-2};
	}
	if(lt(h,p[i].y+r)) { // y=h
		double theta=acos((h-p[i].y)/r);
		t[++cnt]={M_PI_2-theta,2};
		t[++cnt]={M_PI_2+theta,-2};
	}
	t[++cnt]={-M_PI,0},t[++cnt]={M_PI,0};
	stable_sort(t+1,t+cnt+1,[](const auto& a,const auto& b) {
		return a.first<b.first;
	});
	int sum=0;
	for(int i=1; i<cnt; ++i) {
		sum+=t[i].second;
		if(sum<=1&&lt(t[i].first,t[i+1].first)) return true;
	}
	return false;
}
mt19937 rnd(random_device{}());
int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
int main() {
	scanf("%d%d%d",&w,&h,&n);
	for(int i=1; i<=n; ++i) scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=1; i<=n; ++i) swap(p[i],p[randint(1,i)]);
	double ans=0;
	for(int i=1; i<=n; ++i)
		if(check(i,ans+1e-6)) {
			double l=ans,r=1e10;
			for(int j=0; j<100; ++j) {
				double mid=(l+r)/2;
				if(check(i,mid)) l=mid;
				else r=mid;
			}
			ans=l;
		}
	printf("%.15lf",ans);
	return 0;
}