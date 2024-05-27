#include<cstdio>
#include<vector>
using namespace std;
const int N = 3e3;
int n,i;
vector<int> e[N + 2];
int main() {
	scanf("%d",&n);
	for(i=1; i<n; ++i) {
		static int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
	}

	return 0;
}