#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200005;
const ll INF = 4e18;
ll n, q, a[N];
struct Node{
	ll sum, lazy;
} tree[N*4];

void pushup(int p)
{
	tree[p].sum = tree[2*p].sum+tree[2*p+1].sum;
}

void apply(int p, int l, int r, ll x) 
{
	tree[p].sum += (r-l+1)*x;
	tree[p].lazy += x;
}

void pushdown(int p, int l, int r)
{
	if (tree[p].lazy == 0) return;
	int mid = (l+r)/2;
	apply(2*p, l, mid, tree[p].lazy);
	apply(2*p+1, mid+1, r, tree[p].lazy);
	tree[p].lazy = 0;
}

void build(int p, int l, int r)
{
	tree[p].lazy = 0;
	if (l == r)
	{
		tree[p].sum = a[l];
		return;
	}
	int mid = (l+r)/2;
	build(2*p, l, mid);
	build(2*p+1, mid+1, r);
	pushup(p);
}

void update(int p, int l, int r, int ql, int qr, ll val)
{
	if (ql <= l && r <= qr)
	{
		apply(p, l, r, val);
		return;
	}
	pushdown(p, l, r); //下传懒标记
	int mid = (l+r)/2;
	if (ql <= mid) update(2*p, l, mid, ql, qr, val);
	if (qr > mid) update(2*p+1, mid+1, r, ql, qr, val); 
	pushup(p);
}

ll query(int p, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) //查询的区间完全覆盖了这个节点的区间
	{
		return tree[p].sum;
	}
	pushdown(p, l, r);
	int mid = (l+r)/2;
	ll ans = 0;
	if (ql <= mid) ans += query(2*p, l, mid, ql, qr);
	if (qr > mid) ans += query(2*p+1, mid+1, r, ql, qr);
	return ans;
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
		int cmd, x, y;
		cin >> cmd;
		if (cmd == 1)
		{
			ll k;
			cin >> x >> y >> k;
			update(1, 1, n, x, y, k);
		} else {
			cin >> x >> y;
			cout << query(1, 1, n, x, y) << "\n";
		}
	}
	return 0; 
}