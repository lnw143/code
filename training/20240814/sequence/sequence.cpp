#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
const int N = 4e5, logN = 19;
int n,c[N + 5];
ll s[N + 5];
int m;
gp_hash_table<ll,int> mp;
int v[N + 2];
int anc[logN][N + 5];
int q;
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
		freopen(filein,"r",stdin);
		freopen(fileout,"w",stdout);
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
	IO::init("sequence.in","sequence.out");
	read(n);
	for(int i=1; i<=n; ++i) read(c[i]),s[i]=s[i-1]+c[i];
	for(int i=0; i<=n; ++i) {
		if(!mp[s[i]]) mp[s[i]]=++m;
		s[i]=mp[s[i]];
	}
	for(int i=1; i<=m; ++i) v[i]=-1;
	for(int i=0; i<=n+1; ++i) anc[0][i]=n+1;
	for(int i=0,maxn=-1,p; i<=n; ++i) {
		p=v[s[i]];
		v[s[i]]=i;
		if(maxn<p) {
			maxn=p;
			anc[0][p]=i;
		}
	}
	for(int i=n; i>=0; --i) anc[0][i]=min(anc[0][i],anc[0][i+1]);
	for(int j=1; j<logN; ++j)
		for(int i=0; i<=n+1; ++i)
			anc[j][i]=anc[j-1][anc[j-1][i]];
	read(q);
	for(int i=1,l,r,k; i<=q; ++i) {
		read(l,r);
		--l;
		k=0;
		for(int j=logN-1; ~j; --j)
			if(anc[j][l]<=r)
				l=anc[j][l],
				k|=1<<j;
		write(k,'\n');
	}
	return 0;
}