#include<cstdio>
using namespace std;
long long n,m,p;
int main() {
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&p);
	printf("%lld",n*m%p);
	return 0;
}