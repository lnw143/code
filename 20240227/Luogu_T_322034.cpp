#include<cstdio>
const int BUF(1<<23);
char buf[BUF],*p1,*p2;
int main() {
	do {
		p2=(p1=buf)+fread(buf,1,BUF,stdin);
		fwrite(buf,1,p2-p1,stdout);
	} while(p1!=p2);
	return 0;
}