#include<iostream>
#include<set>
#include<queue>
#include<string>
#include<utility>
#include<functional>
using namespace std;
using pSI = pair<string,int>;
const int N = 3e3;
int n,ans[N + 2];
char s[N + 2];

int main() {
	scanf("%d%s",&n,s+1);
	for(int k=1; k<=n; ++k)
		for(int l=1; l<=k; ++l) {
			set<int> p;
			priority_queue<pSI,vector<pSI>,greater<pSI>> pq;
			for(int i=0; i<k-l; ++i)
				pq.emplace(s.substr(i,l),i);
			for(int i=0; i<=n-k; ++i) {
				pq.emplace(s.substr(i+k-l,l),i+k-l);
				while(pq.top().second<i) pq.pop();
				p.insert(pq.top().second);
			}
			++ans[p.size()];
		}
	for(int i=1; i<=n; ++i)
		printf("%d\n",ans[i]);
	return 0;
}