#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1e3;
const double eps = 1e-12;
int w,h,n;
struct point {
	double x,y;
} p[N + 2];
double operator-(const point& a,const point& b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool check(int i,double r) {
	for(int j=1; j<=n; ++j) {
		double dis=a[i]-a[j];
		if(j==i||dis<r+eps||dis>2*r-eps) continue;
		
	}
}
int main() {
	scanf("%d%d%d",&w,&h,&n);
	for(int i=1; i<=n; ++i) {
		scanf("%lf%lf",&p[i].x,&p[i].y);
	}

	return 0;
}