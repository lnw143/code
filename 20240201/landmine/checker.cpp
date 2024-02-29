#include<cstdio>
#include<cstdlib>
#include<chrono>
using namespace std;
const int TOT = 1000;
int sum;
int main() {
	system("@echo off");
	system("g++ data.cpp -o data.exe -std=c++14");
	system("g++ simulated_annealing.cpp -o simulated_annealing.exe -std=c++14");
	system("g++ bf.cpp -o bf.exe -std=c++14");
	for(int i=1; i<=TOT; ++i) {
		system("data.exe");
		system("bf.exe");
		auto start_time=chrono::steady_clock::now();
		system("simulated_annealing.exe");
		printf("%d:\n",i);
		if(!system("fc landmine.out landmine.ans")) ++sum;
		printf("running time:%.2lfms\n",chrono::duration<double,milli>(chrono::steady_clock::now()-start_time).count());
	}
	printf("%.2lf%%\n",(double)sum/TOT*1e2);
	return 0;
}