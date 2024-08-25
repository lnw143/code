#include<bits/stdc++.h>
const int BUF_SIZ=1<<18;
char ibuf[BUF_SIZ],*iS=ibuf,*iT=ibuf;
#define getchar() (iS==iT&&(iT=(iS=ibuf)+fread(ibuf,1,BUF_SIZ,stdin)),iS==iT?EOF:*iS++)
template <typename _Tp>void read(_Tp &x){
	char ch(getchar());bool f(false);while(!isdigit(ch))f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();while(isdigit(ch))x=x*10+(ch&15),ch=getchar();
	if(f)x=-x;
}
template <typename _Tp,typename... Args>void read(_Tp &t,Args &...args){read(t);read(args...);}
typedef unsigned long long ull;
int n,q;
struct MY_GENERATOR{
	int type;ull seed;
	inline ull nextInt(){
		ull z=(seed+=0x9E37793B5F4A7C15ULL);
		z=(z^(z>>30))*0xBE99136D1CE4E5B9ULL;
		z=(z^(z>>27))*0x94A749BB033BD1FBULL;
		return z^(z>>31);
	}
	int get(){return nextInt()%998244352+1;}
	inline void get(int lastans,int &l,int &r){
		if(type==2){
			if(!type)lastans=0;
			l=((1+(nextInt()>>33))^lastans)%n+1;
			r=((1+(nextInt()>>33))^lastans)%n+1;
			if(l>r)std::swap(l,r);
		}
		else{
			read(l),read(r);
			if(type)l^=lastans,r^=lastans;
		}
	}
}gen;
using namespace std;
template<int N,int logN,class _Tp,_Tp max(_Tp,_Tp)> struct RMQ {
	int n,m,B;
	_Tp a[N + 2],pre[N + 2],suf[N + 2],st[logN][N/logN + 2];
	unsigned long long sta[N + 2];
	inline int belong(int p) {
		return (p-1)/B+1;
	}
	inline int pos(int p) {
		return (p-1)%B;
	}
	void init(int len,_Tp *_a) {
		n=len;
		B=1.5*log2(n);
		if(B<1) B=1;
		for(int i=1; i<=n; ++i) a[i]=_a[i];
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
const int N = 3e6 + 5, logN = 22;
int a[N + 5],p[N + 5];
namespace solution {
	using ll = long long;
	const int P = 998244353;
	namespace fastmod {
		typedef unsigned long long u64;
		typedef __uint128_t u128;
		const int m = P;
		const u64 b = ((u128)1 << 64) / m;
		int reduce(u64 a) {
			u64 q = ((u128)a * b) >> 64;
			int r = a - q * m;
			return r < m ? r : r - m;
		}
	}
	using fastmod::reduce;
	ll qpow(ll a,ll n) {
		ll x=1;
		for(; n; n>>=1,a=reduce(a*a)) if(n&1) x=reduce(x*a);
		return x;
	}
	int b[N + 2],fac[N + 2],ifac[N + 2];
	int pos[N + 2],node[N + 2];
	int myMax(int x,int y) {
		return x>y?x:y;
	}
	RMQ<N,logN,int,myMax> rmax;
	namespace gsegtree {
		const int S = N << 1;
		int tot,s[S + 2],t[S + 2],ls[S + 2],rs[S + 2],fa[S + 2];
		int build(int l,int r) {
			int u=++tot;
			if(l==r) {
				node[l]=u;
				s[u]=a[l];
				t[u]=b[l];
				return u;
			}
			int mid=pos[rmax.query(l,r-1)];
			ls[u]=build(l,mid);
			rs[u]=build(mid+1,r);
			fa[ls[u]]=fa[rs[u]]=u;
			s[u]=reduce((ll)s[ls[u]]*t[rs[u]]);
			t[u]=reduce((ll)t[ls[u]]*s[rs[u]]);
			return u;
		}
		const int M = N << 2;
		int cnt,euler[M + 2],pos[S + 2],dep[S + 2],sta[S + 2];
		int f[S + 2][2][2];
		void dfs(int u) {
			if(!fa[u])
				f[u][0][0]=f[u][0][1]=f[u][1][0]=f[u][1][1]=1;
			else if(u==rs[fa[u]]) {
				f[u][0][0]=f[fa[u]][0][1]*t[ls[fa[u]]];
				f[u][0][1]=f[fa[u]][0][0]*s[ls[fa[u]]];
				
			}
			euler[++cnt]=u;
			pos[u]=cnt;
			if(ls[u]) {
				dep[ls[u]]=dep[u]+1;
				dfs(ls[u]);
				sta[ls[u]]=sta[u];
				euler[++cnt]=u;
			}
			if(rs[u]) {
				dep[rs[u]]=dep[u]+1;
				dfs(rs[u]);
				sta[rs[u]]=sta[u]^1;
				euler[++cnt]=u;
			}
		}
		int eulerMax(int x,int y) {
			return pos[x]<pos[y]?x:y;
		}
		RMQ<M,logN+2,int,eulerMax> eSeq;
		void init() {
			dfs(1);
			eSeq.init(cnt,euler);
		}
		int lca(int x,int y) {
			int l=pos[x],r=pos[y];
			if(l>r) swap(l,r);
			return eSeq.query(l,r);
		}
	}
	void init() {
		fac[0]=1;
		for(int i=1; i<=n+1; ++i) fac[i]=reduce((ll)fac[i-1]*a[i]);
		ifac[n+1]=qpow(fac[n+1],P-2);
		for(int i=n; i>=1; --i) ifac[i]=reduce((ll)ifac[i+1]*a[i+1]);
		for(int i=1; i<=n; ++i) b[i]=reduce((ll)fac[i-1]*ifac[i]);
		for(int i=1; i<=n; ++i) pos[p[i]]=i;
		rmax.init(n,p);
		gsegtree::build(0,n+2);
		gsegtree::init();
	}
	int solve(int l,int r) {
		using namespace gsegtree;
		int x=node[l-1],y=node[r+2];
		
	}
}
int main(){
	freopen("fraction.in","r",stdin);
	freopen("fraction.out","w",stdout);
	read(n),read(q),read(gen.type),read(gen.seed);
	for(int i=1;i<=n+1;++i) a[i]=gen.get();
	for(int i=1;i<=n;++i) read(p[i]);
	solution::init();
	int l,r,lastans=0;
	ull final_ans=0;
	for(int t=1;t<=q;++t){
		gen.get(lastans,l,r);
		int ansnow=solution::solve(l,r);
		lastans=ansnow;
		final_ans^=1ull*t*ansnow;
	}
	printf("%llu\n",final_ans);
	return 0;
}