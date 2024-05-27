#include<cstdio>
#include<vector>
using namespace std;
using vi = vector<int>;
#define push push_back
#define pop pop_back
#define top(v) (*(v).rbegin())
#define bot(v) (*(v).begin())
const int N(1e5);
int T,n,p,tot,f[N * 5 + 2][2];
vi s[3];
vi read(int n) {
	vi a;
	for(int i=1; i<=n; ++i) {
		static int x;
		scanf("%1d",&x);
		if(i==1||x!=top(a)) a.push(x);
	}
	return a;
}
void work(int x,int y) {
	++tot;
	f[tot][0]=x+1;
	f[tot][1]=y+1;
	if(s[y].size()==0||top(s[y])!=top(s[x])) s[y].push(top(s[x]));
	s[x].pop();
}
void solve(int x,int y) {
	work(x,2);
	while(s[x].size()>1) {
		// if(s[x].size()==1) break;
		work(x,y);
		work(x,2);
	}
	if(s[x].size()==0) {
		if(top(s[y])==bot(s[y])) {
			while(s[y].size()>1) {
				work(y,x);
				work(y,2);
			}
			work(x,y);
			work(2,x);
		} else {
			work(y,x);
			while(s[y].size()>1) {
				work(y,2);
				work(y,x);
			}
			work(2,y);
		}
	} else {
		if(bot(s[x])==bot(s[y])) work(x,2);
		work(y,x);
		while(s[y].size()>1) {
			work(y,2);
			work(y,x);
		}
		work(2,y);
	}
}
int main() {
	scanf("%d",&T);
	for(; T>0; --T) {
		scanf("%d%d",&n,&p);
		s[0]=read(n);
		s[1]=read(n);
		s[2].clear();
		tot=0;
		if(top(s[0])==top(s[1])) {
			if(s[0].size()>1) work(0,1);
			else work(1,0);
		}
		if(s[0].size()>1) solve(0,1);
		else if(s[1].size()>1) solve(1,0);
		printf("%d\n",tot);
		if(p>1) for(int i=1; i<=tot; ++i)
				printf("%d %d\n",f[i][0],f[i][1]);
	}
	return 0;
}