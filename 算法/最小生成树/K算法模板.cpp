#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5005;
struct Edge{
	int u, v, z;
};
vector<Edge> edges;
bool cmp(Edge x, Edge y)
{
	return x.z < y.z;
}
int n, m, parent[N], sz[N];
int find(int x)
{
	if (parent[x] != x)
	{
		parent[x] = find(parent[x]);
	}
	return parent[x];
}
bool unite(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y) return false; //本来就联通 合并失败
	if (sz[x] < sz[y]) swap(x, y);
	parent[y] = x;
	sz[x] += sz[y];
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i  <= n; ++i)
	{
		parent[i] = i; //初始时 各自不连通
		sz[i] = 1;
	}
	for (int i = 1; i <= m; ++i)
	{
		int x, y, z;
		cin >> x >> y >> z;
		edges.push_back({x, y, z});
	}
	sort(edges.begin(), edges.end(), cmp);
	int sum = 0, cnt = 0; //边权之和 已经添加到边数
	for (auto &e:edges)
	{
		if (unite(e.u, e.v)) //不连通 可以合并成功
		{
			sum += e.z;
			++cnt;
		}
		if (cnt == n-1) break; //数量够了
	}
	if (cnt == n-1) cout << sum;
	else cout << "orz";
	return 0;
}
