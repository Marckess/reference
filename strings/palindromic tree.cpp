const int MX = 1e6+5, SIG = 26;
int str[MX], len[MX], link[MX], to[MX][SIG];

// <comentar si no se requiere factorizar cadena>
int slink[MX], dif[MX];
// </comentar>

int cur, sl, sz;

void init () {
	memset(to, 0, sizeof(to));
	cur = sl = 0;
	str[sl++] = -1;

	link[0] = 1, len[0] = 0;
	link[1] = 0, len[1] = -1;

	sz = 2;
}

int getLink (int v) {
	while (str[sl - len[v] - 2] != str[sl - 1]) v = link[v];
	return v;
}

void insert (int c) {
	str[sl++] = c;
	cur = getLink(cur);

	if (!to[cur][c]) {
		len[sz] = len[cur] + 2;
		link[sz] = to[getLink(link[cur])][c];
		
		// <comentar si no se requiere factorizar cadena>
		dif[sz] = len[sz] - len[link[sz]];
		if (dif[sz] == dif[link[sz]]) slink[sz] = slink[link[sz]];
		else slink[sz] = link[sz];
		// </comentar>

		to[cur][c] = sz++;
	}

	cur = to[cur][c];
}

// <comentar si no se requiere factorizar cadena>
vector<int> factorizar (string s) {
	vector<int> dp(s.size() + 1), acu(s.size() + 1);
	
	init();
	
	dp[0] = 1;
	
	for (int i = 1; i <= s.size(); i++) {
		insert(s[i-1]-'a');
		
		for (int j = cur; j > 1; j = slink[j]) {
			acu[j] = dp[i - len[slink[j]] - dif[j]];
			if (dif[j] == dif[link[j]])
				(acu[j] += acu[link[j]]) %= mod;
			(dp[i] += acu[j]) %= mod;
		}
	}
	
	return dp;
}
// </comentar>
