#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9 + 7;
const long long base = 27;

long long hash_needle(string p){
	int n = p.size();
	long long true_hash = 0;

	for(int i = 0; i < p.size(); i++){
		true_hash *= base;
		true_hash += p[i] - 'a' + 1;
		true_hash %= mod;
	}

	return true_hash;
}

string hay = "";
int n;
long long true_hash, power, curr_hash;

bool update_hash(char c, int idx){
	bool ok = false;

	if(idx < n){
		curr_hash *= base;
		curr_hash += c - 'a' + 1;
		curr_hash %= mod;

		if(idx == n - 1 && curr_hash == true_hash){
			cout << "0\n";
			ok = true;
		}

		hay += c;

		return ok;
	}
	//cout << curr_hash << " curr_hash\n";
	//cout << idx % n << " idx hay " << hay << "\n"; 

	curr_hash *= base;
	curr_hash -= ((hay[idx % n] - 'a' + 1) * power) % mod;
	curr_hash += mod;
	curr_hash += (c - 'a' + 1);
	curr_hash %= mod;

	hay[idx % n] = c;

	if(curr_hash == true_hash){
		cout << idx - n + 1 << "\n";
		ok = true;
	}

	return ok;
}

bool solve(){
	string needle;
	hay.clear();

	if(!(cin >> n >> needle)){
		return false;
	}
	//cout << n << " n needle " << needle << "\n"; 

	true_hash = hash_needle(needle);
	//cout << true_hash << " true_hash\n";

 	power = 1;
 	for(int i = 1; i <= n; i++){
 		power *= base;
 		power %= mod;
 	}
 	//cout << power << " power\n";

 	curr_hash = 0;

 	char c;
 	int idx = 0;

 	cin.get(c);

 	bool ok = false;

	while(cin.get(c)){
		if(c < 'a' || c > 'z'){
			break;
		}
		//cout << c << endl;
		if(update_hash(c, idx)){
			ok = true;
		}
		idx++;
	}

	if(!ok){
		cout << "\n";
	}

	return true;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//freopen("input.txt", "r", stdin);

	while(solve()){
		continue;
	}

	return 0;
}
/*
2
na
banananobano
6
foobar
foo
9
foobarfoo
barfoobarfoobarfoobarfoobarfoo
*/
