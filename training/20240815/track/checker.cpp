#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;
#define N 1005
struct node{
	int x,y;
	node(int X=0,int Y=0){x=X,y=Y;}
}b[N];
int T,n,a[N];
bool mp[N][N];
void gg(int x){
	printf("%d\n",20-T);
	quitf(_wa,"Wrong Answer. Error id: %d",x),exit(0);
}
void work(int x,int y){
	if(mp[x][y])gg(1);
	mp[x][y]=1;
}
void cover(node x,node y){
	if(x.x==y.x){
		if(x.y<y.y){
			for(int i=x.y;i<y.y;i++)
				work(x.x,i);
		}
		else if(x.y>y.y){
			for(int i=x.y;i>y.y;i--)
				work(x.x,i);
		}
		else gg(2);
	}
	else if(x.y==y.y){
		if(x.x<y.x){
			for(int i=x.x;i<y.x;i++)
				work(i,x.y);
		}
		else if(x.x>y.x){
			for(int i=x.x;i>y.x;i--)
				work(i,x.y);
		}
		else gg(3);
	}
	else gg(4);
}
int dir(node x,node y,node z){
	if(x.x==y.x){
		if(y.y!=z.y)gg(5);
		if(x.y<y.y){
			if(y.x<z.x)return 1;
			else return 0;
		}
		else{
			if(y.x<z.x)return 0;
			else return 1;
		}
	}
	else{
		if(y.x!=z.x)gg(6);
		if(x.x<y.x){
			if(y.y<z.y)return 0;
			else return 1;
		}
		else{
			if(y.y<z.y)return 1;
			return 0;
		}
	}
}
signed main(signed argc,char*argv[]){
	registerTestlibCmd(argc,argv);
	T=inf.readInt(1,20);
	while(T--){
		memset(mp,0,sizeof(mp));
		n=inf.readInt(1,1000),inf.readEoln();
		for(int i=1;i<=n;i++){
			char x=inf.readChar();
			ensure(x=='L'||x=='R');
			a[i]=(x=='L'?0:1);
		}
		int ms=ouf.readInt(-1,1000),ns=ans.readInt(0,1);
		if(ns==0&&ms!=-1)gg(7);
		if(ns==0&&ms==-1)continue;
		if(ns==1&&ms==-1)gg(8);
		b[0]=node(ms,ouf.readInt(0,1000)),b[n+1]=b[0];
		for(int i=1;i<=n;i++)
			b[i].x=ouf.readInt(0,1000),b[i].y=ouf.readInt(0,1000);
		for(int i=0;i<=n;i++)
			cover(b[i],b[i+1]);
		for(int i=1;i<=n;i++)
			if(dir(b[i-1],b[i],b[i+1])!=a[i])gg(9);
	}
	quitf(_ok,"Correct!");
	return 0;
}