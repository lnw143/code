#include<cstdio>
#include<string>
using namespace std;
enum Sign {
	endl, flush
};
namespace FAST_IO {
	bool isgraph(int c) {
		return 33<=c&&c<=126;
	}
	const int MAXSIZE = 1<<20;
	class FastIO {
		private:
		typedef FastIO& Self;
		int ch,sgn,stk[1<<10];
		char buf[MAXSIZE],pbuf[MAXSIZE],*p1,*p2,*pp;
		int getC() {
			if(p1==p2) p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin);
			return (p1==p2?EOF:*p1++);
		}
		void putC(const int c) {
			if(pp-pbuf==MAXSIZE) fwrite(pbuf,1,MAXSIZE,stdout),pp=pbuf;
			*pp++=c;
		}
		Self self() {
			return (*this);
		}
		public:
	#define End return self()
		// Init
		FastIO() : p1(buf),p2(buf),pp(pbuf) {}
		~FastIO() { fwrite(pbuf,1,pp-pbuf,stdout); }
		// Input
		template<typename T> Self operator>>(T &x) { // integer
			x=0;
			sgn=1;
			do {
				ch=getC();
				if(ch=='-') sgn=-1;
			} while(ch<'0'||ch>'9');
			do x=(x<<3)+(x<<1)+(ch^'0'),ch=getC(); while('0'<=ch&&ch<='9');
			x*=sgn;
			End;
		}
		Self operator>>(char &x) { // char
			x=getC();
			End;
		}
		Self operator>>(string &s) { // string
			s="";
			do ch=getC(); while(!isgraph(ch));
			do s+=ch,ch=getC(); while(isgraph(ch));
			End;
		}
		Self operator>>(char* s) { // char*
			do ch=getC(); while(!isgraph(ch));
			do *s++=ch,ch=getC(); while(isgraph(ch));
			*s='\0';
			End;
		}
		Self operator>>(bool &x) { // bool
			int y;
			(*this)>>y;
			x=y;
			End;
		}
		// Output
		template<typename T> Self operator<<(T x) { // integer
			if(x<0) {
				x=-x;
				putC('-');
			}
			int tp=0;
			do stk[++tp]=x%10; while(x/=10);
			do putC(stk[tp]^'0'); while(--tp);
			End;
		}
		Self operator<<(const char x) { // char
			putC(x);
			End;
		}
		Self operator<<(const string s) { // string
			for(auto c : s)	
				putC(c);
			End;
		}
		Self operator<<(const char* s) { // const char*
			while(*s) putC(*s++);
			End;
		}
		Self operator<<(char* s) { // char*
			while(*s) putC(*s++);
			End;
		}
		Self operator<<(const bool x) { // bool
			return (*this)<<(int)x;
		}
		Self operator<<(Sign x) { // else
			switch (x) {
				case endl: putC('\n');break;
				case flush: fflush(stdout);break;
			}
			End;
		}
	#undef End
	} fio;
}
using FAST_IO::fio;
#define cin fio
#define cout fio
int main() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	string x;
	cin>>x;
	cout<<x<<endl;
	return 0;
}