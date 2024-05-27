#include<cstdio>
#include<random>
#define R r(1,2000)
using namespace std;
random_device rd;
mt19937 rnd(rd());
template<typename T>T r(T a,T b) {
	uniform_int_distribution<T> d(a,b);
	return d(rnd);
}
int n=2,m=100,k=50,i;
int main() {
//	freopen("er.in","w",stdout);
	printf("%d %d %d\n",n,m,k);
	printf("%d %d\n1 %d\n",R,R,R);
	for(i=1; i<m; ++i)
		printf("%d %d\n",r(2,3),R);
	return 0;
}
