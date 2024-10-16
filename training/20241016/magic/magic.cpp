#include <cstdio>
#include <set>
#include <vector>
#include <utility>
#include <string>
#include <cctype>
namespace IO {
	static const int BUF = 1<<20;
	static char pbuf[BUF],*p=pbuf;
	inline char gc() {
		static char buf[BUF],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,BUF,stdin),p1==p2)?-1:*p1++;
	}
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
		char c=gc();
		T f=1;
		for(; c<'0'||c>'9'; c=gc()) if(c=='-') f=-1;
		for(; c>='0'&&c<='9'; c=gc()) x=(x<<3)+(x<<1)+(c^48);
		x*=f;
	}
	inline void read(char& c) { c=gc(); }
	inline void read(char *p) {
		char c=gc();
		for(; !isgraph(c); c=gc());
		for(; isgraph(c); c=gc()) *p++=c;
		*p='\0';
	}
	inline void read(std::string& s) {
		s.clear();
		char c=gc();
		for(; !isgraph(c); c=gc());
		for(; isgraph(c); c=gc()) s+=c;
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
	struct TMP { ~TMP() { flush(); } } tmp;
};
using IO::read;
using IO::write;
using IO::flush;

using namespace std;
const int N = 1e3, K = 6;
int n,m,k,a[N + 2][N + 2];
struct magic {
	int dx,dy;
} s[K + 2];
int main() {
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	int tid,T;
	read(tid);
	read(T);
	while(T--) {
		read(n,m,k);
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j) {
				char c;
				read(c);
				while(c!='0'&&c!='1') read(c);
				a[i][j]=c&1;
			}
		int p1=0,p2=0;
		set<pair<int,int>> st;
		for(int i=1; i<=k; ++i) {
			int t;
			read(t);
			if(t==1) {
				int x,y;
				read(x,y);
				st.emplace(x,y);
			} else {
				int p;
				read(p);
				if(p==1) p1=1;
				else if(p==2) p2=1;
				else st.emplace(2,1);
			}
		}
		k=0;
		for(auto [u,v] : st) {
			if(u==0&&p2) continue;
			if(v==0&&p1) continue;
			s[++k]={u,v};
		}
		if(p1) s[++k]={2,0};
		if(p2) s[++k]={0,2};
		vector<pair<int,int>> f;
		f.emplace_back(0,0);
		for(int i=1; i<=k; ++i) {
			vector<pair<int,int>> g;
			for(auto [x,y] : f)
				g.emplace_back(x+s[i].dx,y+s[i].dy);
			f.insert(f.end(),g.begin(),g.end());
		}
		bool ans=true;
		for(int i=1; i<=n&&ans; ++i)
			for(int j=1; j<=m; ++j) {
				int sum=0,ok=1;
				for(auto [x,y] : f)
					if(i+x<1||i+x>n||j+y<1||j+y>m) {
						ok=0;
						break;
					} else sum^=a[i+x][j+y];
				if(sum&ok) {
					ans=false;
					break;
				}
			}
		write(ans?"Yes\n":"No\n");
	}
	return 0;
}