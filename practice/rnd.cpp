#include<cstdio>
#include<random>
using namespace std;
mt19937 rnd(random_device{}());
uniform_int_distribution<int> d(1,1000);
int main() {
	printf("%u",d(rnd));
	return 0;
}