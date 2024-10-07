#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
mt19937 rng(time(0));

struct op { int id, x, y, z; op(int a, int b, int c, int d) { id = a, x = b, y = c, z = d; }};
vector<op> res;

bitset<100100> a[101], x, y, z, mask;
int T, n, m, q;

void judge() {
	for (int i = 3; i <= 100; i++) a[i] = a[0];
	a[1] = x, a[2] = y;
	int c = 0;
	for (int i = 0; i < n; i++) {
		c += x[i] + y[i];
		z[i] = c & 1;
		c >>= 1;
	}
	for (auto &x: res) {
		if (x.id == 0) a[x.z] = a[x.x] ^ a[x.y];
		if (x.id == 1) a[x.z] = a[x.x] | a[x.y];
		if (x.id == 2) a[x.z] = a[x.x] & a[x.y];
		if (x.id == 3) a[x.z] = mask ^ a[x.x];
		if (x.id == 4) a[x.z] = mask & (a[x.x] << x.y);
		if (x.id == 5) a[x.z] = a[x.x] >> x.y;
	}
	if (a[3] != z)
		quitf(_wa, "Wrong Answer");
}

int main(int argc, char **argv) {
	registerTestlibCmd(argc, argv);
	T = inf.readInt(1, 10);
	n = inf.readInt();
	m = inf.readInt();
	q = ouf.readInt(0, m), m += 2;
	for (int i = 0; i < n; i++) mask[i] = 1;
	while (q--) {
		string op = ouf.readToken();
		if (op == "~") {
			int i = ouf.readInt(1, 100);
			int j = ouf.readInt(1, 100);
			res.eb(3, i, 0, j);
		} else if (op == "<<" || op == ">>") {
			int i = ouf.readInt(1, 100);
			int j = ouf.readInt(0, 1e9);
			int k = ouf.readInt(1, 100);
			if (op == "<<")
				res.eb(4, i, j, k);
			else
				res.eb(5, i, j, k);
		} else {
			int i = ouf.readInt(1, 100);
			int j = ouf.readInt(1, 100);
			int k = ouf.readInt(1, 100);
			if (op == "^")
				res.eb(0, i, j, k);
			else if (op == "|")
				res.eb(1, i, j, k);
			else if (op == "&")
				res.eb(2, i, j, k);
			else
				quitf(_wa, "unknown operation %s", op.c_str());
		}
		ouf.readEoln();
	}
	//inf.readEof();
	//ouf.readEof();
	//ans.readEof();
	while (1) {
		string s1 = ans.readToken();
		if (s1[0] == '~') break;
		string s2 = ans.readToken();
		x = y = a[0];
		int i = 0;
		for (char c: s1) {
			c -= 33;
			for (int j = 0; j < 6; j++) x[i++] = c >> j & 1;
		}
		i = 0;
		for (char c: s2) {
			c -= 33;
			for (int j = 0; j < 6; j++) y[i++] = c >> j & 1;
		}
		judge();
	}
	quitf(_ok, "Accepted, used %d\n", res.size());
}
