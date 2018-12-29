#include <bits/stdc++.h>

using namespace std;

const int N = 4007;
const int K = 807;
const int INF = 1e9;

int u[N][N];
int c[N][N];
int dp_before[N], dp_curr[N];

inline int calc(int l, int r)
{
	return c[r][r] - c[l-1][r] - c[r][l-1] + c[l-1][l-1];
}

void compute(int l, int r, int optl, int optr)
{
	if(l > r)
		return;

	int mid = (l+r) >> 1;
	pair<int, int> best = {INF, -1};

	for(int k = optl; k <= min(mid, optr); ++k)
		best = min(best, {dp_before[k-1] + calc(k, mid), k});

	dp_curr[mid] = best.first;
	int opt = best.second;

	compute(l, mid-1, optl, opt);
	compute(mid+1, r, opt, optr);
}

int main ()
{
	int n, k;

	scanf("%d %d", &n, &k);

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
		{
			char ch = getchar();

			if('0' <= ch && ch <= '9')
				u[i][j] = ch - '0';
			else
			{
				j--;
				continue;
			}
			//scanf("%lld", &u[i][j]);
			c[i][j] = u[i][j];
		}

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			c[i][j] += c[i][j-1];

	for(int j = 1; j <= n; ++j)
		for(int i = 1; i <= n; ++i)
			c[i][j] += c[i-1][j];

	for(int i = 1; i <= n; ++i)
		dp_curr[i] = INF;

	for(int i = 0; i < k; ++i)
	{
		swap(dp_before, dp_curr);
		compute(1, n, 1, n);
	}

	//cout << dp_curr[n] / 2 << "\n";

	printf("%d\n", dp_curr[n] >> 1);

	return 0;
}