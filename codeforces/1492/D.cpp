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

int main()
{
    fastio;

    ll a, b, k;
    cin >> a >> b >> k;

    if(k == 0) {
        cout << "Yes\n";

        for1(i, b) cout << "1";
        for1(i, a) cout << "0";
        cout << EL;

        for1(i, b) cout << "1";
        for1(i, a) cout << "0";
        cout << EL;

        return 0;
    }

    string x, y;

    if(b == 1 || a == 0) {
        cout << "No\n";
        return 0;
    }

    x.pb('1'), y.pb('1');
    b--;

    if(k > (a+b-1)) {
        cout << "No\n";
        return 0;
    }

    if(k <= a) {
        ll rz = a-k;

        for1(i, b-1) {
            x.pb('1');
            y.pb('1');
        }
        for1(i, rz) {
            x.pb('0');
            y.pb('0');
        }
        x.pb('1');
        y.pb('0');

        for1(i, k) {
            x.pb('0');

            if(i == k) y.pb('1');
            else y.pb('0');
        }

        cout << "Yes\n" << x << EL << y << EL;
        return 0;
    }

    ll need = k-a, rest = b-need;

    for1(i, rest) {
        x.pb('1');

        if(i == rest) y.pb('0');
        else y.pb('1');
    }

    for1(i, need) {
        x.pb('1');
        y.pb('1');
    }

    for1(i, a) {
        x.pb('0');

        if(i == a) y.pb('1');
        else y.pb('0');
    }

    cout << "Yes\n" << x << EL << y << EL;

    return 0;
}

