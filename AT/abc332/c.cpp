#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e3 + 2;
int n,m,i,a,b,ans;
char s[N];
int main() {
	scanf("%d%d%s",&n,&m,s+1);
	for(i=1; i<=n; ++i) {
		if(s[i]=='0')
			a=b=0;
		else if(s[i]=='1')
			++a;
		else if(s[i]=='2')
			++b;
		ans=max(ans,max(0,a-m)+b);
	}
	printf("%d",ans);
	return 0;
}