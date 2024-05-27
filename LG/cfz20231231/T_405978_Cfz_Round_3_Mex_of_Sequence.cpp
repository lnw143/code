#include<cstdio>
#include<vector>
using namespace std;
using pii = pair<int,int>;
using vii = vector<pii>;
const int N = 1e6 + 2;
int T,n,i,m,a,b[N];
vii v;
vii wk(vii x) {
	vii v;
	int las=-1;
	for(auto i : x) {
		if(i.first>las+1)
			break;
		las=i.first;
	}
	int sum=0,s=0;
	for(auto i : x) {
		if(i.first>las+1) break;
		if(i.second==1) v.push_back(i);
		else s+=i.second;
		sum+=i.second;
	}
	if(n-sum+s) v.push_back(pii(las+1,n-sum+s));
	return v;
}
void print(vii v) {
	for(auto i : v)
		for(int j=1; j<=i.second; ++j)
			printf("%d ",i.first);
	putchar('\n');
}
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(i=0; i<=n+1; ++i)
			b[i]=0;
		for(i=1; i<=n; ++i) {
			scanf("%d",&a);
			++b[a>n?n+1:a];
		}
		v.clear();
		for(i=0; i<=n+1; ++i)
			if(b[i])
				v.push_back(pii(i,b[i]));

		while(m&&v.size()>1) {
			--m;
			v=wk(v);
		}
		// printf("%d\n",m);
		print(v);
	}
	return 0;
}