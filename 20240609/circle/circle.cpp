#include <cstdio>
#include <random>
#include <chrono>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
char sss;
const int N = 12, S = 1 << N, M = 20;
const double eps = 1e-12;
int n,m,s;
namespace geometry {
	struct point {
		double x,y;
	} a[N + 2];
	double rad[S + 2];
	double sqr(double x) {
		return x*x;
	}
	double operator-(const point& a,const point& b) {
		return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
	}
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	int randint(int l,int r) {
		return uniform_int_distribution<int>(l,r)(rnd);
	}
	point getO(const point& a,const point& b,const point& c) {
		double u0=2*(b.x-a.x),v0=2*(b.y-a.y),w0=sqr(b.x)-sqr(a.x)+sqr(b.y)-sqr(a.y);
		double u1=2*(c.x-b.x),v1=2*(c.y-b.y),w1=sqr(c.x)-sqr(b.x)+sqr(c.y)-sqr(b.y);
		return {(w0*v1-w1*v0)/(u0*v1-u1*v0),(w1*u0-w0*u1)/(u0*v1-u1*v0)};
	}
	double solve(int sta) {
		vector<point> v;
		for(int i=0; i<n; ++i)
			if(sta&(1<<i))
				v.push_back(a[i+1]);
		const int t=v.size();
		point o=v[0];
		double r=0;
		for(int i=0; i<t; ++i) swap(v[i],v[randint(0,i)]);
		for(int i=0; i<t; ++i) {
			if(v[i]-o<r+eps) continue;
			o={(v[0].x+v[i].x)/2,(v[0].y+v[i].y)/2};
			r=(v[i]-v[0])/2;
			for(int j=0; j<i; ++j) {
				if(v[j]-o<r+eps) continue;
				o={(v[i].x+v[j].x)/2,(v[i].y+v[j].y)/2};
				r=(v[i]-v[j])/2;
				for(int k=0; k<j; ++k) {
					if(v[k]-o<r+eps) continue;
					o=getO(v[i],v[j],v[k]);
					r=v[i]-o;
				}
			}
		}
		return r;
	}
	void init() {
		for(int i=1; i<=n; ++i)
			scanf("%lf%lf",&a[i].x,&a[i].y);
		for(int i=1; i<s; ++i)
			rad[i]=solve(i);
	}
}
namespace dp {
	int r[M + 2],w[M + 2];
	int f[S + 2];
	void init() {
		for(int i=1; i<=m; ++i)
			scanf("%d%d",&r[i],&w[i]);
	}
	using geometry::rad;
	int solve() {
		memset(f,0x3f,sizeof(f));
		f[0]=0;
		for(int i=1; i<=m; ++i)
			for(int j=0; j<s; ++j)
				for(int k=j; k; k=(k-1)&j)
					if(rad[k]<r[i]+eps)
						f[j]=min(f[j],f[j^k]+w[i]);
		return f[s-1];
	}
}
char ttt;
int main() {
	fprintf(stderr,"%lldkb\n",(&ttt-&sss)>>10);
	scanf("%d%d",&n,&m);
	s=1<<n;
	geometry::init();
	dp::init();
	printf("%d\n",dp::solve());
	return 0;
}