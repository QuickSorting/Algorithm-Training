#include <bits/stdc++.h>

using namespace std;

vector<long long> failure_function(string s){
	vector<long long> f;
	long long j = 0;

	f.resize((int)s.size() + 1, 0);

	f[0] = 0;

	for(int i = 1; i < (int)s.size(); i++){
		while(j >= 0 && s[i] != s[j]){
			if(j >= 1){
				j = f[j - 1];
			}
			else{
				j = -1;
			}
		}

		j++;
		f[i] = j;
	}

	return f;
}

void solve(){
	string s;
	long long k;

	cin >> s >> k;

	vector<long long> f = failure_function(s);

	long long n = (long long)s.size();
	long long res = n + (long long)(n - f[n - 1]) * (k - 1);

	cout << res << "\n";

	return ;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long t;

	cin >> t;

	while(t--){
		solve();
	}

	return 0;
}
