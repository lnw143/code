#include<cstdio>
#define NO return printf("-1"),0
using namespace std;
const int N = 2e5;
int n,i,s,ans;
bool f;
char a[N + 2],b[N + 2];
int main() {
	scanf("%d%s%s",&n,a+1,b+1);
	for(i=1; i<=n; ++i) {
		if(a[i]!=b[i]) {
			if(b[i]=='A') ++s,++ans;
			else {
				if(!f) NO;
				if(s<=0) ++ans;
				else --s;
			}
		}
		f=f||b[i]=='A';
	}
	f=false;
	for(i=n; i>=1; --i) {
		f=f||b[i]=='B';
		if(!f&&b[i]=='A'&&a[i]=='B') NO;
	}
	printf("%d",ans);
	return 0;
}