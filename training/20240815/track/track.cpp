#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <utility>
#define fst first
#define scd second
#define double long double
using namespace std;
const int N = 1e3;
int n;
string s;
double X;
vector<pair<double,double>> res;
inline void insert(int pos,const pair<double,double> p,const pair<double,double> q) {
	res.insert(res.begin()+pos,q);
	res.insert(res.begin()+pos,p);
}
enum Dir {
	U, D, L, R
};
void dfs(string s) {
	if(s.size()==4) {
		X=powl(2,n);
		if(s.front()=='L') res={{0,0}, {X,0}, {X,X}, {0,X}};
		else res={{0,0}, {0,X}, {X,X}, {X,0}};
		return ;
	}
	int i=0;
	while(i+1<s.size()&&s[i]==s[i+1]) ++i;
	char c=s[i];
	string t=s;
	t.erase(t.begin()+i,t.begin()+i+2);
	dfs(t);
	Dir dir;
	const int len = res.size();
	i%=len;
	int j=(i+len-1)%len;
	if(res[j].fst==res[i].fst) {
		if(res[j].scd<res[i].scd) dir=U;
		else dir=D;
	} else {
		if(res[j].fst<res[i].fst) dir=R;
		else dir=L;
	}
	X/=2;
	auto [x,y]=res[i];
	if(c=='R') {
		switch(dir) {
			case L: {
				res[i].scd+=X;
				insert(i,make_pair(x+X,y),make_pair(x+X,y+X));
				break;
			}
			case R: {
				res[i].scd-=X;
				insert(i,make_pair(x-X,y),make_pair(x-X,y-X));
				break;
			}
			case U: {
				res[i].fst+=X;
				insert(i,make_pair(x,y-X),make_pair(x+X,y-X));
				break;
			}
			case D: {
				res[i].fst-=X;
				insert(i,make_pair(x,y+X),make_pair(x-X,y+X));
				break;
			}
		}
	} else {
		switch(dir) {
			case L: {
				res[i].scd-=X;
				insert(i,make_pair(x+X,y),make_pair(x+X,y-X));
				break;
			}
			case R: {
				res[i].scd+=X;
				insert(i,make_pair(x-X,y),make_pair(x-X,y+X));
				break;
			}
			case U: {
				res[i].fst-=X;
				insert(i,make_pair(x,y-X),make_pair(x-X,y-X));
				break;
			}
			case D: {
				res[i].fst+=X;
				insert(i,make_pair(x,y+X),make_pair(x+X,y+X));
				break;
			}
		}
	}
}
int main() {
	freopen("track.in","r",stdin);
	freopen("track.out","w",stdout);
	int T;
	cin>>T;
	while(T--) {
		cin>>n>>s;
		int sl=count(s.begin(),s.end(),'L'),sr=s.size()-sl;
		int delta=abs(sl-sr);
		if(delta<3||5<delta) {
			cout<<"-1\n";
			continue;
		}
		if(delta!=4) s+=(delta==5)^(sl<sr)?'R':'L';
		s.insert(s.begin(),s.back());
		s.pop_back();
		dfs(s);
		auto ans=res;
		if(n%2==0) {
			ans.push_back(ans.front());
			ans.erase(ans.begin());
			auto [sx,sy]=ans.front();
			auto [ex,ey]=ans.back();
			ans.insert(ans.begin(),make_pair(ex/2+sx/2,ey/2+sy/2));
		}
		vector<pair<int,int>> p;
		{
			vector<double> a,b;
			for(auto [i,j] : ans) a.push_back(i),b.push_back(j);
			sort(a.begin(),a.end());
			sort(b.begin(),b.end());
			a.erase(unique(a.begin(),a.end()),a.end());
			b.erase(unique(b.begin(),b.end()),b.end());
			for(auto [i,j] : ans)
				p.emplace_back(lower_bound(a.begin(),a.end(),i)-a.begin(),
				lower_bound(b.begin(),b.end(),j)-b.begin());
		}
		for(auto [i,j] : p)
			printf("%d %d\n",i,j);
	}
	return 0;
}