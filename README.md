#### 存放个人训练代码，资料

```cpp
// lnw143's template
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cctype>
#include<random>
#include<algorithm>
#define rep(i,l,r) for(int i(l),i##END(r); i<=i##END; ++i)
#define per(i,l,r) for(int i(r),i##END(l); i>=i##END; --i)
using namespace std;
using ll = long long;
namespace FAST_IO {
	const int BUF(1<<20);
	char buf[BUF],*p1=buf,*p2=buf;
	char pbuf[BUF],*p=pbuf;
	char gc() {
		return p1==p2?(p2=(p1=buf)+fread(buf,1,BUF,stdin),p1==p2?EOF:*p1++):*p1++;
	}
	void pc(char c) {
		*p++=c;
		if(p-pbuf==BUF) fwrite(pbuf,1,BUF,stdout),p=pbuf;
	}
	void flush() {
		fwrite(pbuf,1,p-pbuf,stdout);
		p=pbuf;
	}
	template<typename T> void read(T &x) {
		x=0;
		static char c;
		T f=1;
		do {
			c=gc();
			if(c=='-') f=-f;
		} while(!isdigit(c));
		do {
			x=(x<<3)+(x<<1)+(c^48);
			c=gc();
		} while(isdigit(c));
		x*=f;
	}
	template<typename T,typename ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	template<typename T> void write(T x) {
		if(x<0) {
			pc('-');
			x=-x;
		}
		static char stk[1<<8],*tp;
		tp=stk;
		do *tp++=(x%10)^48; while(x/=10);
		while(tp!=stk) pc(*--tp);
	}
	void write(char c) { pc(c); }
	template<typename T,typename ...Args> void write(T &x,Args &...args) {
		write(x);
		write(args...);
	}
};
using FAST_IO::read;
using FAST_IO::write;
using FAST_IO::flush;
int main() {
	// read(...);
	return 0;
}
```