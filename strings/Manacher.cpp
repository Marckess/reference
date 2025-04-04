// a b a c c a b a
// 103010161010301
const int MX = 3005;
int pal[2*MX], t[2*MX];

void manacher (string &s) {
	int n = s.size(), m = 2 * n - 1;

	for (int i = 0; i < m; i++)
		pal[i] = 0, t[i] = -1;
	for (int i = 0; i < n; i++)
		t[2*i] = s[i];

	int x = 0;
	for (int i = 1; i < m; i++) {
		int &r = pal[i];

		if (i <= x + pal[x])
			r = min(pal[2*x-i], x + pal[x] - i);
		while (i - r - 1 >= 0 && i + r + 1 < m && t[i-r-1] == t[i+r+1])
			r++;
		if (i + r >= x + pal[x])
			x = i;
	}

	for (int i = 0; i < m; i++)
		if (i - pal[i] == 0 || i + pal[i] == m - 1)
			pal[i]++;

	for (int i = 0; i < m; i++) {
		pal[i] /= 2;
		pal[i] = pal[i] + pal[i] + 1 - i % 2;
	}
}

