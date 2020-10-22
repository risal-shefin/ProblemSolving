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

ll tr, tc, ans = inf;
ll c[6];

ll dr[] = {1, 0, -1, -1, 0, 1};
ll dc[] = {1, 1, 0, -1, -1, 0};

int main()
{
    ll t; sl(t);

    while(t--) {
        sl(tr), sl(tc);
        for0(i, 6) sl(c[i]);

        if(tr == 0 && tc == 0) {
            pf("0\n");
            continue;
        }

        ll ans = inf;
        for0(i, 6) {
            for0(j, 6) {

                if(i == j) continue;

                ll mvi, mvj;

                ll nom = tr*dc[i] - tc*dr[i];
                ll den = dr[j]*dc[i] - dc[j]*dr[i];

                if(nom == 0)
                    mvj = 0;
                else if(den == 0 || nom%den != 0 || nom/den < 0)
                    continue;
                else
                    mvj = nom / den;

                nom = tr+tc - mvj*(dr[j]+dc[j]);
                den = dr[i] + dc[i];

                if(nom == 0)
                    mvi = 0;
                else if(den == 0 || nom%den != 0 || nom/den < 0)
                    continue;
                else
                    mvi = nom / den;

                ans = min(ans, mvi*c[i] + mvj*c[j]);
             }
        }

        pf("%lld\n", ans);
    }

    return 0;
}
