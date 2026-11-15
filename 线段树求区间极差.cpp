#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200005;
const ll INF = 4e18;
int n, q, a[N];
struct Node{
	ll mx, mn;
} tree[N*4];

Node merge(Node a, Node b)
{
	return {max(a.mx, b.mx), min(a.mn, b.mn)};
}

void build(int p, int l, int r)
{
	if (l == r)
	{
		tree[p].mn = tree[p].mx = a[l];
		return;
	}
	int mid = (l+r)/2;
	build(2*p, l, mid);
	build(2*p+1, mid+1, r);
	tree[p] = merge(tree[2*p], tree[2*p+1]);
}

void update(int p, int l, int r, int pos, int val)
{
	if (l == r)
	{
		tree[p].mn = tree[p].mx = val;
		return;
	}
	int mid = (l+r)/2;
	if (pos <= mid) //要修改的点在当前节点的左子树
	{
		update(2*p, l, mid, pos, val);
	}
	else update(2*p+1, mid+1, r, pos, val);
	tree[p] = merge(tree[2*p], tree[2*p+1]);
}

Node query(int p, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) //查询的区间完全覆盖了这个节点的区间
	{
		return tree[p];
	}
	int mid = (l+r)/2;
	Node res = {-INF, INF};
	if (ql <= mid) res = merge(res, query(2*p, l, mid, ql, qr));
	if (qr > mid) res = merge(res, query(2*p+1, mid+1, r, ql, qr));
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(1, 1, n);
	while(q--)
	{
		int cmd;
		cin >> cmd;
		if (cmd == 1)
		{
			int p;
			ll x;
			cin >> p >> x;
			update(1, 1, n, p, x);
		} else {
			int l, r;
			cin >> l >> r;
			Node ans = query(1, 1, n, l, r);
			cout << ans.mx - ans.mn << "\n";
		}
	}
	return 0; 
}