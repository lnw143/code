#include<cstdio>
using namespace std;
int n,t1=-1,t2;
int main() {
	freopen("apple.in","r",stdin);
	freopen("apple.out","w",stdout);
	scanf("%d",&n);
	while(n) {
		++t2;
		if(n%3==1&&t1==-1) t1=t2;
		n-=(n+2)/3;
	}
	printf("%d %d",t2,t1);
	return 0;
}
