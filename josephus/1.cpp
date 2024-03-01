#include<cstdio>
#include<cmath>
using namespace std;
long long n;
int main() {
	scanf("%lld",&n);
	printf("%lld",2*(n-(1ll<<(int)log2(n)))+1);
	return 0;
}