#include<iostream>
#include<cstring>
using namespace std;
const int N(1e2), inf(0x3f3f3f3f);
int n,f[N + 2],g[N + 2];
string t;
int main() {
	cin>>t>>n;
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1; i<=n; ++i) {
		int m;
		cin>>m;
		memset(g,0x3f,sizeof(g));
		for(int j=1; j<=m; ++j) {
			string s;
			cin>>s;
			try {
				for(int k=0; k<=t.size()-s.size(); ++k)
					if(t.substr(k,s.size())==s)
						g[k+s.size()]=min(g[k+s.size()],f[k]+1);
			} catch(const std::exception& e) {
				cerr << e.what() << '\n';
			}
		}
		for(int i=1; i<=t.size(); ++i)
			f[i]=min(f[i],g[i]);
	}
	printf("%d",f[t.size()]==inf?-1:f[t.size()]);
	return 0;
}