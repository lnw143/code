#include <cstdio>
using namespace std;
using uint = unsigned int;
inline char gc() {
	static char buf[1<<20],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,1<<20,stdin),l==r)?-1:*l++;
}
void read(int &x) {
	x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(ch&15);
}
void read(char *p) {
	char c=gc();
	for(; c<'a'||c>'z'; c=gc());
	for(; c>='a'&&c<='z'; c=gc()) *p++=c;
	*p='\0';
}
const int T = 1500, S = 1e5, Q = 1e6;
int n,m,q;
int main() {
	read(n),read(m),read(q);
	
	return 0;
}