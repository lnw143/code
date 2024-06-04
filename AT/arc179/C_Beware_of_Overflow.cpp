#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int query(char op,int x,int y) {
	printf("%c %d %d\n",op,x,y);
	fflush(stdout);
	int p;
	scanf("%d",&p);
	return p;
}
int main() {
	scanf("%d",&n);
	vector<int> v;
	for(int i=1; i<=n; ++i) v.push_back(i);
	stable_sort(v.begin(),v.end(),[](int x,int y) { return query('?',x,y); });
	while(v.size()>1) {
		int p=query('+',v.front(),v.back());
		v=vector<int>(v.begin()+1,v.end()-1);
		v.insert(lower_bound(v.begin(),v.end(),p,[](int x,int y) { return query('?',x,y); }),p);
	}
	printf("!\n");
	fflush(stdout);
	return 0;
}