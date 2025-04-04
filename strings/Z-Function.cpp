int n, q, k, t;
string s;
vi zf;

void obtZF (string &s) {
    n = s.size();
    zf = vi(n);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            zf[i] = min (r - i + 1, zf[i - l]);
        while (i + zf[i] < n && s[zf[i]] == s[i + zf[i]])
            zf[i]++;
        if (i + zf[i] - 1 > r)
            l = i, r = i + zf[i] - 1;
    }
}

int main () {   
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> t;
    while (t--) {
        cin >> s;
        n = s.size();

        obtZF();

        vi acu(1e5+2);
        acu[n]++;
        for (int i = 1; i < n; i++)
            acu[zf[i]]++;

        for (int i = 1e5; i >= 0; i--)
            acu[i] += acu[i+1];

        cin >> q;
        while (q--) {
            cin >> k;
            cout << acu[k] << " ";
        }
        cout << endl;
    }

    return 0;
}  