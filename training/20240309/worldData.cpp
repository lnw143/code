#include<cstdio>
#include<random>
#include<bitset>
using namespace std;
const int N(1e3);
mt19937 rnd(random_device{}());
int T,n,m;
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
			if(x<1||y<1||x>n||y>m) return;
			(a[x][y]?--sum:++sum);
			a[x][y].flip();
		}
};
Mat01 o,x;
int randint(int l,int r) {
	return uniform_int_distribution<int>(l,r)(rnd);
}
Mat01 trans(Mat01 x) {
	switch(rnd()&3) {
		case 0: {
			int u=randint(1,n);
			for(int i=1; i<=n; ++i)
				x.flip(u,i);
			break;
		}
		case 1: {
			int u=randint(1,n);
			for(int i=1; i<=n; ++i)
				x.flip(i,u);
			break;
		}
		case 2: {
			int u=randint(1-n,n-1);
			for(int i=1; i<=n; ++i)
				x.flip(i,i-u);
			break;
		}
		case 3: {
			int u=randint(2,2*n);
			for(int i=1; i<=n; ++i)
				x.flip(i,u-i);
			break;
		}
	}
	return x;
}
int main() {
	freopen("world.in","w",stdout);
	T=20;
	printf("%d\n",T);
	for(int id=1; id<=T; ++id) {
		n=m=250;
		printf("%d %d\n",n,m);
		x=o;
		for(int i=1; i<=n; ++i)
			x=trans(x);
		for(int i=1; i<=n; ++i,putchar('\n'))
			for(int j=1; j<=m; ++j)
				putchar(x[i][j]?'1':'0');
		for(int i=1; i<=n; ++i,putchar('\n'))
			for(int j=1; j<=m; ++j)
				putchar('0');
	}
	return 0;
}