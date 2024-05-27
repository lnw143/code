#include<cstdio>
using namespace std;
const int N = 1e2 + 2;
int n,s,k,a,b,i,sum;
int main() {
	scanf("%d%d%d",&n,&s,&k);
	for(i=1; i<=n; ++i) {
		scanf("%d%d",&a,&b);
		sum+=a*b;
	}
	printf("%d",sum>=s?sum:sum+k);
	return 0;
}