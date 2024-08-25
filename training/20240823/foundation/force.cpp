#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5;
int n,q,a[N + 2];
char s[N + 2];
int main() {
	freopen("foundation.in","r",stdin);
	freopen("foundation.out","w",stdout);
	scanf("%d%d%s",&n,&q,s+1);
	for(int i=1; i<=n; ++i) a[i]=s[i]=='('?1:-1;
	for(int i=1; i<=q; ++i) {
		static char op[10];
		int l,r;
		scanf("%s%d%d",op,&l,&r);
		switch(*op) {
			case 'R': {
				char c;
				scanf(" %c",&c);
				for(int j=l; j<=r; ++j) a[j]=c=='('?1:-1;
				break;
			}
			case 'S': {
				reverse(a+l,a+r+1);
				break;
			}
			case 'I': {
				for(int j=l; j<=r; ++j) a[j]=-a[j];
				break;
			}
			case 'Q': {
				int sum=0,minn=0;
				for(int j=l; j<=r; ++j) {
					sum+=a[j];
					minn=min(minn,sum);
				}
				printf("%d\n",sum/2+(1-minn)/2*2);
				break;
			}
		}
	}
	return 0;
}