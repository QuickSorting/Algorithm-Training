#include <bits/stdc++.h>

using namespace std;

vector<int> failure_function(string p){
	vector<int> f;
	int j = 0;

	f.resize((int)p.size() + 1, 0);

	f[0] = 0;

	for(int i = 1; i < p.size(); i++){
		while(j >= 0 && p[i] != p[j]){
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

vector<int> match(vector<int> f, string p, string s){
	int j = 0;
	vector<int> res;

	for(int i = 0; i < (int)s.size(); i++){
		while(j >= 0 && s[i] != p[j]){
			if(j >= 1){
				j = f[j - 1];
			}
			else{
				j = -1;
			}
		}

		j++;
		if(j == (int)p.size()){
			res.push_back(i - (int)p.size() + 2);
			j = f[j - 1];
		}
	}

	return res;
}

void solve(){
	string s, p;

	cin >> s >> p;

	vector<int> f = failure_function(p);
	vector<int> res = match(f, p, s);

	if(res.empty()){
		cout << "Not Found\n\n";

		return ;
	}

	cout << res.size() << "\n";
	for(int idx: res){
		cout << idx << " "; 
	}
	cout << "\n\n";

	return ;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t;

	cin >> t;

	while(t--){
		solve();
	}

	return 0;
}
