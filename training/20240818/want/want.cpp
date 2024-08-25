#include <cstdio>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
using namespace std;
const int N = 100;
int main() {
	freopen("table","w",stdout);
	int n=N;
	for(int a=1; a<=n; ++a) {
		for(int b=1; b<=n; ++b) {
			vector<int> v;
			set<vector<int>> st;
			for(int i=1; i<=n; ++i) v.push_back(i);
			queue<vector<int>> q;
			q.push(v);
			st.insert(v);
			while(q.size()) {
				auto v=q.front();
				q.pop();
				auto t=v;
				reverse(t.begin(),t.begin()+a);
				if(!st.count(t)) {
					st.insert(t);
					q.push(t);
				}
				t=v;
				reverse(t.end()-b,t.end());
				if(!st.count(t)) {
					st.insert(t);
					q.push(t);
				}
			}
			printf("%4d",st.size());
		}
		printf("\n");
	}
	return 0;
}