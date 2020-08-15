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
#define inf (1LL << 62)
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

const ll sz = 5005;
ll p[sz], c[sz], n, k, lev[sz];

ll dfs(ll u, ll lv)
{
    if(lv > k)
        return 0;

    if(lev[u] != -1) {
        ll cycLen = lv - lev[u], rest = k - lv + 1, now = u, mx = 0, val;

        ll sum = 0;
        for(ll i = 1; i <= cycLen && i <= rest; i++) {
            now = p[now], val = c[now];
            sum += val;

            mx = max(mx, sum);
        }
        if(sum <= 0) return mx;

        ll cycCnt = rest / cycLen, cycSum = sum;
        rest = rest % cycLen;

        sum = mx = 0, now = u;
        for(ll i = 1; i <= rest; i++) {
            now = p[now], val = c[now];
            sum += val;

            mx = max(mx, sum);
        }

        ll ret = cycSum*cycCnt + mx;

        if(cycCnt > 0) {

            sum = mx = 0, now = u;
            for(ll i = 1; i <= cycLen; i++) {
                now = p[now], val = c[now];
                sum += val;

                mx = max(mx, sum);
            }

            ret = max(ret, cycSum*(cycCnt-1) + mx);
        }

        return ret;
    }

    lev[u] = lv;

    ll nxt = p[u], val = c[nxt];
    return val + max(0LL, dfs(nxt, lv+1));
}

int main()
{
    cin >> n >> k;
    for1(i, n) sl(p[i]);
    for1(i, n) sl(c[i]);

    ll ans = -inf;

    for1(i, n) {
        ms(lev, -1);

        ans = max(ans, dfs(i, 1));
    }

    cout << ans << endl;

    return 0;
}
