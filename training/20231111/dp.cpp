#include <cstdio>
#include <cstdlib>
#include <windows.h>
#define ll long long
ll pos;
int main() {
	while(true) {
		printf("%lld", ++pos);
		system("ex_rd.exe");
		printf("开始");
		system("experiment.exe");
		printf("结束");
		system("ext.exe");
		if(system("fc experiment.out experiment.ans")) {
			MessageBox(0, "wrong answer", "wrong answer", 0);
			return 0;
		}
		if(pos == 10000) {
			MessageBox(0, "10000组AC", "10000组AC", 0);
		}
	}
}
