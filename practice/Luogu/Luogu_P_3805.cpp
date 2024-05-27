#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1.1e7;
int n,d1[N + 2],d2[N + 2];
char s[N + 2];
int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1,l=0,r=-1; i<=n; ++i) {
		int k=i>r?1:min(r-i+1,d1[l+r-i]);
		while(k<i&&i+k<=n&&s[i-k]==s[i+k]) ++k;
		d1[i]=k;
		if(i+k-1>r) r=i+k-1,l=i-k+1;
	}
	
	for(int i=1,l=0,r=-1; i<=n; ++i) {
		int k=i>r?0:min(r-i+1,d2[l+r-i+1]);
		while(1<=i-k-1&&i+k<=n&&s[i-k-1]==s[i+k]) ++k;
		d2[i]=k;
		if(i+k-1>r) r=i+k-1,l=i-k;
	}
	int ans=0;
	for(int i=1; i<=n; ++i)
		ans=max({ans,d2[i]*2,d1[i]*2-1});
	printf("%d",ans);
/*
	for(int i=0; i<=n; ++i)
		s[i*2+1]=-1;
	for(int i=1; i<=n; ++i)
		s[i*2]=t[i];
	n=n*2+1;
	int l=0,r=-1;
	for(int i=1; i<=n; ++i) {
		int k=i>r?1:min(d1[l+r-i],r-i+1);
		while(k<i&&i+k<=n&&s[i-k]==s[i+k]) ++k;
		--k;
		d1[i]=k;
		if(i+k>r) l=i-k,r=i+k;
	}
	int ans=1;
	for(int i=1; i<=n; ++i)
		ans=max(ans,d1[i]);
	printf("%d",ans);
*/
	return 0;
}