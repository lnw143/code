#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 3e6 + 2, Month_Days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int n,i,j;
ll x;
int a[N];
bool is_run(int y) {
	return y<=1582?y%4==0:y%400==0||(y%4==0&&y%100!=0);
}
int find_year(ll x) {
	int l=0,r=N-1,mid;
	while(l<=r) {
		mid=(l+r)/2;
		if(a[mid]<=x)
			l=mid+1;
		else
			r=mid-1;
	}
	return l-1;
}
int rest_year(ll &x) {
	const int Y400 = 146097, Y100 = 36524;
	int y=x/Y400*400;
	x%=Y400;
	y+=x/Y100*100;
	x%=Y100;
	return y;
}
int year_days(ll x) {
	return is_run(x)+365;
}
int main() {
	freopen("julian.in","r",stdin);
	freopen("julian.out","w",stdout);
	a[0]=0;
	for(i=1; i<N; ++i) {
		a[i]=a[i-1]+year_days(i-4713);
		if(i-4712==1583) a[i]-=10;
	}
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%lld",&x);
		int y=find_year(x),m=1;
		if(x>2299160&&y-4712==1582) x+=10;
		x-=a[y];
		y-=4712;
		--x;
		y+=rest_year(x);
		++x;
		while(x>=year_days(y)) x-=year_days(y),++y;
		for(m=1; m<=12; ++m)
			if(x>=Month_Days[m]+(m==2&&is_run(y)))
				x-=Month_Days[m]+(m==2&&is_run(y));
			else break;
		if(y<=0)
			printf("%lld %d %d BC\n",x+1,m,-y+1);
		else
			printf("%lld %d %d\n",x+1,m,y);
	}
	return 0;
}