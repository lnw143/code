#include<cstdio>
#include<algorithm>
#include<random>
using namespace std;
using ll = long long;
const int N = 1e6, M = 10;
int n,s[N + 2],k;
ll a[N + 2],d[N + 2],ans=1;
mt19937 rnd(random_device{}());
int randint(int l,int r) { return uniform_int_distribution<int>(l,r)(rnd); }
void split(ll x) {
	k=0;
	auto put = [&](ll t) {
		d[++k]=t;
		s[k]=0;
	};
	for(ll i=1; i*i<=x; ++i)
		if(x%i==0) {
			put(i);
			if(i*i!=x) put(x/i);
		}
	sort(d+1,d+k+1);
}
ll gcd(ll a,ll b) {
	return b?gcd(b,a%b):a;
}
inline char gc() {
	static char buf[1<<16],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<16,stdin),l==r)?-1:*l++;
}
template<class T> void read(T& x) {
	x=0;
	char c=gc();
	while(c<'0'||c>'9') c=gc();
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<3)+(x<<1)+(c^48);
}
int main() {
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int id=0; id<M; ++id) {
		const ll u=a[randint(1,n)];
		split(u);
		for(int i=1; i<=n; ++i)
			++s[lower_bound(d+1,d+k+1,gcd(u,a[i]))-d];
		for(int i=1; i<k; ++i)
			for(int j=i+1; j<=k; ++j)
				if(d[j]%d[i]==0)
					s[i]+=s[j];
		for(int i=k; i>=1; --i)
			if(s[i]*2>=n) {
				ans=max(ans,d[i]);
				break;
			}
	}
	printf("%lld",ans);
	return 0;
}