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

const ll sz = 60;
ll ara[sz], temp[sz], used[60];
vector < vector <int> > ans;

int main()
{
    ll n; sl(n);
    for1(i, n) sl(ara[i]);

    while(!is_sorted(ara+1, ara+n+1)) {

        ms(used, 0);
        used[0] = 1;

        vector <int> part;

        for1(i, n) {
            ll now = ara[i];
            used[now] = 1;

            if(used[now-1])
                continue;

            if(i != 1) part.pb(i-1);

            ll nxt;
            for(ll j = i; j <= n; j++) {
                if(ara[j] == now-1) {
                    nxt = j;
                    break;
                }
            }

            ll stop;
            for(ll j = i; j <= n; j++) {
                if(ara[j] - now != j-i)
                    break;

                stop = j;
            }

            part.pb(stop-i+1);
            part.pb(nxt-stop);
            if(nxt != n) part.pb(n-nxt);

            break;
        }
        ans.pb(part);

        ll last = n, idx = 0;
        for(ll i = (ll)part.size() - 1; i >= 0; i--) {

            ll p = part[i];

            for(ll i = last-p+1; i <= last; i++)
                temp[++idx] = ara[i];

            last = last - p;
        }

        for1(i, n) ara[i] = temp[i];
    }

    cout << ans.size() << EL;

    for(vector <int> &part : ans) {

        pf("%d", (int)part.size());
        for(int &p : part) pf(" %d", p);
        pn;
    }

    return 0;
}
