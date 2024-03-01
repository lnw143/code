#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int N(1e6);
int n,f[N + 2],ans=1;
char s[N + 2];
int main() {
	scanf("%d%s",&n,s+1);
	for(int i=2; i<=n; ++i)
		f[i]=f[i-1]+(s[i]==s[1]?1:-1);
	for(int i=n-1; i>=1; --i)
		if(s[i+1]!=s[1]&&(f[i]==-1||f[i]==0||f[i]==1))
			++ans;
	
	printf("%d",ans);
	return 0;
}