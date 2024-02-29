#include<cstdio>
#include<vector>
#include<string>
using namespace std;
using ll = long long;
using llu = long long unsigned;
using vi = vector<int>;
using vvi = vector<vi>;
int n,m,q,i,j;
vector<string> s;
void readStr(string &s) {
	s="";
	char ch=getchar();
	while(ch<'a'||ch>'z') ch=getchar();
	do {
		s+=ch;

		ch=getchar();
	} while(ch>='a'&&ch<='z');
}
int kmp(string s1,string s2) {
	string s=s1+'#'+s2;
	vi p(s.size(), 0);+
	
	for(int i=1; i<s.size(); ++i) {
		int j=p[i-1];
		while(j>0&&s[j]!=s[i]) j=p[j-1];
		if(s[j]==s[i]) ++j;
		p[i]=j;
	}
	return p[s.size()-1];
}
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	scanf("%d%d",&n,&q);
	s.resize(n + 2);
	for(i=1; i<=n; ++i) {
		readStr(s[i]);
		m+=s[i].size()-1;
	}
	for(i=1; i<=q; ++i) {
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",kmp(s[y],s[x]));
	}
	return 0;
}