#include<cstdio>
#include<random>
#include<chrono>
using namespace std;
using ll = long long;
const int N = 16, M = N * (N + 1) / 2;
mt19937 rnd(random_device{}());
int p,b,n,m,a[N + 2],l[M + 2],r[M + 2];
int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
bool check() {
	for(int i=1; i<=n; ++i)
		a[i]=randint(0,p-1);
	for(int i=1; i<=m; ++i)
		if(a[l[i]]==a[r[i]+1])
			return false;
	return true;
}
auto start_time=chrono::steady_clock::now();
double running_time() {
	return chrono::duration<double>(chrono::steady_clock::now()-start_time).count();
}
int main() {
	scanf("%d%d%d%d",&p,&b,&n,&m);
	for(int i=1; i<=m; ++i)
		scanf("%d%d",&l[i],&r[i]);
	while(running_time()<1.99)
		if(check()) {
			printf("Yes");
			return 0;
		}
	printf("No");
	return 0;
}