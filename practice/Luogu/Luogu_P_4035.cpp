#include<cstdio>
#include<random>
#include<chrono>
#include<cmath>
using namespace std;
using namespace chrono;
const int N = 10;
int n;
mt19937_64 rnd(random_device{}());
inline double Rnd(double l,double r) {
	return uniform_real_distribution<double>(l,r)(rnd);
}
double z,k;
struct Point {
	double a[N + 2];
	void read() {
		for(int i=1; i<=n; ++i)
			scanf("%lf",&a[i]);
	}
	void print() {
		for(int i=1; i<=n; ++i)
			printf("%.3lf ",a[i]);
	}
	Point rand() const {
		Point r;
		double *y=r.a;
		for(int i=1; i<=n; ++i)	
			y[i]=a[i]+Rnd(-k,k);
		return r;
	}
} a[N + 2],ans;
double operator-(const Point &x,const Point &y) {
	const double *a=x.a,*b=y.a;
	double dist=0;
	for(int i=1; i<=n; ++i)
		dist+=(a[i]-b[i])*(a[i]-b[i]);
	return sqrt(dist);
}
double calc(const Point &x) {
	double ave=0;
	vector<double> p(n+1);
	for(int i=0; i<=n; ++i)
		ave+=p[i]=x-a[i];
	ave/=n+1;
	double var=0;
	for(int i=0; i<=n; ++i)
		var+=(p[i]-ave)*(p[i]-ave);
	return var*1e4;
}
void Sim_anneal() {
	Point x=ans;
	double y=calc(x),temp=1e8;
	while(temp>1e-10) {
		Point x_=x.rand();
		double y_=calc(x_);
		if(y_<y||Rnd(0,1)<exp((y-y_)/temp)) {
			x=x_;
			y=y_;
			if(y<z) {
				z=y;
				ans=x;
			}
		}
		temp*=.9997;
	}
	return ;
}
const auto start_time=steady_clock::now();
double runtime() {
	return duration<double>(steady_clock::now()-start_time).count();
}
int main() {
	scanf("%d",&n);
	for(int i=0; i<=n; ++i)
		a[i].read();
	z=calc(ans);
	k=1e2;
	while(z>1e-12&&runtime()<0.9) Sim_anneal(),k*=.2;
	ans.print();
	return 0;
}