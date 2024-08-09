#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e6;
int n,p[N + 2];
string a,b;
int solve() {
	int res=0;
	string s=b+'#'+a;
	for(int i=1; i<s.size(); ++i) {
		int j=p[i-1];
		while(j>0&&s[j]!=s[i]) j=p[j-1];
		if(s[j]==s[i]) ++j;
		p[i]=j;
		if(p[i]==b.size()) ++res;
	}
	return res;
}
int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	freopen("classic.in","r",stdin);
	freopen("classic.out","w",stdout);
	cin>>a>>b>>n;
	for(int i=1; i<=n; ++i) {
		int op;
		cin>>op;
		if(op==5) cout<<solve()<<'\n';
		else {
			char c;
			cin>>c;
			--op;
			string &s=(op&2?b:a);
			s.insert((op&1?s.end():s.begin()),c);
		}
	}
	return 0;
}