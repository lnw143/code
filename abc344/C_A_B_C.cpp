#include<cstdio>
#include<vector>
#include<set>
using namespace std;
int q;
vector<int> a,b,c;
vector<int> read() {
	int n;
	scanf("%d",&n);
	vector<int> a;
	a.resize(n);
	for(int i=0; i<n; ++i)
		scanf("%d",&a[i]);
	return a;
}
int main() {
	a=read(),b=read(),c=read();
	set<int> st;
	for(auto i : a)
		for(auto j : b)
			for(auto k : c)
				st.insert(i+j+k);
	scanf("%d",&q);
	for(int i=1; i<=q; ++i) {
		int x;
		scanf("%d",&x);
		printf(st.find(x)==st.end()?"No\n":"Yes\n");
	}
	return 0;
}