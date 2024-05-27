// Problem URL : https://uoj.ac/problem/52

#include "kth.h"
#include<utility>
#include<vector>
#include<algorithm>

using namespace std;

int query_kth(int n_a, int n_b, int n_c, int k)
{
	int p[3]={0,0,0};
	while(k>2) {
		int t=k/3;
		auto [x,v]=min({
			make_pair(get_a(p[0]+t-1),0),
			make_pair(get_b(p[1]+t-1),1),
			make_pair(get_c(p[2]+t-1),2),
		});
		p[v]+=t;
		k-=t;
	}
	if(k==1) return min({
		get_a(p[0]),
		get_b(p[1]),
		get_c(p[2])
	});
	vector<int> val{
		get_a(p[0]),get_b(p[1]),get_c(p[2]),
		get_a(p[0]+1),get_b(p[1]+1),get_c(p[2]+1)
	};
	sort(val.begin(),val.end());
	return val[1];
}