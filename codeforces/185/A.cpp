// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define sl(n) scanf("%lld", &n)
#define si(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define inf (1LL << 61)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; ++i)
#define for0(i, stop) for(ll i = 0; i < stop; ++i)
#define rep1(i, start) for(ll i = start; i >= 1; --i)
#define rep0(i, start) for(ll i = (start-1); i >= 0; --i)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll MOD = 1e9 + 7;
const ll MOD2 = MOD * MOD;   /// Only when (MOD * MOD) fits into long long
#define row 2
#define col 2
ll exponents[64][row][col];
ll result[row], vect[row];
ll base[row][col] = { {3, 1}, {1, 3} }; /// Base Matrix
ll baseVect[row] = {1, 0};

struct MatExpo

{
	MatExpo() {
        memcpy(exponents[0], base, sizeof(base));

    	/// Calculating all exponents
    	for(ll p = 1; p < 62; p++) {

            for(ll i = 0; i < row; i++) {
                for(ll j = 0; j < col; j++) {
                    ll tmp = 0;
                    for(ll k = 0; k < col; k++) {
                    	tmp += exponents[p - 1][i][k] * exponents[p - 1][k][j];
                        while(tmp >= MOD2) /// Taking modulo MOD2 is easy, because we can do it by subtraction
                        	tmp -= MOD2;
                    }
                    exponents[p][i][j] = tmp % MOD;
                }
        	}
	    }

	}

	ll ans(ll m) {

    	/// Return from base case
    	if(m == 0)
            return 1;

        memcpy(vect, baseVect, sizeof(baseVect));
    	ll n = m, tmp;   /// Here, (n - 1)th power of base matrix represents the nth term
    	for(ll p = 60; p >= 0; p--) {
            if((n >> p) & 1) {

                for(ll i = 0; i < row; i++) {
                    tmp = 0;
                    for(ll j = 0; j < col; j++) {
                    	tmp += exponents[p][i][j] * vect[j];
                    	while(tmp >= MOD2) /// Taking modulo MOD2 is easy, because we can do it by subtraction
                        	tmp -= MOD2;
      	          }
                    result[i] = tmp % MOD;
                }

                memcpy(vect, result, sizeof(result));
        	}

    	}

    	return result[0] % MOD;
	}

};

// MatExpo ex = MatExpo();
// ans = ex.ans(n);  	nth term, term count starts from 0

int main()
{
    MatExpo ex = MatExpo();
    ll n;
    cin >> n;
    cout << ex.ans(n) << EL;

    return 0;
}