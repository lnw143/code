#include<cstdio>
#include<set>
#include<map>
using namespace std;
using ll = long long;
using si = set<int>;
const int N(2e5);
int n,a,i,zero;
ll ans;
map<si,int> mp;
void insert(int x) {
	if(x==0) {
		ans+=i-1;
		++zero;
		return ;
	}
	si p;
	for(int i=2; i*i<=x; ++i) {
		int t=0;
		while(x%i==0) x/=i,t^=1;
		if(t) p.insert(i);
	}
	if(x>1) p.insert(x);
	ans+=zero+mp[p]++;
}
int main() {
	scanf("%d",&n);
	for(i=1; i<=n; ++i) {
		scanf("%d",&a);
		insert(a);
	}
	printf("%lld",ans);
	return 0;
}