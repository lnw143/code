#include<cstdio>
using namespace std;
int T,a,b,p;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&a,&b,&p);
		if(b-b%p==0) printf("Alice\n");
		else if(a-a%p==0) printf("Bob\n");
		else printf("Lasting Battle\n");
	}
	return 0;
}