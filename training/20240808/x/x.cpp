#include <cstdio>
#include <cmath>
using namespace std;
const int N = 1e5, BUF = 1 << 18;
char pbuf[BUF],*p=pbuf;
inline char gc() {
	static char buf[BUF],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,BUF,stdin),l==r)?-1:*l++;
}
inline void pc(char c) {
	if(p-pbuf==BUF) fwrite(pbuf,1,BUF,stdout),p=pbuf;
	*p++=c;
}
inline int read() {
	int x=0;
	char c=gc();
	for(; c<'0'||c>'9'; c=gc());
	for(; c>='0'&&c<='9'; c=gc()) x=(x<<1)+(x<<3)+(c^48);
	return x;
}
inline void write(int x) {
	static int stk[1 << 7];
	int tp=0;
	do stk[++tp]=(x%10)^48; while(x/=10);
	while(tp) pc(stk[tp--]);
}
inline void Yes() {
	pc('Y'),pc('e'),pc('s'),pc('\n');
}
inline void No() {
	pc('N'),pc('o'),pc('\n');
}
struct TMP { ~TMP() { fwrite(pbuf,1,p-pbuf,stdout); } } tmp;
int n,m,k,cnt,a[N + 2],b[N + 2];
inline int sgn(int x) {
	return x<0?-1:(x>0);
}
inline void print(int x,int y) {
	write(x),pc(' '),write(y),pc('\n');
}
int main() {
	freopen("x.in","r",stdin);
	freopen("x.out","w",stdout);
	int T=read();
	while(T--) {
		n=read(),k=read(),cnt=m=0;
		for(int i=1; i<=n; ++i) a[i]=sgn(read()-k);
		for(int i=1; i<=n; ++i)
			if(i==n||a[i]!=-1||a[i+1]!=-1)
				b[++m]=a[i];
		int neg=0,zer=0,pos=0;
		for(int i=1; i<=m; ++i)
			++(b[i]<0?neg:b[i]>0?pos:zer);
		if(neg*2>=m) {
			No();
			continue;
		}
		Yes();
		for(int i=n-1; i>=1; --i)
			if(a[i]==-1&&a[i+1]==-1)
				print(i,i+1);
		for(int i=m-1; i>=1&&pos>m/2; --i)
			if(b[i]>0)
				print(i,i+1),--pos,--m;
		if(1<m) print(1,m);
	}
	return 0;
}