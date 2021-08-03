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

// === DEBUG MACRO STARTS HERE === //
#ifndef ONLINE_JUDGE
#define DEBUG
#define SYS_COL system("COLOR")
#endif

int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; \
                cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":" \
                <<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value,
            Ostream&>::type operator<<(Ostream& os,  const Cont& v) {
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
#else
#define dbg(x)
#endif
// === DEBUG MACRO ENDS HERE === //

#define ff first
#define ss second

/// O(n^2logn) per query if matrix is fixed for all queries
ll MOD, MOD2;   /// MOD2 only when (MOD * MOD) fits into long long
#define row 2
#define col 2
ll exponents[64][row][col];
ll result[row], vect[row];
ll base[row][col] = { {1, 1}, {1, 0} }; /// Base Matrix
ll baseVect[row] = {1, 1};  /// fibonacci sequence {1, 1, 2.....} here. So,f(1)=f(0)=1.

struct MatExpo

{
    MatExpo()
    {
        memcpy(exponents[0], base, sizeof(base));

        /// Calculating all exponents
        for(ll p = 1; p < 62; p++)
        {
            for(ll i = 0; i < row; i++)
            {
                for(ll j = 0; j < col; j++)
                {
                    ll tmp = 0;
                    for(ll k = 0; k < col; k++)
                    {
                        tmp += exponents[p - 1][i][k] * exponents[p - 1][k][j];
                        while(tmp >= MOD2) /// Taking modulo MOD2 is easy, because we can do it by subtraction
                            tmp -= MOD2;
                    }
                    exponents[p][i][j] = tmp % MOD;
                }
            }
        }

    }

    ll ans(ll m)
    {
        /// Return from base case
        if(m == 0 || m == 1)
            return 1%MOD;

        memcpy(vect, baseVect, sizeof(baseVect));
        ll n = m - 1, tmp;   /// Here, (n - 1)th power of base matrix represents the nth term
        for(ll p = 60; p >= 0; p--)
        {
            if((n >> p) & 1)
            {

                for(ll i = 0; i < row; i++)
                {
                    tmp = 0;
                    for(ll j = 0; j < col; j++)
                    {
                        tmp += exponents[p][i][j] * vect[j];
                        while(tmp >= MOD2) /// faster, because we can do it by subtraction
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
    //gcd(F(a),F(b))=F(gcd(a,b))

    ll m, l, r, k;
    cin >> m >> l >> r >> k;

    ll idx = 1;
    for(ll i = 1; i * i <= r; i++) {
        ll x = i;
        if(r/x - (l-1)/x >= k) idx = max(idx, x);

        x = r/i;
        if(r/x - (l-1)/x >= k) idx = max(idx, x);
    }

    MOD = m, MOD2 = MOD*MOD;
    MatExpo ex = MatExpo();

    cout << ex.ans(idx-1) << EL;

    return 0;
}
