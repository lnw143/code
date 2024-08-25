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
const int N=3000005;
int a[N],p[N];
int main(){
	read(n),read(q),read(gen.type),read(gen.seed);
	for(int i=0;i<=n;++i) a[i]=gen.get();
	for(int i=1;i<=n;++i) read(p[i]);
	
	/*
	Write your code here
	*/
	
	int l,r,lastans=0;
	ull final_ans=0;
	for(int t=1;t<=q;++t){
		gen.get(lastans,l,r);
		int ansnow=0;
		
		/*
		Write your code here
		*/
		
		lastans=ansnow;
		final_ans^=1ull*t*ansnow;
	}
	printf("%llu\n",final_ans);
	return 0;
}
