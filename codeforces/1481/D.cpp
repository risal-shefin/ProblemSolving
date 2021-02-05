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

const ll sz = 1009;
char mat[sz][sz];
ll togo[sz][2];

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n, m;
        sl(n), sl(m);

        for1(i, n)
            cin >> (mat[i]+1);

        if(m == 1) {
            pf("YES\n");
            pf("1 2\n");
            continue;
        }

        ll v1 = -1, v2 = -1;

        for1(i, n) {
            for1(j, n) {
                if(i == j)
                    continue;

                if(mat[i][j] == mat[j][i]) {
                    v1 = i, v2 = j;
                    break;
                }
            }
            if(v1 != -1)
                break;
        }

        if(v1 == -1 && (m & 1)) v1 = 1, v2 = 2;

        if(v1 != -1) {
            pf("YES\n");

            bool state = 0;
            for1(i, m+1) {
                if(!state) pf("%lld ", v1);
                else pf("%lld ", v2);

                state ^= 1;
            }
            pn;
            continue;
        }

        ll v3 = -1;
        for1(i, n)
            for0(j, 2)
                togo[i][j] = -1;

        for1(i, n) {
            for1(j, n) {
                if(i == j)
                    continue;

                ll now = mat[i][j] - 'a';
                togo[i][now] = j;
            }
        }

        for1(i, n) {
            for1(j, n) {
                if(i == j)
                    continue;

                ll now = mat[i][j] - 'a';
                if(togo[j][now] == -1)
                    continue;

                v1 = i, v2 = j, v3 = togo[j][now];
            }
        }

        if(v1 == -1) {
            pf("NO\n");
            continue;
        }

        pf("YES\n");
        ll ptr = 1, flag = 0;

        if((m/2) % 2 == 0) ptr = 2;

        for1(i, m+1) {

            if(ptr == 1) pf("%lld ", v1);
            else if(ptr == 2) pf("%lld ", v2);
            else pf("%lld ", v3);

            if(ptr == 3)
                flag = 1;
            if(ptr == 1)
                flag = 0;

            if(!flag) ptr++;
            else ptr--;
        }
        pn;
    }

    return 0;
}
