#include<cstdio>
#include<cmath>
using namespace std;
int x,y;
int main() {
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	scanf("%d%d",&x,&y);
	printf("%.0Lf",floorl(sqrtl(x*x+y*y)*2)+1);
	return 0;
}