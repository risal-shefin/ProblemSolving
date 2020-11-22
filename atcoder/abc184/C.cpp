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
    ll r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    if(r1 == r2 && c1 == c2) {
        cout << 0 << endl;
        return 0;
    }
    else if(abs(r1-r2) + abs(c1-c2) <= 3) {
        cout << 1 << endl;
        return 0;
    }

    ll f1 = r2+c2, f2 = r2-c2;
    ll k1 = r1+c1, k2 = r1-c1;

    if(f1 == k1 || f2 == k2) {
        cout << 1 << endl;
        return 0;
    }
    if(f1 % 2 == k1 % 2 || f2 % 2 == k2 % 2) {
        cout << 2 << endl;
        return 0;
    }
    if(abs(k1-f1) <= 3 || abs(k2-f2) <= 3) {
        cout << 2 << endl;
        return 0;
    }

    cout << 3 << EL;

    return 0;
}
