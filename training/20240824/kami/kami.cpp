#include <cstdio>
#include <cstring>
using namespace std;
const int N = 3e5;
char s[N + 2];
int n;
int main() {
	freopen("kami.in","r",stdin);
	freopen("kami.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	int ans=0,sum=0;
	for(int i=1; i<=n; ++i) {
		if(s[i]!='1') continue;
		for(int j=n-i; j; --j&=n-i)
			ans^=j+sum;
		ans^=sum;
		++sum;
	}
	printf("%d",ans);
	return 0;
}