#include<cstdio>
using namespace std;
int n,l,r,i,a;
int main() {
	scanf("%d%d%d",&n,&l,&r);
	for(i=1; i<=n; ++i) {
		scanf("%d",&a);
		printf("%d ",a<l?l:a>r?r:a);
	}
	return 0;
}