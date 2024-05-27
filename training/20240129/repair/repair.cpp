#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int N = 18, P = 1e9 + 7;
int n,a[N + 2],k,i;
bool bz[N + 2];
ll ans,maxa;
void dfs(int x,int A,int B,int s) {
	if(x>n) {
		if(A>maxa) {
			maxa=A;
			ans=0;
		}
		if(A==maxa) ans=(ans+s)%P;
		return ;
	}
	for(int i=1; i<=n; ++i)
		if(!bz[i]) {
			bz[i]=true;
			if(x==1) dfs(x+1,a[i],0,0);
			else {
				int a_=max(A,a[i])+(A==a[i]),b_=B<<1|1;
				dfs(x+1,a_,b_,(s+(ll)k*a_%P+B)%P);
			}
			bz[i]=false;
		}
}
int main() {
	freopen("repair.in","r",stdin);
	freopen("repair.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	if(n<=10) dfs(1,0,0,0);
	else {
		return 233;
	}
	printf("%lld %lld",maxa,ans);
	return 0;
}