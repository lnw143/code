#include<cstdio>
#include<queue>
using namespace std;
using ll = long long;
const int N(1e5);
int T,n,a;
priority_queue<int,vector<int>,greater<int>> hp;
ll ans;
int pop() {
	int x=hp.top();
	hp.pop();
	return x;
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(int i=1; i<=n; ++i) {
			scanf("%d",&a);
			hp.push(a);
		}
		ans=0;
		for(int i=1; i<n; ++i) {
			int u=pop(),v=pop();
			ans+=u+v;
			hp.push(u+v);
		}
		while(!hp.empty()) hp.pop();
		printf("%lld\n",ans);
	}
	return 0;
}