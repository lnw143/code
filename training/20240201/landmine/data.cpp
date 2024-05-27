#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
uniform_int_distribution<int> dist(-1000,1000);
int n=1e8,i;
int main() {
	freopen("happy","w",stdout);
	for(i=1; i<=n; ++i)
		printf("%d\n",114514);
	return 0;
}