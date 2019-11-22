#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vl;
typedef vector<ii> vii;

struct Node {
	Node *p, *l, *r;
	int v;
	Node () : p(0), l(0), r(0), v(0) {}
	Node (int v) : p(0), l(0), r(0), v(v) {}
};

void rotate (Node *t) {
	if (!t || !t->p) return;

	Node *p = t->p;

	if (t == p->l) {
		p->l = t->r;
		t->r = p;
	} else {
		p->r = t->l;
		t->l = p;
	}

	t->p = p->p;
	p->p = t;

	if (p->l) p->l->p = p; 
	if (p->r) p->r->p = p;
	
	if (t->p) {
		if (t->p->l == p)
			t->p->l = t;
		else
			t->p->r = t;
	}
}

void splay (Node *t) {
	if (!t) return;

	while (t->p) {
		Node *p = t->p;
		Node *gp = p->p;

		if (gp) {
			if (t == p->l) {
				if (p == gp->l)
					rotate(p);
				else
					rotate(t);
			} else {
				if (p == gp->r)
					rotate(p);
				else
					rotate(t);
			}
		}

		rotate(t);
	} 
}

Node * find (Node *root, int k) {
	if (!root) return 0;

	Node *t = root;

	while (t && t->v != k) {
		if (k < t->v && t->l)
			t = t->l;
		else if (k > t->v && t->r)
			t = t->r;
		else
			break;
	}

	splay(t);
	return t;
}

Node * insert (Node *root, int k) {
	if (!root)
		return new Node(k);
	root = find(root, k);

	if (root->v == k)
		return root;

	Node *n = new Node(k);
	if (root->v < k) {
		n->r = root->r;
		root->r = 0;
		n->l = root;
	} else {
		n->l = root->l; 
		root->l = 0;
		n->r = root;
	}

	if (n->l) n->l->p = n;
	if (n->r) n->r->p = n;

	return n;
}

Node * erase (Node *root, int k) {
	if (!root)
		return 0;
	root = find(root, k);

	if (root->v != k)
		return root;

	Node *l = root->l;
	Node *r = root->r;

	if (l) l->p = 0;
	if (r) r->p = 0;
	delete root; 

	if (!l)
		return r;

	l = find(l, k);
	l->r = r;
	if (l->r)
		l->r->p = l;
	return l;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	srand(time(0));

	Node *r = 0;
	set<int> st;

	int q;
	cin >> q;
	while (q--) {
		int op = rand() % 3, k = rand() % 1000000;

		if (op == 0) {
			r = insert(r, k);
			st.insert(k);
		} else if (op == 1) {
			continue;
			r = erase(r, k);
			st.erase(k);
		} else if (op == 2) {
			r = find(r, k);
			if (st.count(k) != (r && r->v == k)) {
				cout << k << endl;
			}
		}
	}

	return 0;
}
