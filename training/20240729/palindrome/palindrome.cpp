#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 5e5, logN = 20, inf = 1e7;
int n,q,d0[N + 2],d1[N + 2];
char s[N + 2];
struct ST {
	int st[logN][N + 2];
	void init(int n,int *a) {
		for(int i=1; i<=n; ++i) st[0][i]=a[i];
		for(int j=1; j<logN; ++j)
			for(int i=1; i<=n-(1<<j)+1; ++i)
				st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	}
	int query(int l,int r) {
		int k=__lg(r-l+1);
		return max(st[k][l],st[k][r-(1<<k)+1]);
	}
} f0,f1;
int main() {
	freopen("palindrome.in","r",stdin);
	freopen("palindrome.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int l=0,r=-1,i=1; i<=n; ++i) {
		int p=r<i?1:min(d1[l+r-i],r-i+1);
		while(i+p<=n&&1<=i-p&&s[i-p]==s[i+p]) ++p;
		d1[i]=p;
		if(i+p>r) l=i-p+1,r=i+p-1;
	}
	for(int l=0,r=-1,i=1; i<=n; ++i) {
		int p=r<i?0:min(d0[l+r-i+1],r-i+1);
		while(i+p<=n&&1<=i-p-1&&s[i-p-1]==s[i+p]) ++p;
		d0[i]=p;
		if(i+p-1>r) l=i-p,r=i+p-1;
	}
	f0.init(n,d0);
	f1.init(n,d1);
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int x,y,ans=1;
		scanf("%d%d",&x,&y);
		{
			int l=1,r=(y-x)/2+1;
			while(l<=r) {
				int mid=(l+r)/2;
				if(f1.query(x+mid-1,y-mid+1)>=mid) l=mid+1;
				else r=mid-1;
			}
			ans=max(ans,(l-1)*2-1);
		}
		{
			int l=1,r=(y-x+1)/2;
			while(l<=r) {
				int mid=(l+r)/2;
				if(f0.query(x+mid,y-mid+1)>=mid) l=mid+1;
				else r=mid-1;
			}
			ans=max(ans,(l-1)*2);
		}
		printf("%d\n",ans);
	}
	return 0;
}