#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	long long x, a, b, c;
	cin >> x >> a >> b >> c;

	const int m = n - k + 1; 
	long long ans = 0;

	for (int j = 1; j <= n; j++) {
		int left = max(1, j - k + 1);
		int right = min(j, m);
		int cnt = right - left + 1;

		if (cnt > 0 && (cnt & 1)) {
			ans ^= x;
		}

		if (j < n) {
			x = (a * x + b) % c;
		}
	}

	cout << ans << '\n';
	return 0;
}
