#include<cstdio>
#include<random>
#include<cmath>
#include<ctime>
using namespace std;
mt19937_64 rnd(time(NULL));
template<typename T> T rd(T l, T r) {
	return uniform_int_distribution<T>(l,r)(rnd);
}
long long n;
int main() {
	freopen("data1\\20.in","w",stdout);
	n=rd(1000000000ll,1000000000000000000ll);
	printf("%lld",n);
	fclose(stdout);
	freopen("data1\\20.out","w",stdout);
	printf("%lld",2*(n-(1ll<<(int)log2(n)))+1);
	return 0;
}