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

const ll sz = 55, lsz = 25;
char s[sz][lsz];
ll cst[sz], dp[lsz][sz][2], len[sz], n;

bool isPal(ll idx, ll start, ll stop)
{
    for(ll i = start, j = stop; i <= j; i++, j--) {
        if(s[idx][i] != s[idx][j])
            return 0;
    }
    return 1;
}

ll solve(ll start, ll last, bool isLeft)
{
    ll &ret = dp[start][last][isLeft];
    if(ret != -1)
        return ret;

    ret = inf;

    for1(i, n) {

        if(isLeft) {
            ll ptr1 = start, ptr2 = len[i];

            for(; ptr1 <= len[last] && ptr2 >= 1; ptr1++, ptr2--) {
                if(s[last][ptr1] != s[i][ptr2]) {
                    ptr2 = -1;
                    break;
                }
            }

            if(ptr2 == -1) continue;
            //cout << i << " " << ptr1 << " " << ptr2 << " " << len[last] << endl;

            if(ptr1 > len[last] && ptr2 < 1)
                ret = min(ret, cst[i]);
            else if(ptr1 > len[last]) {

                if(isPal(i, 1, ptr2))
                    ret = min(ret, cst[i]);
                else
                    ret = min(ret, cst[i] + solve(ptr2, i, 0));
            }
            else {
                //cout << ptr1 << " " << len[last] << endl;
                if(isPal(last, ptr1, len[last]))
                    ret = min(ret, cst[i]);
                else
                    ret = min(ret, cst[i] + solve(ptr1, last, 1));
            }
        }
        else {
            ll ptr1 = 1, ptr2 = start;

            for(; ptr1 <= len[i] && ptr2 >= 1; ptr1++, ptr2--) {
                if(s[i][ptr1] != s[last][ptr2]) {
                    ptr2 = -1;
                    break;
                }
            }

            if(ptr2 == -1) continue;

            if(ptr1 > len[i] && ptr2 < 1)
                ret = min(ret, cst[i]);
            else if(ptr1 > len[i]) {

                if(isPal(last, 1, ptr2))
                    ret = min(ret, cst[i]);
                else
                    ret = min(ret, cst[i] + solve(ptr2, last, 0));
            }
            else {

                if(isPal(i, ptr1, len[i]))
                    ret = min(ret,cst[i]);
                else
                    ret = min(ret, cst[i] + solve(ptr1, i, 1));
            }
        }
    }

    return ret;
}

int main()
{
    cin >> n;

    for1(i, n) {
        scanf("%s %lld", s[i]+1, &cst[i]);
        len[i] = strlen(s[i]+1);
    }

    ll ans = inf;
    ms(dp, -1);
    for1(i, n) {

        if(isPal(i, 1, len[i])) {
            ans = min(ans, cst[i]);
            continue;
        }

        ans = min(ans, cst[i] + solve(1, i, 1));
    }

    if(ans >= inf) cout << -1 << EL;
    else cout << ans << EL;

    return 0;
}
