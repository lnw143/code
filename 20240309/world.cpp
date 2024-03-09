#include<cstdio>
#include<random>
#include<bitset>
using namespace std;
const int N(1e3);
mt19937 rnd(random_device{}());
int T,n,m;
char s[N + 2];
struct Mat01 {
	private:
		bitset<N + 2> a[N + 2];
	public:
		int sum=0;
		bitset<N + 2>& operator [](int x) {
			return a[x];
		}
		void upd() {
			sum=0;
			for(int i=1; i<=n; ++i)
				sum+=a[i].count();
		}
		void flip(int x,int y) {
			a[x][y].flip();
			(a[x][y]?++sum:--sum);
		}
};
Mat01 x,a;
int read01() {
	switch(getchar()) {
		case '0': return 0;
		case '1': return 1;
		default: return read01();
	}
}
int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
Mat01 trans(Mat01 x) {
	switch(rnd()&3) {
		case 0: {
			int u=randint(1,n);
			for(int i=1; i<=m; ++i)
				x.flip(u,i);
			break;
		}
		case 1: {
			int u=randint(1,m);
			for(int i=1; i<=n; ++i)
				x.flip(i,u);
			break;
		}
		case 2: {
			int u=randint(1-m,n-1);
			for(int i=max(u+1,1); i<=u+m&&i<=n; ++i)
				x.flip(i,i-u);
			break;
		}
		case 3: {
			int u=randint(2,2*n);
			for(int i=max(u-m,1); i<u&&i<=n; ++i)
				x.flip(i,u-i);
			break;
		}
	}
	return x;
}
bool simAnneal() {
	int temp=1e4;
	while(temp--) {
		if(x.sum==0) break;
		Mat01 y=trans(x);
		if(y.sum<x.sum) x=y;
	}
	return x.sum==0;
}
int main() {
	freopen("world.in","r",stdin);
	freopen("world.out","w",stdout);
	scanf("%d",&T);
	for(int id=1; id<=T; ++id) {
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				a[i][j]=read01();
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				if(read01())
					a[i][j].flip();
		a.upd();
		x=a;
		printf(simAnneal()||simAnneal()?"Yes\n":"No\n");
	}
	return 0;
}