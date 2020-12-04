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

const ll sz = 2009;
ll ans[10], row1[10], row2[10], col1[10], col2[10];
char s[sz][sz];

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        ll n;
        sl(n);

        for1(i, n)
            scanf("%s", s[i]+1);

        for0(d, 10) row1[d] = col1[d] = inf, row2[d] = col2[d] = -inf;

        for1(i, n) {
            for1(j, n) {
                ll now = s[i][j] - '0';

                row1[now] = min(row1[now], i);
                col1[now] = min(col1[now], j);

                row2[now] = max(row2[now], i);
                col2[now] = max(col2[now], j);
            }
        }

        ms(ans, 0);

        for0(d, 10) {

            char ch = d + '0';

            for1(i, n) {
                ll l = -1, r = -1;

                for1(j, n) {

                    if(s[i][j] != ch)
                        continue;

                    ll h = abs(i - row1[d]), base = max(j-1, n-j);
                    ans[d] = max(ans[d], base*h);

                    h = abs(i - row2[d]), base = max(j-1, n-j);
                    ans[d] = max(ans[d], base*h);

                    h = abs(j - col1[d]), base = max(i-1, n-i);
                    ans[d] = max(ans[d], base*h);

                    h = abs(j - col2[d]), base = max(i-1, n-i);
                    ans[d] = max(ans[d], base*h);

                    if(l == -1)
                        l = j;
                    else
                        r = max(r, j);
                }

                if(l == -1 || r == -1)
                    continue;

                ll base = r-l;
                ll h = max(i-1, n-i);
                ans[d] = max(ans[d], base*h);
            }
        }

        for0(d, 10) {

            char ch = d + '0';

            for1(j, n) {
                ll l = -1, r = -1;

                for1(i, n) {

                    if(s[i][j] != ch)
                        continue;

                    if(l == -1)
                        l = j;
                    else
                        r = max(r, j);
                }

                if(l == -1 || r == -1)
                    continue;

                ll base = r-l;
                ll h = max(j-1, n-j);
                ans[d] = max(ans[d], base*h);
            }
        }

        for0(d, 10)
            pf("%lld ", ans[d]);

        pn;
    }

    return 0;
}
