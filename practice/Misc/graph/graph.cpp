/*
#include "graph.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

namespace {

int read_int() {
	int x;
	if (scanf("%d", &x) != 1) {
		fprintf(stderr, "Error while reading input\n");
		exit(1);
	}
	return x;
}

} // namespace

int main() {
	int N = read_int();
	int M = read_int();
	std::vector<int> a(N);
	for (int i = 0; i < N; ++i) {
		a[i] = read_int();
	}

	init_permutation(N, a);
	for (int i = 0; i < M; ++i) {
		int l = read_int();
		int r = read_int();
		printf("%d\n", calc_f(l, r));
	}
	return 0;
}
//*/

#include <vector>
using namespace std;

const int N = 3e5, logN = 20;

int a[N + 2],mx[N + 2],mn[N + 2],p[logN][N + 2],Log2[N + 2];
struct rmq {
	int x,y;
} st[logN][N + 2];

rmq merge(rmq u,rmq v) {
	return rmq{a[u.x]<a[v.x]?u.x:v.x,a[u.y]<a[v.y]?v.y:u.y};
}

rmq ask(int l,int r) {
	int k=Log2[r-l+1];
	return merge(st[k][l],st[k][r-(1<<k)+1]);
}

void init_permutation(int n, vector<int> a_) {
	for(int i=0; i<n; ++i) a[i]=a_[i];
	vector<int> stk1,stk2;
	for(int i=2; i<=n; ++i)
		Log2[i]=Log2[i>>1]+1;
	for(int i=0; i<n; ++i) {
		while(!stk1.empty()&&a[stk1.back()]<a[i]) {
			mx[stk1.back()]=i;
			stk1.pop_back();
		}
		while(!stk2.empty()&&a[stk2.back()]>a[i]) {
			mn[stk2.back()]=i;
			stk2.pop_back();
		}
		stk1.push_back(i);
		stk2.push_back(i);
	}
	for(auto i : stk1) mx[i]=n;
	for(auto i : stk2) mn[i]=n;
	for(int i=0; i<n; ++i)
		st[0][i]=rmq{i,i};
	for(int j=1; j<logN; ++j)
		for(int i=0; i+(1<<j)<=n; ++i)
			st[j][i]=merge(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	for(int i=0; i<n-1; ++i)
		p[0][i]=max(ask(i,mx[i]-1).x,ask(i,mn[i]-1).y);
	p[0][n-1]=n;
	for(int j=0; j<logN; ++j)
		p[j][n]=n;
	for(int j=1; j<logN; ++j)
		for(int i=0; i<n; ++i)
			p[j][i]=p[j-1][p[j-1][i]];
}

int calc_f(int l, int r) {
	int ans=0;
	for(int i=logN-1; i>=0; --i)
		if(p[i][l]<=r)
			ans+=1<<i,l=p[i][l];
	while(l<r) {
		l=max(ask(l,min(mx[l]-1,r)).x,ask(l,min(mn[l]-1,r)).y);
		++ans;
	}
	return ans;
}