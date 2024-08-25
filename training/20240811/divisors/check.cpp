#include <cstdio>
#include <cstdlib>
using namespace std;
int main() {
	for(int i=3; i<=2500; ++i) {
		freopen("divisors.in","w",stdout);
		printf("%d\n",i);
		fclose(stdout);
		printf("checking %d\n",i);
		system("divisors.exe");
		if(system("checker.exe")) {
			printf("WA on %d\n",i);
		}
	}
	return 0;
}