#include<cstdio>
using namespace std;
int n,i,a,l,sum;
int main() {
	scanf("%d%d",&n,&l);
	for(i=1; i<=n; ++i) {
		scanf("%d",&a);
		sum+=a>=l;
	}
	printf("%d",sum);
	return 0;
}