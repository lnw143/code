#include<cstdio>
#include<random>
#include<queue>
using namespace std;
using llu = long long unsigned;
const int N = 8, M = 1e7 + 19, inf = 1 << 30;
const llu P = 131;
int n,m,i,j,ans=inf;
struct Matrix {
	int a[N + 2][N + 2],d;
	llu hash_val() {
		llu r=0;
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				r=r*P+a[i][j];
		return r;
	}
	Matrix turn(bool x,bool y) {
		Matrix r=*(this);
		for(int i=1; i<n; ++i)
			for(int j=1; j<m; ++j)
				r.a[n-i+x][m-j+y]=a[i+x][j+y];
		r.d=d+1;
		return r;
	}
} a,b;
struct Hash {
	llu id[M];
	int v[M];
	bool bz[M];
	int check_hash(llu x) {
		int k=x%M;
		while(bz[k]&&id[k]!=x) ++k%=M;
		return bz[k]?v[k]:inf;
	}
	void put_hash(llu x,int y) {
		int k=x%M;
		while(bz[k]&&id[k]!=x) ++k%=M;
		if(bz[k]) return ;
		bz[k]=true;
		v[k]=y;
		id[k]=x;
	}
} f,g;
queue<Matrix> q;
int main() {
	scanf("%d%d",&n,&m);
	for(i=1; i<=n; ++i)
		for(j=1; j<=m; ++j) {
			scanf("%d",&a.a[i][j]);
			b.a[i][j]=(i-1)*m+j;
		}
	q.push(a);
	f.put_hash(a.hash_val(),a.d);
	while(!q.empty()) {
		Matrix u=q.front();
		q.pop();
		if(u.d==10) continue;
		for(i=0; i<4; ++i) {
			Matrix v=u.turn(i&1,i&2);
			llu h=v.hash_val();
			if(f.check_hash(h)==inf) {
				f.put_hash(h,v.d);
				q.push(v);
			}
		}
	}
	q.push(b);
	g.put_hash(b.hash_val(),b.d);
	while(!q.empty()) {
		Matrix u=q.front();
		q.pop();
		ans=min(ans,u.d+f.check_hash(u.hash_val()));
		if(u.d==10) continue;
		for(i=0; i<4; ++i) {
			Matrix v=u.turn(i&1,i&2);
			llu h=v.hash_val();
			if(g.check_hash(h)==inf) {
				g.put_hash(h,v.d);
				q.push(v);
			}
		}
	}
	printf("%d",ans==inf?-1:ans);
	return 0;
}