#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 300005;
const int INF = 2e9;
int n, q, a[N]; 
struct Node{
	int mx, mn; //节点中有效元素的最大/最小值(有效元素:除了-1以外的元素)
} tree[N*4];
Node merge(Node a, Node b)
{
	Node res;
	res.mn = min(a.mn, b.mn);
	res.mx = max(a.mx, b.mx);
	return res;
}
void pushup(int p)
{
	tree[p] = merge(tree[2*p], tree[2*p+1]);
}
void update(int p, int l, int r, int pos, int x)
{
	if (l == r) 
	{
		if (x == -1) 
		{
			tree[p].mn = INF;
			tree[p].mx = 0;
		}
		else tree[p].mn = tree[p].mx = x;
		return;
	}
	int mid = (l+r)/2;
	if (pos <= mid) update(2*p, l, mid, pos, x);
	if (pos > mid) update(2*p+1, mid+1, r, pos, x);
	pushup(p);
}
void build(int p, int l, int r)
{
	if (l == r) 
	{
		if (a[l] == -1)
		{
			tree[p].mx = 0;
			tree[p].mn = INF;
		} 
		else tree[p].mx = tree[p].mn = a[l];
		return;
	}
	int mid = (l+r)/2;
	build(2*p, l, mid);
	build(2*p+1, mid+1, r);
	pushup(p);
}
Node query(int p, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr)
	{
		return {tree[p].mx, tree[p].mn};
	}
	int mid = (l+r)/2;
	Node res = {0, INF};
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
	for (int i = 1; i <= q; ++i)
	{
		int cmd, pos, x, l, r;
		cin >> cmd;
		if (cmd == 1)
		{
			cin >> pos >> x;
			update(1, 1, n, pos, x);
		} else {
			cin >> l >> r;
			Node ans = query(1, 1, n, l, r);
			if (ans.mn == ans.mx || ans.mx == 0) cout << "Yes\n";
			else cout << "No\n";
		}
	}
	return 0;
}
