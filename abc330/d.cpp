#include<cstdio>
#define fn(x) for(x=1; x<=n; ++x)
using namespace std;
const int N = 2e3 + 2;
int n,i,j,k,c[N],sum,f;
long long ans;
char a[N][N];
int main() {
	scanf("%d",&n);
	fn(i) {
		scanf("%s",a[i]+1);
		fn(j)
		if(a[i][j]=='o')
			++c[j];
	}
	fn(i) {
		f=sum=0;
		fn(j)
		if(a[i][j]=='o') {
			ans+=sum+(c[j]-1)*f;
			sum+=c[j]-1;
			++f;
		}
	}
	printf("%lld",ans);
	return 0;
}