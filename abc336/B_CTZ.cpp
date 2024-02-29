#include<atcoder/all>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace atcoder;
using namespace std;
int n,s;
int main() {
	scanf("%d",&n);
	while(n%2==0) n>>=1,++s;
	printf("%d",s);
	return 0;
}