#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fo1(i,a,b) for(i=a;i>=b;i--)
#define ll long long 
#define maxlongint 2147483647
#define N 1500
using namespace std;
void read(int &n)
{
	char ch=getchar();
	while(ch==' ' || ch=='\n') ch=getchar();int q=0,w=1;if(ch=='-') {w=-1;ch=getchar();}
	while(ch>='0' && ch<='9' || ch=='-') {q=q*10+ch-48;ch=getchar();}n=q*w;
}
int i,j,m,n,ans,q,w,e,e1,S,T,ans1;
int a[N],B[N*2][2],B0,tl[N],F[N*2][2];
int d1[N];
bool z[N];
void join(int q,int w,int e,int e1)
{
	B0++;
	if(a[q]==0) a[q]=B0;
		else B[tl[q]][0]=B0;
	tl[q]=B0;
	B[B0][0]=0;
	B[B0][1]=w;
	F[B0][0]=e;
	F[B0][1]=e1;
	B0++;
	if(a[q]==0) a[w]=B0;
		else B[tl[w]][0]=B0;
	tl[w]=B0;
	B[B0][0]=0;
	B[B0][1]=q;
	F[B0][0]=0;
	F[B0][1]=-e1;
}
bool OK()
{
	int m1=maxlongint;
	fo(i,1,n)
		if(z[i])
		{
			for(int j=a[i];j;j=B[j][0])
				if(!z[B[j][1]] && F[j][0]) m1=min(m1,d1[B[j][1]]+F[j][1]-d1[i]);
		}
	if(m1==maxlongint) return 0;
	fo(i,1,n)
		if(z[i])
		{
			z[i]=0;
			d1[i]+=m1;
		}
	return 1;
}
int aug(int q,int e)
{
	if(q==T) 
	{
		ans1+=d1[S]*e;
		return e;
	}
	z[q]=1;
	int t,i,w;
	for(i=a[q];i;i=B[i][0])
	{
		w=B[i][1];
		if(!z[w] && d1[w]+F[i][1]==d1[q] && F[i][0])
		{
			t=aug(w,min(e,F[i][0]));
			if(t)
			{
				F[i][0]-=t;
				F[i^1][0]+=t;
				return t;
			}
		}
	}
	return 0;
}
int main()
{
//	freopen("!.in","r",stdin);
//	freopen(".out","w",stdout);
	read(n); read(m); 
	B0=1; S=1; T=n;
	fo(i,1,m)
	{
		read(q); read(w); read(e); read(e1);
		join(q,w,e,e1);
	}
	z[S]=1;
	while(OK())
	{
		while(q=aug(S,maxlongint)) 
		ans+=q,memset(z,0,sizeof(z));
	}
	printf("%d   %d \n",ans,ans1);
	return 0;
}
