#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e6 + 2;
int n,m,i;
double ans=1e20;
struct Point {
	int x,y;
	double f(double k) {
		return x+y-x*k-y/k;
	}
	double slope(Point t) {
		return double(y-t.y)/(x-t.x);
	}
	void input() {
		scanf("%d%d",&x,&y);
	}
	bool operator<(const Point t) const {
		return x!=t.x?x<t.x:y>t.y;
	}
} a[N],b[N],x;
bool cmp(Point a,Point b,Point c) {
	return (a.y-b.y)*(b.x-c.x)<=(b.y-c.y)*(a.x-b.x);
}
int main() {
	freopen("monster4.in","r",stdin);
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		a[i].input();
	stable_sort(a+1,a+n+1);
	for(i=1; i<=n; ++i) {
		while(1<m&&cmp(b[m-1],b[m],a[i])) --m;
		b[++m]=a[i];
	}
	for(i=1; i<=m; ++i) {
		if((i==1||b[i].slope(b[i-1])>(double)-b[i].y/b[i].x)&&(i==m||b[i].slope(b[i+1])>(double)-b[i].y/b[i].x))
			ans=min(ans,2.0*(b[i].x+b[i].y));
		if(i>1) ans=min(ans,b[i].f(b[i].slope(b[i-1])));
		if(i<m) ans=min(ans,b[i].f(b[i].slope(b[i+1])));
	}
	printf("%.4lf",ans);
	return 0;
}