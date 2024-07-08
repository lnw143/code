#include <cstdio>
#include <vector>
#include <cassert>
#include <set>
#include <algorithm>
using namespace std;
const int N = 7e4;
int n,x[N + 2],y[N + 2],ans;
int main() {
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&x[i]);
	for(int i=1; i<=n; ++i) scanf("%d",&y[i]);
	sort(x+1,x+n+1);
	for(int i=2; i<=n; ++i) x[i]-=x[1];
	ans-=x[1];
	x[1]=0;
	sort(y+1,y+n+1);
	for(int i=2; i<=n; ++i) y[i]-=y[1];
	ans+=y[1];
	y[1]=0;
	for(int i=1; i<=n; ++i) {
		const int t=y[i];
		set<int> st;
		vector<int> v;
		for(int j=1; j<=n; ++j) st.insert(y[j]);
		for(int j=1; j<=n; ++j)
			if(st.count(x[j]+t))
				st.erase(x[j]+t);
			else
				v.push_back(x[j]);
		if(v.empty()) {
			printf("%d %d\n",ans+t,ans+t);
			return 0;
		}
		auto it=st.begin();
		const int s=*it-v.front();
		bool f=true;
		for(auto u : v)
			if(*it!=u+s) {
				f=false;
				break;
			} else
				++it;
		if(f) {
			printf("%d %d\n",ans+t,ans+s);
			return 0;
		}
	}
	assert(false);
	return 0;
}