#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
const int N = 4e3;
int n,k,s[N + 2];
char c[N + 2];
map<int,int> mp;
long long ans;	
int main() {
	scanf("%d%s",&k,c+1);
	n=strlen(c+1);
	for(int i=1; i<=n; ++i)
		s[i]=s[i-1]+c[i]-'0';
	for(int i=1; i<=n; ++i)
		for(int j=i; j<=n; ++j)
			++mp[s[j]-s[i-1]];
	for(int i=1; i<=n; ++i)
		for(int j=i; j<=n; ++j)
			if(s[j]!=s[i-1]&&k%(s[j]-s[i-1])==0) {
				ans+=mp[k/(s[j]-s[i-1])];
			} else if(s[j]==s[i-1]&&k==0) {
				ans+=(n+1ll)*n/2;
			}
	printf("%lld\n",ans);
	return 0;
}