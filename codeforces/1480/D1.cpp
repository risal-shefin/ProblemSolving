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

const ll sz = 1e5 + 10;
ll ara[sz], tmp[sz], cnt[sz];
bool took[sz], mark[sz];

int main()
{
    ll n, idx = 0;
    cin >> n;

    for1(i, n) sl(tmp[i]);

    for1(i, n) {

        ll stop = i;

        for(ll j = i; j <= n; j++) {
            if(tmp[j] != tmp[i])
                break;

            stop = j;
        }

        ll mil = stop - i +1;

        ara[++idx] = tmp[i];

        if(mil > 1) {
            mark[idx] = 1;
            ara[++idx] = tmp[i];
        }

        i = stop;
    }

    ll ans = 0, prv = -1, unq = 0;
    vector <int> lst;

    for1(i, idx) {
        if(mark[i]) {

            if(ara[i] != prv) {
                ans += 2, prv = ara[i];
                ans += unq;
            }
            else {
                ans += 2, prv = ara[i];

                ll rest = unq - cnt[ ara[i] ];
                if(rest == cnt[ ara[i] ] + 1)
                    ans += (unq-1);
                else
                    ans += unq;
            }

            unq = 0;
            i++;

            for(int &val : lst) cnt[val]--;
            lst.clear();
        }
        else {
            unq++;
            lst.pb(ara[i]);
            cnt[ ara[i] ]++;
        }
    }
    ans += unq;

    cout << ans << EL;

    return 0;
}

