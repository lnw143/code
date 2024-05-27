#include<cstdio>
#include<bitset>
#include<string>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
const int N(3e3);
int n;
bitset<N + 2> a[N + 2];
char s[N + 2];
long long ans;
int main() {
	scanf("%d",&n);
	rep(i,1,n) {
		scanf("%s",s);
		a[i]=bitset<N + 2>(s,n);
	}
	rep(i,1,n)
		rep(j,i+1,n)
			if(a[i][n-j])
				ans+=(a[i]&a[j]).count();
	printf("%lld",ans/3);
	return 0;
}