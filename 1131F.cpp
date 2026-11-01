#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 4005, MOD = 998244353;
ll t, n, m, dp[N][N], pre[N]; //dp[k][j]:开头为m+2长度为k,结尾为j的第一类数组的方案数
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
		for (int i = 2; i <= n; ++i)
		{
			for (int j = 1; j <= m+2; ++j)
			{
				pre[j] = pre[j-1]+dp[i-1][j];
			}
			for (int j = 2; j <= m+2; ++j)
			{
				dp[i][j] = (pre[min(2LL*j-1, m+2)]-pre[j-1] + MOD) % MOD;
			}
			if (i >= 2) ans = (ans+dp[i][2]) % MOD;
		}
		cout << ans%MOD << "\n";
	}
	return 0;
}