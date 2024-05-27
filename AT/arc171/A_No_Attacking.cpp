#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a,b,c;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&n,&a,&b);
		if(a>n) {
			printf("No\n");
			continue;
		}
		c=n-a;
		printf((min(c,a)+(a<=c?(c-a+1)/2:0))*c>=b?"Yes\n":"No\n");
	}
	return 0;
}