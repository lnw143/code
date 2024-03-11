#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
using ll = long long;
int T;
ll n;
bool check(ll x) {
	while(x) {
		if(x/10%10==x%10) return false;
		x/=10;
	}
	return true;
}
vector<int> split(ll x) {
	vector<int> a;
	do {
		a.push_back(x%10);
	} while(x/=10);
	reverse(a.begin(),a.end());
	return a;
}
ll p(ll x) {
	vector<int> a=split(x);
	ll y=0,x_=x;
	for(int i=0; i<a.size()-1; ++i) {
		if(i) y=y*10+a[i-1];
		int z=a[i]-1+(a[i]<=a[i+1]);
		if(i+2<a.size()&&a[i+1]-1+(a[i+1]<=a[i+2])<=z) --z;
		x_-=(y+1)*z;
	}
	return x_;
}
int main() {
	for(ll i=1; i<=1e6; ++i)
		if(check(i))
			printf("%lld %lld %lld\n",i,i-(++n),i-p(i));
		else 
			printf("!%lld\n",i);
	return 0;
	scanf("%d",&T);
	while(T--) {
		scanf("%lld",&n);
	}
	return 0;
}