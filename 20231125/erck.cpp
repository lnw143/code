#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int main() {
	while(true) {
		system("errnd.exe > er.in");
		int s=clock();
		system("er.exe < er.in > er.out");
		int e=clock();
		printf("%.3lf\n",double(e-s)/CLOCKS_PER_SEC);
//		system("erbf.exe < er.in > er.bf");
//		if(system("fc er.bf er.out"))
//			break;
	}
	return 0;
}
