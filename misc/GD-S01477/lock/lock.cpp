#include<cstdio>
using namespace std;
const int N = 8 + 2;
int n,i,j,ans;
struct Lock {
	int p[5];
	void read() {
		for(int i=0; i<5; ++i)
			scanf("%d",&p[i]);
	}
	bool check(const Lock x) const {
		int r=-1,p1=-1,p2=-1;
		for(int i=0; i<5; ++i)
			if(p[i]!=x.p[i]) {
				int e=(p[i]-x.p[i]+10)%10;
				if(r!=-1&&r!=e) return false;
				r=e;
				if(p1==-1) p1=i;
				else if(p2==-1)  p2=i;
				else return false;
			}
		return r!=-1&&(p2==-1||p1+1==p2);
	}
	Lock(int x=0) {
		for(int i=4; i>=0; --i) {
			p[i]=x%10;
			x/=10;
		}
	}
} a[N],b;
int main() {
	freopen("lock.in","r",stdin);
	freopen("lock.out","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		a[i].read();
	for(i=0; i<100000; ++i) {
		b=Lock(i);
		for(j=1; j<=n; ++j)
			if(!a[j].check(b))
				break;
		if(j>n) ++ans;
	}
	printf("%d",ans);
	return 0;
}
