#include <cstdio>
#include <vector>
using namespace std;
const int logN = 16;
int tot=3;
struct Num {
	int id;
	Num(int id):id(id) {}
	Num(const Num& t):id(t.id) {}
} a(1),b(2);
Num operator|(const Num& a,const Num& b) {
	printf("| %d %d %d\n",a.id,b.id,++tot);
	return tot;
}
Num operator&(const Num& a,const Num& b) {
	printf("& %d %d %d\n",a.id,b.id,++tot);
	return tot;
}
Num operator^(const Num& a,const Num& b) {
	printf("^ %d %d %d\n",a.id,b.id,++tot);
	return tot;
}
Num operator>>(const Num& a,int b) {
	printf(">> %d %d %d\n",a.id,b,++tot);
	return tot;
}
Num operator<<(const Num& a,int b) {
	printf("<< %d %d %d\n",a.id,b,++tot);
	return tot;
}
Num operator~(const Num& a) {
	printf("~ %d %d\n",a.id,++tot);
	return tot;
}
int main() {
	freopen("cnt.out","w",stdout);
	printf("92\n");
	Num x=a|b,y=a&b;
	vector<Num> s{x};
	for(int i=0; i<=logN; ++i) s.push_back(s.back()&(s.back()>>(1<<i)));
	for(int i=logN; i>=0; --i) {
		y=y|((s[i]&y)<<(1<<i));
		if(i==0) y=y&x;
	}
	Num ans=a^b^(y<<1);
	printf("<< %d 0 3\n",ans.id);
	return 0;
}