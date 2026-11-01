//滚动数组优化版本,dp数组第一个[]只保留2

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 4005, MOD = 998244353;
ll t, n, m, dp[2][N], pre[N]; //dp[j]:开头为m+2,结尾为j的第一类数组的方案数(滚动数组优化)
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 1; i <= m+1; ++i) dp[1][i] = 0;
		dp[1][m+2] = 1;
		ll ans = 0;
		int idx = 1;
		for (int i = 2; i <= n; ++i)
		{
			idx = !idx;
			for (int j = 1; j <= m+2; ++j)
			{
				pre[j] = pre[j-1]+dp[!idx][j];
			}
			for (int j = 2; j <= m+2; ++j)
			{
				dp[idx][j] = (pre[min(2LL*j-1, m+2)]-pre[j-1] + MOD) % MOD;
			}
			if (i >= 2) ans = (ans+dp[idx][2]) % MOD;
		}
		cout << ans%MOD << "\n";
	}
	return 0;
}
