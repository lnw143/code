#include<cstdio>
#include<cstdlib>
int main() {
	while(true) {
		system("ddata.exe");
		system("dbf.exe");
		system("rnd.exe");
		if(system("fc .out .ans")) {
			break;
		}
	}
	return 0;
}