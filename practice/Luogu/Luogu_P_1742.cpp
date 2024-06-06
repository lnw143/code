#include <cstdio>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;
mt19937 rnd(random_device{}());
const int N = 1e5;
const double eps = 1e-12;
int n;
struct point {
	double x,y;
} p[N + 2];
double operator-(const point &a,const point &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
point getO(const point& a,const point& b,const point& c) {
	double u1=2*(b.x-a.x),v1=2*(b.y-a.y),w1=b.x*b.x-a.x*a.x+b.y*b.y-a.y*a.y;
	double u2=2*(c.x-a.x),v2=2*(c.y-a.y),w2=c.x*c.x-a.x*a.x+c.y*c.y-a.y*a.y;
	return {(v1*w2-v2*w1)/(u2*v1-u1*v2),(u1*w2-u2*w1)/(v2*u1-v1*u2)};
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=1; i<=n; ++i) swap(p[i],p[rnd()%i+1]);
	point o=p[1];
	double r=0;
	for(int i=1; i<=n; ++i) {
		if(o-p[i]<r+eps) continue;
		o.x=(p[1].x+p[i].x)/2;
		o.y=(p[1].y+p[i].y)/2;
		r=(p[1]-p[i])/2;
		for(int j=1; j<i; ++j) {
			if(o-p[j]<r+eps) continue;
			o.x=(p[j].x+p[i].x)/2;
			o.y=(p[j].y+p[i].y)/2;
			r=(p[i]-p[j])/2;
			for(int k=1; k<j; ++k) {
				if(o-p[k]<r+eps) continue;
				o=getO(p[k],p[j],p[i]);
				r=o-p[i];
			}
		}
	}
	printf("%.15lf\n%.15lf %.15lf",r,o.x,o.y);
	return 0;
}