#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 200005;
const ll MOD = 1e9+7;

int n, q;
ll a[N];

struct Node {
    ll sum, mul, add;
} tree[N*4];

ll norm(ll x)
{
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

void pushup(int p)
{
    tree[p].sum = (tree[p*2].sum + tree[p*2+1].sum) % MOD;
}

// 对当前区间施加变换：x -> x*k+b
void apply(int p, int l, int r, ll k, ll b)
{
    tree[p].sum = (tree[p].sum*k+(r-l+1)*b)%MOD;
    tree[p].mul = (tree[p].mul*k)%MOD;
    tree[p].add = (tree[p].add*k+b)%MOD;
}

void pushdown(int p, int l, int r)
{
	if (tree[p].add == 0 && tree[p].mul == 1) return;
    int mid = (l+r)/2;
	apply(p*2, l, mid, tree[p].mul, tree[p].add);
	apply(p*2+1, mid+1, r, tree[p].mul, tree[p].add);
	tree[p].add = 0;
	tree[p].mul = 1;
}

void build(int p, int l, int r)
{
    tree[p].mul = 1;
    tree[p].add = 0;

    if (l == r)
    {
        tree[p].sum = norm(a[l]);
        return;
    }

    int mid = (l+r)/2;

    build(p*2, l, mid);
    build(p*2+1, mid+1, r);

    pushup(p);
}

// 区间执行 x -> x*k+b
void update(int p, int l, int r,
            int ql, int qr, ll k, ll b)
{
    if (ql <= l && r <= qr)
    {
        apply(p, l, r, k, b);
        return;
    }

    pushdown(p, l, r);

    int mid = (l+r)/2;

    if (ql <= mid)
        update(p*2, l, mid, ql, qr, k, b);

    if (qr > mid)
        update(p*2+1, mid+1, r, ql, qr, k, b);

    pushup(p);
}

ll query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return tree[p].sum;

    pushdown(p, l, r);

    int mid = (l+r)/2;
    ll ans = 0;

    if (ql <= mid)
        ans = (ans + query(p*2, l, mid, ql, qr)) % MOD;

    if (qr > mid)
        ans = (ans + query(p*2+1, mid+1, r, ql, qr)) % MOD;

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    build(1, 1, n);

    while (q--)
    {
        int op, l, r;
        cin >> op >> l >> r;

        if (op == 1)
        {
            ll x;
            cin >> x;
            x = norm(x);
            update(1, 1, n, l, r, x, 0);
        }
        else if (op == 2)
        {
            ll x;
            cin >> x;
            x = norm(x);
            update(1, 1, n, l, r, 1, x);
        }
        else
        {
            cout << query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}
