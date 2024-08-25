#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2500;
int n,a[N + 2],fa[N + 2],pow3[10];
bool bz[N + 2];
vector<int> ans,oth;
int lcm(int x,int y) {
	return x/__gcd(x,y)*y;
}
int main() {
	freopen("divisors.in","r",stdin);
	freopen("divisors.out","w",stdout);
	scanf("%d",&n);
	pow3[0]=1;
	for(int i=1; pow3[i-1]<=n; ++i) pow3[i]=pow3[i-1]*3;
	for(int i=1; i<=n; ++i)
		if(i%2!=0&&i%3!=0) {
			if(i*2>n) {
				oth.push_back(i);
				continue;
			}
			vector<int> now;
			for(int j=0; (i<<j)<=n; ++j) {
				int k=0; 
				while((i<<j)*pow3[k]<=n) ++k;
				--k;
				now.push_back((i<<j)*pow3[k]);
			}
			ans.push_back(now.front());
			for(int i=0; i+1<now.size(); ++i)
				ans.push_back(lcm(now[i],now[i+1]));
			ans.push_back(now.back());
		}
	int cnt=ans.size();
	for(auto i : ans)
		printf("%d ",i);
	if(oth.size()==1) {
		cnt+=2;
		printf("%d %d ",oth[0],oth[0]);
	} else {
		for(int i=0; i<oth.size(); ++i) {
			if(i) printf("%d ",oth[i]/__gcd(oth[i],oth[i-1])*oth[i-1]),++cnt;
			printf("%d ",oth[i]),++cnt;
		}
	}
	for(int i=cnt+1; i<=n; ++i) printf("1 ");
	putchar('\n');
	for(int i=1; i<n; ++i)
		printf("%d %d\n",i,i+1);
	return 0;
}