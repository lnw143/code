#include<cstdio>
using namespace std;
const int P = 998244353;
using ll = long long;
ll n;
int q,k,s,t,i,j;
bool in(int x,int y) {
	do {
		if(y%k==x) return true;
		y/=k;
	} while(y);
	return false;
}
int main() {
	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);
	scanf("%lld%d%d",&n,&q,&k);
	for(i=1; i<=1e6; ++i) {
		for(j=1; j<k; ++j)
			if(in(j,i)||in(j,i+j)) {
				printf("%d ",j);
			}
		puts("");
	}
	return 0;
}