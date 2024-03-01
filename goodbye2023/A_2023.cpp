#include<cstdio>
using namespace std;
const int N = 5 + 2;
int T,n,k,i,a,s;
bool flag;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&k);
		s=2023;
		flag=true;
		for(i=1; i<=n; ++i) {
			scanf("%d",&a);
			if(s%a)
				flag=false;
			else
				s/=a;
		}
		if(!flag) {
			printf("NO\n");
			continue;
		}
		printf("YES\n%d",s);
		for(i=1; i<k; ++i)
			printf(" 1");
		putchar('\n');
	}
	return 0;
}