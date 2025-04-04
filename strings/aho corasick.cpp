int nex[MX][SIG], fail[MX], out[MX], finish[MX], cnt[MX], sz = 1;
vi ocu[MX]; // Almacena las ocurrencias de cada cadena en el texto

void insert (string &s, int ind) {
	int u = 0;

	for (char c : s) {
		c -= 'a';

		if (!nex[u][c]) {
			nex[u][c] = sz;
			finish[sz] = -1;
			sz++;
		}

		u = nex[u][c];
	}

	finish[u] = ind;
	cnt[u]++;
}

int getFail (int u, int c) {
	while (u && !nex[u][c])
		u = fail[u];
	return nex[u][c];
}

void build () {
	queue<int> q;
	
	for (int i = 0; i < SIG; i++)
		if (nex[0][i])
			q.push(nex[0][i]);

	while (q.size()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < SIG; i++) {
			int v = nex[u][i];

			if (v) {
				fail[v] = getFail(fail[u], i);
				cnt[v] += cnt[fail[v]];
				q.push(v);

				// <comentar> Si no necesitan las posiciones exactas de cada patron en el texto
				// Complejidad de esta parte O(sqrt(n))
				out[v] = fail[v];
				while (finish[out[v]] == -1)
					out[v] = fail[out[v]];
				// </comentar>
			}
		}
	}
}

int match (string &t) {
	int u = 0, res = 0;

	for (int i = 0; i < t.size(); i++) {
		char c = t[i] - 'a';
		
		if (nex[u][c])
			u = nex[u][c];
		else
			u = getFail(fail[u], c);
		res += cnt[u];

		// <comentar> Si no necesitan las posiciones exactas de cada patron en el texto
		// Complejidad de esta parte O(sqrt(n))
		int v = u;
		while (v && cnt[v]) {
			if (finish[v] != -1)
				ocu[finish[v]].push_back(i);
			v = out[v];
		}
		// </comentar>
	}

	return res;
}
