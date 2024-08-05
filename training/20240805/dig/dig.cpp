#include <cstdio>
#include <vector>
using namespace std;
const int N = 64;
int n,tot,a[N + 2],tmp[N + 2];
void msort(int l,int r) {
	if(l==r) return ;
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r);
	for(int i=l; i<=r; ++i) {
		int need=r-i+1;
		vector<int> t;
		for(int k=0; k<=need; ++k)
			if(k<=mid-l+1&&need-k<=r-mid) {
				printf("AND %d",need);
				for(int j=mid-k+1; j<=mid; ++j) printf(" %d",a[j]);
				for(int j=r-(need-k)+1; j<=r; ++j) printf(" %d",a[j]);
				putchar('\n');
				t.push_back(++tot);
			}
		printf("OR %d",t.size());
		for(auto j : t) printf(" %d",j);
		putchar('\n');
		tmp[i]=++tot;
	}
	for(int i=l; i<=r; ++i) a[i]=tmp[i];
}
int main() {
	freopen("dig.in","r",stdin);
	freopen("dig.out","w",stdout);
	scanf("%d%*d",&n);
	if(n==0) return printf("END"),0;
	if(n==1) return printf("OR 1 1\nEND"),0;
	if(n==2) return printf("OR 2 1 2\nEND"),0;
	if(n==3) return printf("AND 2 1 2\nAND 2 1 3\nAND 2 2 3\nOR 3 4 5 6\nEND"),0;
	for(int i=1; i<=n; ++i) a[i]=i;
	tot=n;
	msort(1,n);
	printf("AND 1 %d\nEND",a[n/2+1]);
	return 0;
}