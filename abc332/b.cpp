#include<cstdio>
using namespace std;
int g,m,a,b,c,k,i;
int main() {
	scanf("%d%d%d",&k,&g,&m);
	for(i=1; i<=k; ++i) {
		if(a==g) a=0;
		else if(b==0) b=m;
		else {
			c=g-a<b?g-a:b;
			a+=c;
			b-=c;
		}
	}
	printf("%d %d",a,b);
	return 0;
}