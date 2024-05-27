#include<atcoder/all>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace atcoder;
using namespace std;
long long n;
void dfs(long long x) {
	if(!x) return ;
	dfs(x/5);
	printf("%d",x%5*2);
}
int main() {
	scanf("%lld",&n);
	if(n==1) putchar('0');
	else dfs(n-1);
	return 0;
}