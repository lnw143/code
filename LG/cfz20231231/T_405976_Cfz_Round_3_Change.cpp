#include<cstdio>
using namespace std;
int T,p,a,b,c;
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d%d",&p,&a,&b,&c);
		if(c==0) printf("Yes\n");
		else if(b==0) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}