#include<cstdio>
#include<cstdlib>
using namespace std;
int main() {
	while(true) {
		system("data.exe > .in");
		system("std.exe < .in > .ans");
		system("Luogu_P_2455.exe < .in > .out");
		if(system("fc .out .ans")) {
			return 0;
		}
	}
	return 0;
}