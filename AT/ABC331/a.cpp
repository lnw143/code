#include<cstdio>
using namespace std;
int a,b,y,m,d;
int main() {
	scanf("%d%d%d%d%d",&a,&b,&y,&m,&d);
	++d;
	if(d>b) {
		d=1,++m;
		if(m>a)
			m=1,++y;
	}
	printf("%d %d %d",y,m,d);
	return 0;
}