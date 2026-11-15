#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 300005;
int n, cnt[N]; 
ll a[N], s[N], ss[N], treecnt[N], l, r; //treecnt[i]:截止到目前位置,s对应的离散化编号i出现过的次数所对应的树状数组
int lowbit(int x) {return x&-x;}
void add(int x, int val)
{
	while (x <= n)
	{
		treecnt[x] += val;
		x += lowbit(x);
	}
}
ll sum(int x)
{
	ll res = 0;
	while (x > 0)
	{
		res += treecnt[x];
		x -= lowbit(x);
	}
	return res;
}
unordered_map<ll, int> pos; //pos[x]:x所对应的离散化编号
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> l >> r;
	for (int i = 1; i <= n; ++i) 
	{
		cin >> a[i];
		s[i] = s[i-1]+a[i];
		ss[i] = s[i];
	}
	sort(ss+1, ss+n+1);
	ll ans = 0;
	for (int i = 1; i <= n; ++i) pos[ss[i]] = i;
	for (int i = 1; i <= n; ++i)
	{
		ll L = s[i]-r, R = s[i]-l; //[L,R]:所需要找的前面的前缀和的范围
		int lo = lower_bound(ss+1, ss+n+1, L)-ss; //转化为对应的离散化编号区间
		int hi = upper_bound(ss+1, ss+n+1, R)-ss-1;
		ans += sum(hi)-sum(lo-1); //找离散化编号区间内的cnt数量
		if (s[i] >= l && s[i] <= r) ++ans; 
		add(pos[s[i]], 1);
	}
	cout << ans;
	return 0;
}
