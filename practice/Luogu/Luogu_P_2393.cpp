#include <cstdio>
#include <cmath>
using ll = __int128_t;
using ld = long double;
char s[1<<16],*t=s;
int main() {
	ll sum=0;
	ld x=0;
	while(scanf("%Lf",&x)==1) sum+=roundl(1e6l*x);
	if(sum<0) putchar('-'),sum=-sum;
	sum=(sum+5)/10;
	for(int i=1; i<=5; ++i,sum/=10) *t++=sum%10+'0';
	*t++='.';
	do {
		*t++=sum%10+'0';
		sum/=10;
	} while(sum);
	for(char *i=t-1; i>=s; --i) putchar(*i);
	return 0;
}