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
ll ara[sz];
multiset <ll> lst;

inline bool check(ll n, ll k)
{
    lst.clear();

    ll s = 0, l = 0;

    for1(i, n) {
        if(ara[i] >= k) l++;
        else s++;

        lst.insert(l-s);
    }

    s = 0, l = 0;

    for1(i, n) {
        if(ara[i] >= k) l++;
        else s++;

        lst.erase(lst.find(l-s));

        if(ara[i] != k)
            continue;

        if(lst.find(l-s) != lst.end() || lst.find(1+ (l-s)) != lst.end())
            return true;
    }

    return false;
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {

        ll n, k, ok = 0, exist = 0;
        sl(n), sl(k);

        for1(i, n) sl(ara[i]), exist |= (ara[i] == k);

        if(!exist) {
            pf("no\n");
            continue;
        }

        if(n == 1) {
            pf("yes\n");
            continue;
        }

        for1(i, n-1) if(ara[i] == k && ara[i+1] >= k) ok = 1;

        if(ok) {
            pf("yes\n");
            continue;
        }

        ok |= check(n, k);

        reverse(ara+1, ara+n+1);

        ok |= check(n, k);

        for1(i, n-1) {
            if(ara[i] > k && ara[i+1] > k) ok = 1;

            if(i + 2 <= n && ara[i] > k && ara[i+2] > k) ok = 1;
        }

        if(ok) pf("yes\n");
        else pf("no\n");
    }

    return 0;
}
