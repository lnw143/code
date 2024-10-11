#include <cstdio>
#include <cctype>
#include <string>
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
	inline void read(char *p) {
		char c=*ch++;
		for(; !isgraph(c); c=*ch++);
		for(; isgraph(c); c=*ch++) *p++=c;
		*p='\0';
	}
	inline void read(std::string& s) {
		s.clear();
		char c=*ch++;
		for(; !isgraph(c); c=*ch++);
		for(; isgraph(c); c=*ch++) s+=c;
	}
	template<typename T,typename ...Args> void read(T &x,Args &...args) {
		read(x);
		read(args...);
	}
	template<typename T> inline void write(const T &y) {
		T x=y;
		if(x<0) {
			pc('-');
			x=-x;
		}
		static char stk[1<<8],*tp;
		tp=stk;
		do *tp++=(x%10)^48; while(x/=10);
		while(tp!=stk) pc(*--tp);
	}
	inline void write(const char &c) { pc(c); }
	inline void write(const std::string &s) {
		for(auto i : s) pc(i);
	}
	inline void write(const char *p) {
		for(; *p; ++p) pc(*p);
	}
	inline void write(char *p) {
		write(static_cast<const char*>(p));
	}
	template<typename T,typename ...Args> void write(const T &x,const Args &...args) {
		write(x);
		write(args...);
	}
	inline void init(const char* filein, const char* fileout) {
		if(filein!=nullptr) freopen(filein,"r",stdin);
		if(fileout!=nullptr) freopen(fileout,"w",stdout);
    	ch=(char*)mmap(NULL,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);
	}
	struct TMP { ~TMP() { flush(); } } tmp;
};
using IO::read;
using IO::write;
using IO::flush;

int main() {
	IO::init(nullptr,nullptr);
	int a,b;
	read(a,b);
	write(a+b,'\n');
	// std::string s,t;
	char s[100],t[100];
	read(s,t);
	write(s,' ',t,'\n');
	return 0;
}