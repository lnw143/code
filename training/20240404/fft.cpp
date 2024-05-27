#include<cstdio>
#include<map>
using namespace std;
using ll = long long;
const int N = 5e5, P = 998244353;
int n,m,inv[N + 2];
map<int,map<int,int>> mp;
int solve(int n,int m) {
	if(!n||!m) return 0;
	if(n<m) n^=m^=n^=m;
	if(mp.count(n)&&mp[n].count(m)) return mp[n][m];
	const int k=n+m;
	return mp[n][m]=((ll)inv[k]*n%P*solve(n-1,m)+(ll)inv[k]%P*m%P*(solve(n,m-1)+1)%P)%P;
}
int main() {
	// freopen("fft.in","r",stdin);
	// freopen("fft.out","w",stdout);
	scanf("%d%d",&n,&m);
	inv[1]=1;
	for(int i=2; i<=N; ++i)
		inv[i]=ll(P-(P/i))*inv[P%i]%P;
	int ans=solve(n,m);
	printf("%d\n",ans);
	for(int i=1; i<=100; ++i)
		printf("%d/%d\n",(ll)ans*i%P,i);
	return 0;
}