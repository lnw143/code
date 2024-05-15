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
