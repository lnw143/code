#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
namespace IO {
	static const int BUF = 1<<20;
	static char pbuf[BUF],*p=pbuf,*ch;
	inline void pc(char c) {
		*p++=c;
		if(p-pbuf==BUF) fwrite(pbuf,1,BUF,stdout),p=pbuf;
	}
	inline void flush() {
		fwrite(pbuf,1,p-pbuf,stdout);
		p=pbuf;
	}
	template<typename T> inline void read(T &x) {
		x=0;
		char c=*ch++;
		T f=1;
		for(; c<'0'||c>'9'; c=*ch++) if(c=='-') f=-1;
		for(; c>='0'&&c<='9'; c=*ch++) x=(x<<3)+(x<<1)+(c^48);
		x*=f;
	}
	template<typename T,typename ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	template<typename T> inline void write(T x) {
		if(x<0) {
			pc('-');
			x=-x;
		}
		static char stk[1<<8],*tp;
		tp=stk;
		do *tp++=(x%10)^48; while(x/=10);
		while(tp!=stk) pc(*--tp);
	}
	inline void write(char c) { pc(c); }
	inline void init(const char* filein, const char* fileout) {
		if(*filein) freopen(filein,"r",stdin);
		if(*fileout) freopen(fileout,"w",stdout);
    	ch=(char*)mmap(NULL,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);
	}
	template<typename T,typename ...Args> void write(T x,Args ...args) {
		write(x);
		write(args...);
	}
	struct TMP { ~TMP() { flush(); } } tmp;
};
using IO::read;
using IO::write;
using IO::flush;

int main() {
	IO::init("io.in","io.out");
	int a,b;
	read(a,b);
	write(a+b);
	return 0;
}