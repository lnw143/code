#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
int t,e,b;
int main() {
	while(true) {
		printf("%d",++t);
		system("ho_rd.exe");
		b=clock();
		system("holiday.exe");
		e=clock();
		if(system("fc holiday.ans holiday.out"))
			break;
		printf("%dms\n",e-b);
	}
	return 0;
}