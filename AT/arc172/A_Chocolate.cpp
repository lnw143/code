#include<cstdio>
using namespace std;
using ll = long long;
const int N(25);
int h,w,n,a[N + 2];
ll s;
int main() {
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1; i<=n; ++i) {
		int x;
		scanf("%d",&x);
		++a[x];
	}
	for(int i=N; i>=0; --i) {
		s=s*4+a[i];
		if(s>(ll)(h>>i)*(w>>i)) {
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}