#include <bits/stdc++.h>

using namespace std;

using cd = complex<long double>;
const long double PI = acos(-1);

void fft(vector<cd> &a, bool invert)
{
	int n = a.size();

	for(int i = 1, j = 0; i < n; i++)
	{
		int bit = n / 2;

		for(; j & bit; bit /= 2)
			j ^= bit;
		j ^= bit;

		if(i < j)
			swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1)
	{
		long double ang = 2 * PI / len * (invert ? 1 : -1);
		cd wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len)
		{
			cd w(1);
			for(int j = 0; j < len / 2; j++)
			{
				cd u = a[i + j], v = a[i + j + len/2] * w;
				a[i + j] = u + v;
				a[i + j + len/2] = u - v;
				w *= wlen;
			}
		}
	}

	if(invert)
		for(cd &x: a)
			x /= n;
}

vector<long long> multiply(vector<long long> const &a, vector<long long> const &b)
{
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;

	while(n < a.size() + b.size())
		n <<= 1;

	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);

	for(int i = 0; i < n; i++)
		fa[i] *= fb[i];

	fft(fa, true);

	vector<long long> res(n);
	for(int i = 0; i < n; i++)
		res[i] = round(fa[i].real());

	return res;
}

vector<long long> v[3], rv[3];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string s;

	cin >> s;

	for(long long i = 0; i < 3; i++)
		for(long long j = 0; j < s.size(); j++)
			if(s[j] == 'a' + i)
				v[i].push_back(1);
			else
				v[i].push_back(0);

	for(long long i = 0; i < 3; i++)
	{
		rv[i] = v[i];
		reverse(rv[i].begin(), rv[i].end());

		v[i] = multiply(v[i], rv[i]);
	}


	for(long long i = 1; i < 3; i++)
		for(long long j = 0; j < v[i].size(); j++)
			v[0][j] += v[i][j];

	long long mx = 0;

	for(long long i = s.size(); i < v[0].size(); i++)
		mx = max(mx, v[0][i]);

	cout << mx << "\n";

	for(long long i = s.size(); i < v[0].size(); i++)
		if(v[0][i] == mx)
			cout << i + 1 - s.size() << " ";
	cout << "\n";

	return 0;
}
