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

const ll sz = 105;
ll mat[sz][sz];
ll cnt[sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        ll mn = inf, pt;

        rep1(p, 300) {

            ll ok = 1, draw = 0;
            ms(cnt, 0);

            for(ll i = 1; i <= n; i++) {
                for(ll j = i+1; j <= n; j++) {

                    ll need = p - cnt[i];

                    if(need >= 3) {
                        mat[i][j] = 1;
                        cnt[i] += 3;
                    }
                    else if(need > 0) {
                        mat[i][j] = 0;
                        cnt[i]++, cnt[j]++, draw++;
                    }
                    else {
                        mat[i][j] = -1;
                        cnt[j] += 3;
                    }
                }

                if(cnt[i] != p) {
                    ok = 0;
                    break;
                }
            }
            //cout << p << " " << ok << EL;

            if(ok) {
                if(mn > draw) {
                    mn = draw;
                    pt = p;
                }
            }
        }

        ms(cnt, 0);
        for(ll i = 1; i <= n; i++) {
            for(ll j = i+1; j <= n; j++) {

                ll need = pt - cnt[i];

                if(need >= 3) {
                    mat[i][j] = 1;
                    cnt[i] += 3;
                }
                else if(need > 0) {
                    mat[i][j] = 0;
                    cnt[i]++;
                }
                else {
                    mat[i][j] = -1;
                    cnt[j] += 3;
                }
            }
        }

        for(ll i = 1; i <= n; i++)
            for(ll j = i+1; j <= n; j++)
                pf("%lld ", mat[i][j]);

        pn;
    }

    return 0;
}
