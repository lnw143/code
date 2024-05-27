#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
using ll = long long;
const int N = 1e5, M = 7e6;
int n,m,q,u,v,t,w,i,a[N + 2];
char buf[30];
template<typename T>
void read(T &x) {
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^'0');
		ch=getchar();
	}
	return ;
}
template<typename T,typename ...Args>
void read(T &x,Args &...args) {
	read(x);
	read(args...);
}

template<typename T>
void write(T x) {
	int l=0;
	do
		buf[++l]=x%10;
	while(x/=10);
	while(l) putchar(buf[l--]^'0');
	return ;
}
struct Heap {
	int Q[3][M + 2],h[3]= {1,1,1},t[3];
	void push(int x,int y) {
		Q[x][++t[x]]=y;
	}
	int pop() {
		int r=-1;
		for(int i=0; i<3; ++i)
			if((h[i]<=t[i])&&(r==-1||Q[i][h[i]]>Q[r][h[r]]))
				r=i;
		int ret=Q[r][h[r]++];
		return ret+w*q;
	}
	int cut() {
		int r=pop();
		++w;
		push(1,(ll)r*u/v-w*q);
		push(2,r-(ll)r*u/v-w*q);
		return r;
	}
} hp;
int main() {
	freopen("earthworm.in","r",stdin);
	freopen("earthworm.out","w",stdout);
	read(n,m,q,u,v,t);
	for(i=1; i<=n; ++i)
		read(a[i]);
	stable_sort(a+1,a+n+1);
	for(i=n; i>=1; --i)
		hp.push(0,a[i]);
	for(i=1; i<=m; ++i) {
		int r=hp.cut();
		if(i%t==0)
			write(r),putchar(' ');
	}
	putchar('\n');
	for(i=1; i<=n+m; ++i) {
		int r=hp.pop();
		if(i%t==0)
			write(r),putchar(' ');
	}
	return 0;
}