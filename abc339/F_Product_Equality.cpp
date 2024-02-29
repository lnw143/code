#include<cstdio>
#include<random>
#include<vector>
#include<map>
using namespace std;
using ll = unsigned long long;
using vl = vector<ll>;
mt19937_64 rnd(random_device{}());
uniform_int_distribution<ll> dist(1,1e18);
const int N = 1e3;
int n,i,j,sum;
vl P;
struct Num {
	vl x;
	bool operator<(const Num t ) const {
		for(int i=0; i<P.size(); ++i)
			if(x[i]!=t.x[i])
				return x[i]<t.x[i];
		return false;
	}
	Num operator*(const Num t) const {
		Num y;
		y.x.resize(P.size());
		for(int i=0; i<P.size(); ++i)
			y.x[i]=(unsigned __int128)x[i]*t.x[i]%P[i];
		return y;
	}
	void read() {
		x.resize(P.size());
		char ch=getchar();
		while(ch<'0'||ch>'9') ch=getchar();
		while(ch>='0'&&ch<='9') {
			ch^='0';
			for(int i=0; i<P.size(); ++i)
				x[i]=(x[i]*10+ch)%P[i];
			ch=getchar();
		}
	}
} a[N + 2];
map<Num,int> ans;
int main() {
	P.push_back(998344353);
	P.push_back(1e9+7);
	P.push_back(1145141919810ll);
	for(i=1; i<=3; ++i)
		P.push_back(dist(rnd));
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
		a[i].read();
	for(i=1; i<=n; ++i)
		for(j=1; j<=n; ++j)
			++ans[a[i]*a[j]];
	for(i=1; i<=n; ++i)
		sum+=ans[a[i]];
	printf("%d",sum);
	return 0;
}