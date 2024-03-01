#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
char a,b,c,d;
int main() {
	while(a<'A'||a>'Z') a=getchar();
	while(b<'A'||b>'Z') b=getchar();
	while(c<'A'||c>'Z') c=getchar();
	while(d<'A'||d>'Z') d=getchar();
	printf(min(abs(a-b),5-abs(a-b))==min(abs(c-d),5-abs(c-d))?"Yes":"No");
	return 0;
}