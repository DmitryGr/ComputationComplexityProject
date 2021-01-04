#include <bits/stdc++.h>
#define ll long long
#define db long double
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()

using namespace std;

const int N = 5;

int g[N][N];
int gs[2*N][2*N];

const int INF = 1e9;

int gen_edge() {
	return rand() % 5 + 1;
}

void build_bipartite() {

	for (int i = 0; i < 2*N; ++i) {
		for (int j = 0; j < 2*N; ++j) {
			gs[i][j] = INF;
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			gs[i][N+j] = g[i][j];
			gs[N+j][i] = g[i][j];
		}
		gs[i][N+i] = 0;
		gs[N+i][i] = 0;
	}

}

template <int n>
int hamilton_cycle(int gr[n][n]) {

	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		v[i] = i;
	}

	int ans = INF;
	do {

		int tut = 0;
		for (int i = 0; i < v.size(); ++i) {
			int w = v[i], to = v[(i+1) % v.size()];
			tut += gr[w][to];
			tut = min(tut, INF);
		}

		ans = min(ans, tut);

	}
	while (next_permutation(all(v)));

	return ans;

}

template <int n>
void print_cycle(int gr[n][n]) {

	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		v[i] = i;
	}

	vector<int> opt;

	int ans = INF;
	do {

		int tut = 0;
		for (int i = 0; i < v.size(); ++i) {
			int w = v[i], to = v[(i+1) % v.size()];
			tut += gr[w][to];
			tut = min(tut, INF);
		}

		if (tut < ans) {
			ans = tut;
			opt = v;
		}

	}
	while (next_permutation(all(v)));

	cout << "CYCLE IS ";

	for (auto x : opt) {
		cout << x+1 << " ";
	}
	cout << endl;

}

main(){
#ifdef LOCAL
	freopen("A_input.txt", "r", stdin);
	//freopen("A_output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while (true) {

		for (int i = 0; i < N; ++i) {
			g[i][i] = INF;
			for (int j = i+1; j < N; ++j) {
				g[i][j] = gen_edge();
				g[j][i] = gen_edge();
			}
		}

		build_bipartite();

		int A = hamilton_cycle<N>(g);
		int B = hamilton_cycle<2*N>(gs);

		if (A != B) {
			cout << "GRAPH:\n";
			cout << N << endl;
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					if (g[i][j] == INF) cout << "X ";
					else cout << g[i][j] << " ";
				}
				cout << '\n';
			}
			cout << "HAMILTONIAN CYCLE SIZE IS " << A << endl;
			print_cycle<N>(g);
			cout << "BUT IN THE CORRESPODING BIPARTITE GRAPH IT'S " << B << endl;
			print_cycle<2*N>(gs);
			exit(0);
		}

	}

	


}
