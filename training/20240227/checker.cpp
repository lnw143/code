#include"testlib.h"

using namespace std;

const int N=205;
int inG[N][N],curG[N][N],n,m;
int readAns(InStream &S){
	string Res=S.readString();
	// cout<<"Res = "<<Res<<" n,m = "<<n<<" "<<m<<endl;
	if(Res=="No")return -1;
	if(Res!="No"&&Res!="Yes")S.quitf(_wa,"???");
	for(int i=1;i<=m+1;i++)for(int j=i+1;j<=m+1;j++)curG[i][j]=curG[j][i]=S.readInt(1,m);
	S.readEoln();
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){
		if(inG[i][j]!=curG[i][j]){
			S.quitf(_wa,
			"Color of edge (%d,%d) should be %d , not %d.\n"
			,i,j,inG[i][j],curG[i][j]);
		}
	}
	for(int i=1;i<=m+1;i++){
		vector<int>vis(m+1);
		for(int j=1;j<=m+1;j++)if(i!=j)vis[curG[i][j]]++;
		for(int j=1;j<=m;j++)if(vis[j]>=2)S.quitf(_wa,"node = %d Color = %d\n",i,j);
	}
	return 1;
}
int main(int argc,char **argv){
	registerTestlibCmd(argc,argv);
	int T=inf.readInt();
	for(int t=1;t<=T;t++){
		// cout<<"t = "<<t<<endl;
		n=inf.readInt(),m=inf.readInt();
		// cout<<"n,m = "<<n<<" "<<m<<endl;
		for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)inG[i][j]=inG[j][i]=inf.readInt(1,m);
		int jans=readAns(ans),pans=readAns(ouf);
		if(jans!=pans){
			if(jans==1&&pans==-1)quitf(_wa,"Wrong answer!");
			if(jans==-1&&pans==1)quitf(_fail,">_<");
		}
	}
	quitf(_ok,"Right output!\n");
	return 0;
}