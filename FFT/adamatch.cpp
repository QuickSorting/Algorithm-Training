#include <bits/stdc++.h>

using namespace std;

struct fast_complex
{
	long double a, b;

	fast_complex(long double _a = 0.0, long double _b = 0.0)
	{
		a = _a;
		b = _b;
	}

	long double real()
	{
		return a;
	}

	friend fast_complex operator+(fast_complex lvalue, fast_complex rvalue)
	{
		fast_complex ret;

		ret.a = lvalue.a + rvalue.a;
		ret.b = lvalue.b + rvalue.b;

		return ret;
	}

	friend fast_complex operator-(fast_complex lvalue, fast_complex rvalue)
	{
		fast_complex ret;

		ret.a = lvalue.a - rvalue.a;
		ret.b = lvalue.b - rvalue.b;

		return ret;
	}

	friend fast_complex operator*(fast_complex lvalue, fast_complex rvalue)
	{
		fast_complex ret;

		ret.a = lvalue.a * rvalue.a + lvalue.b * rvalue.b;
		ret.b = lvalue.a * rvalue.b + lvalue.b * rvalue.a;

		return ret;
	}
};

using cd = complex<long double>;

const long double PI = acos(-1);

void fft(vector<cd> &a, bool invert)
{
	int n = a.size();

	for(int i = 1, j = 0; i < n; i++)
	{
		int bit = n / 2;
		for(; bit & j; bit /= 2)
			j ^= bit;
		j ^= bit;

		if(i < j)
			swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len *= 2)
	{
		long double ang = 2 * PI / len * (invert ? -1 : 1);
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
		for(auto &x: a)
			x /= n;
}

vector<long long> multiply(vector<long long> const &a, vector<long long> const &b)
{
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;

	while(n < a.size() + b.size())
		n *= 2;

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

char c[4] = {'A', 'C', 'G', 'T'};

vector<long long> vs[4], vr[4], tmp;
vector<long long> res;

int main ()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string s, r;

	cin >> s >> r;

	for(int i = 0; i < (long long)s.size(); i++)
		for(int j = 0; j < 4; j++)
			if(s[i] == c[j])
				vs[j].push_back(1);
			else
				vs[j].push_back(0);

	for(int i = 0; i < (long long)r.size(); i++)
		for(int j = 0; j < 4; j++)
			if(r[i] == c[j])
				vr[j].push_back(1);
			else
				vr[j].push_back(0);

	tmp = vr[0];
	reverse(tmp.begin(), tmp.end());

	res = multiply(tmp, vs[0]);

	for(int i = 1; i < 4; i++)
	{
		tmp = vr[i];
		reverse(tmp.begin(), tmp.end());

		vector<long long> new_res = multiply(tmp, vs[i]);

		for(int j = 0; j < res.size(); j++)
			res[j] += new_res[j];
	}

	long long mx = 0;

	for(int i = (long long)r.size() - 1; i < (long long)s.size(); i++)
		mx = max(mx, res[i]);

	cout << (long long)r.size() - mx << "\n";

	return 0;
}
/*
GCAG
GA
*/
