#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
namespace GenHelper
{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_()
    {
    b=((z1<<6)^z1)>>13;
    z1=((z1&4294967294U)<<18)^b;
    b=((z2<<2)^z2)>>27;
    z2=((z2&4294967288U)<<2)^b;
    b=((z3<<13)^z3)>>21;
    z3=((z3&4294967280U)<<7)^b;
    b=((z4<<3)^z4)>>12;
    z4=((z4&4294967168U)<<13)^b;
    return (z1^z2^z3^z4);
    }
}
void srand(unsigned x)
{using namespace GenHelper;
z1=x; z2=(~x)^0x233333333U; z3=x^0x1234598766U; z4=(~x)+51;}
int read()
{
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}
const int N = 2e7;
int n,m,a[N + 2];
unsigned int s;
template<int N,int logN,class _Tp,_Tp max(_Tp,_Tp)> struct RMQ {
	_Tp pre[N + 2],suf[N + 2],st[logN][N/logN + 2];
	int n,m,B;
	unsigned long long sta[N + 2];
	inline int belong(int p) {
		return (p-1)/B+1;
	}
	inline int pos(int p) {
		return (p-1)%B;
	}
	void init(int len) {
		n=len;
		B=1.5*log2(n);
		if(B<1) B=1;
		for(int i=1; i<=n; ++i)
			if(pos(i)==0)
				pre[i]=a[i];
			else
				pre[i]=max(pre[i-1],a[i]);
		suf[n]=a[n];
		for(int i=n-1; i>=1; --i)
			if(i%B==0)
				suf[i]=a[i];
			else
				suf[i]=max(suf[i+1],a[i]);
		m=belong(n);
		for(int i=1; i<=m; ++i)
			st[0][i]=suf[(i-1)*B+1];
		for(int j=1; j<logN; ++j)
			for(int i=1; i+(1<<j)-1<=m; ++i)
				st[j][i]=max(st[j-1][i],st[j-1][i+(1<<(j-1))]);
		static int stk[N + 2];
		for(int i=1,tp=0; i<=n; ++i) {
			if(pos(i)==0) tp=0;
			else sta[i]=sta[i-1];
			unsigned long long &s=sta[i];
			while(tp&&max(a[i],a[stk[tp]])==a[i])
				s^=1llu<<pos(stk[tp]),--tp;
			stk[++tp]=i;
			s|=1llu<<pos(i);
		}
	}
	_Tp queryBlock(int l,int r) {
		int k=__lg(r-l+1);
		return max(st[k][l],st[k][r-(1<<k)+1]);
	}
	_Tp query(int l,int r) {
		int x=belong(l),y=belong(r);
		if(x<y) {
			_Tp res=max(suf[l],pre[r]);
			if(x+1<y) res=max(res,queryBlock(x+1,y-1));
			return res;
		} else
			return a[l+__builtin_ctzll(sta[r]>>pos(l))];
	}
};
int myMax(int a,int b) {
    return a<b?b:a;
}
char sss;
RMQ<N,25,int,myMax> R;
char ttt;
int main() {
	scanf("%d%d%u",&n,&m,&s);
	srand(s);
	for(int i=1; i<=n; ++i) a[i]=read();
	R.init(n);
	unsigned long long sum=0;
	for(int i=1; i<=m; ++i) {
		int l=read()%n+1,r=read()%n+1;
		if(l>r) swap(l,r);
		sum+=R.query(l,r);
	}
	printf("%llu",sum);
	return 0;
}