#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e4 + 2, M = 2e4 + 2, K = 1e2 + 2;
int n,m,k,i,j,u,hs,ls[N],e[M],nx[M],a[M],dis[N][K];
bool bz[N][K];
struct Node {
	int x,t,d;
	bool operator<(const Node q) const {
		return d<q.d;
	}
	Node(int a=0,int b=0,int c=0):x(a),t(b),d(c) {}
} hp[N * K * 10];
template<typename T>void swap(T &a,T &b) {
	T c=a;
	a=b;
	b=c;
}
void put(int x,int t,int d) {
	Node p(x,t,d);
	hp[++hs]=p;
	int k=hs;
	while(k>1&&hp[k]<hp[k/2]) {
		swap(hp[k],hp[k/2]);
		k/=2;
	}
	return ;
}
Node pop() {
	Node ret=hp[1];
	hp[1]=hp[hs--];
	int k=1;
	while(k*2<=hs&&hp[k*2]<hp[k]||k*2+1<=hs&&hp[k*2+1]<hp[k]) {
		int kk=k*2;
		if(kk+1<=hs&&hp[kk+1]<hp[kk]) ++kk;
		swap(hp[k],hp[kk]);
		k=kk;
	}
	return ret;
}
int main() {
	freopen("bus.in","r",stdin);
	freopen("bus.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(i=1; i<=m; ++i) {
		scanf("%d%d%d",&u,&e[i],&a[i]);
		nx[i]=ls[u];
		ls[u]=i;
	}
	memset(dis,0x7f,sizeof(dis));
	dis[1][0]=0;
	put(1,0,0);
	for(i=1; i<=n*k&&hs>0; ++i) {
		Node r=pop();
		while(hs>0&&dis[r.x][r.t]!=r.d) r=pop();
		if(dis[r.x][r.t]!=r.d) break;
		int x=r.x,t=r.t,d=r.d;
		bz[x][t]=true;
		for(j=ls[x]; j; j=nx[j]) 
			if(!bz[e[j]][(t+1)%k]){
				int upd=(t+d*k>=a[j]?d:d+(a[j]-t-d*k+k-1)/k)+(t+1==k);
				if(dis[e[j]][(t+1)%k]>upd) {
					dis[e[j]][(t+1)%k]=upd;
					put(e[j],(t+1)%k,upd);
				}
			}
	}
	printf("%d",dis[n][0]<0x7f7f7f7f?dis[n][0]*k:-1);
	return 0;
}
