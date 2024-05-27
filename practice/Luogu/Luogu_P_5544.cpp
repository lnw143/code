#include<cstdio>
#include<random>
#include<chrono>
using namespace std;
using namespace chrono;
const int N = 10, M = 1e3;
const double eps = 1e-12;
int n,m,R,r[N + 2];
template<typename Tp> struct Point {
	Tp x,y;
	Point() = default;
	Point(Tp x,Tp y):x(x),y(y) {}
};
template<typename Tp1,typename Tp2>
double operator-(const Point<Tp1> &a,const Point<Tp2> &b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
Point<int> c[N + 2],p[M + 2];
mt19937 rnd(random_device{}());
double Rnd(double l,double r) {
	return uniform_real_distribution<double>(l,r)(rnd);
}
int calc(Point<double> x) {
	double rad=R;
	for(int i=1; i<=n; ++i)
		rad=min(rad,x-c[i]-r[i]);
	rad+=eps;
	if(rad<0) return 0;
	int sum=0;
	for(int i=1; i<=m; ++i)
		if(x-p[i]<=rad)
			++sum;
	return sum;
}
Point<double> s;
int ans;
int simAnneal() {
	Point<double> x=s;
	int y=calc(x);
	double temp=1e3;
#define randf(a,l,r) a.x+=Rnd(l,r),a.y+=Rnd(l,r)
	while(temp>1e-18) {
		Point<double> x_=x;
		randf(x_,-5e2,5e2);
		int y_=calc(x_);
		if(y_>ans) {
			s=x_;
			ans=y_;
		}
		if(y_>y||Rnd(0,1)<exp((y_-y)/temp)) {
			x=x_;
			y=y_;
		}
		temp*=0.999;
	}
	return ans;
}
const auto start_time=steady_clock::now();
double runtime() {
	return duration<double>(steady_clock::now()-start_time).count();
}
int main() {
	scanf("%d%d%d",&n,&m,&R);
	for(int i=1; i<=n; ++i)
		scanf("%d%d%d",&c[i].x,&c[i].y,&r[i]);
	for(int i=1; i<=m; ++i) {
		scanf("%d%d",&p[i].x,&p[i].y);
		s.x+=p[i].x;
		s.y+=p[i].y;
	}
	double minx=p[1].x,maxx=p[1].x,miny=p[1].y,maxy=p[1].y;
	for(int i=2; i<=m; ++i) {
		if(p[i].x<minx) minx=p[i].x;
		else if(p[i].x>maxx) maxx=p[i].x;
		if(p[i].y<miny) miny=p[i].y;
		else if(p[i].y>maxy) maxy=p[i].y;
	}
	s.x/=m;
	s.y/=m;
	s.x=Rnd(minx,)
	ans=calc(s);
	while(runtime()<0.9) simAnneal();
	printf("%d",ans);
	return 0;
}