	#include<cstdio>
	#include<algorithm>
	using namespace std;
	using db = long double;
	const int N(2e5);
	int n,l,d;
	db f[N + 2],g[N * 2 + 2],s[N * 2 + 2],h[N + 2],sum,ans;
	int main() {
		scanf("%d%d%d",&n,&l,&d);
		sum=g[0]=s[0]=1;
		for(int i=1; i<=n+d; ++i) {
			g[i]=sum/d;
			if(i<l) sum+=g[i];
			if(i>=d&&i-d<l) sum-=g[i-d];
			s[i]=s[i-1]+g[i];
		}
		sum=h[0]=1;
		for(int i=1; i<=n; ++i) {
			h[i]=sum/d;
			sum+=h[i];
			if(i>=d) sum-=h[i-d];
		}
		sum=0;
		for(int i=n; i>=1; --i) {
			f[i]=h[i]*sum/d;
			ans=max(ans+f[i],h[i]*(s[i-1]-s[l-1]));
			sum+=f[i];
			if(i+d<=n) sum-=f[i+d];
		}
		printf("%.15Lf",ans+s[n+d]-s[n]);
		return 0;
	}