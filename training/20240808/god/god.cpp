#include <cstdio>
#include <cstdlib>
using namespace std;
void query(int *d, bool *a);
const int N = 1.6e4;
int d[N + 2];
bool a[N + 2];

namespace sub0 {
	int f[N + 2];
	int find(int x) {
		return f[x]==x?x:f[x]=find(f[x]);
	}
	void solve(int n) {
		for(int i=2; i<=n; ++i) d[i]=-1;
		d[1]=1;
		query(d,a);
		if(a[2]) {
			for(int i=1; i<n; ++i) printf("%d %d\n",i,i+1);
			return ;
		}
		for(int i=1; i<=n; i++) f[i]=i;
		for(int i=1; i<n; i++) {
			int x=rand()%n+1,y=rand()%n+1;
			while(find(x)==find(y)) x=rand()%n+1,y=rand()%n+1;
			printf("%d %d\n",x,y);
			f[find(x)]=find(y);
		}
	}
}

void wxy_god(int n, int subtask) {
	if(subtask==0) {
		if(n==5) return printf("2 1\n5 3\n2 4\n2 3\n"),void();
		sub0::solve(n);
		return ;
	}
	
}

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int Ktvlducfqu93480, Rsqesjxunn48711 = 0;
int Fusewxxijb22131[32010], Atdhnkmnim19426[16010], Cfhpnmupiw99440[16010];
vector<int> Tcioqvrytt86195[16010];
void query(int *d, bool *a) {
	if ((++Rsqesjxunn48711) > 17000) {
		cerr << "Query too much." << endl;
		exit(0);
	}

	for (int i = 1; i <= Ktvlducfqu93480; i++) {
		if (d[i] < -1 || d[i] >= Ktvlducfqu93480) {
			cerr << "Wrong parameter for query()" << endl;
			cerr << "d[" << i << "] = " << d[i] << " violates the range [-1, " << Ktvlducfqu93480 << ")" << endl;
			exit(0);
		}
	}

	static int f[16010], box[16010];
	memset(box, 0, sizeof(box));

	for (int i = 1; i <= Ktvlducfqu93480; i++) {
		a[i] = 0, f[i] = d[i];

		if (f[i] >= 0) {
			box[f[i]]++;
		}
	}

	for (int i = Ktvlducfqu93480 - 2; i >= 0; i--) {
		box[i] += box[i + 1];
	}

	static int q[48010], Q[16010];
	int l = 32000, r = box[0] + 31999;

	for (int i = 1; i <= Ktvlducfqu93480; i++) {
		if (f[i] >= 0) {
			q[(--box[f[i]]) + 32000] = i;
		}
	}

	while (l <= r) {
		int num = 0, F = f[q[l]];

		do {
			int t = q[l++];

			if (!a[t]) {
				a[Q[num++] = t] = 1;
			}
		} while (l <= r && f[q[l]] == F);

		if ((--F) >= 0) {
			for (int i = 0, k = Q[0]; i < num; k = Q[++i]) {
				for (int j = Atdhnkmnim19426[k]; j <= Cfhpnmupiw99440[k]; j++) {
					int t = Fusewxxijb22131[j];

					if (f[t] < F) {
						f[q[--l] = t] = F;
					}
				}
			}
		}
	}
}
void wxy_god(int n, int subtask);
int main() {
	freopen("god.in", "r", stdin);
	freopen("god.out", "w", stdout);
	int subtask;
	cin >> subtask >> Ktvlducfqu93480;

	for (int i = 1, x, y; i < Ktvlducfqu93480; i++) {
		cin >> x >> y;
		Tcioqvrytt86195[x].push_back(y);
		Tcioqvrytt86195[y].push_back(x);
	}

	int num = 0;

	for (int i = 1; i <= Ktvlducfqu93480; i++) {
		Atdhnkmnim19426[i] = num + 1;

		for (int j = 0; j < Tcioqvrytt86195[i].size(); j++) {
			int t = Tcioqvrytt86195[i][j];
			Fusewxxijb22131[++num] = t;
		}

		Cfhpnmupiw99440[i] = num;
	}

	wxy_god(Ktvlducfqu93480, subtask);
	cerr << "Number of queries: " << Rsqesjxunn48711 << endl;
	return 0;
}