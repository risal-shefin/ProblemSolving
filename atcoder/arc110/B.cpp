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

    ll n, tot = 1e10;
    cin >> n;

    string s;
    cin >> s;

    if(s.length() == 1) {
        if(s[0] == '1')
            cout << tot*2 << EL;
        else
            cout << tot << EL;

        return 0;
    }

    string got = "110";
    ll start;

    if(s[0] == '1' && s[1] == '1') {
        start = 0;
    }
    else if(s[0] == '1' && s[1] == '0') {
        start = 1;
    }
    else if(s[0] == '0' && s[1] == '1') {
        start = 2;
    }
    else {
        cout << 0 << EL;
        return 0;
    }

    bool valid = 1;
    ll now = start;

    for(ll i = 0; i < s.length(); i++) {
        if(s[i] != got[now]) {
            valid = 0;
            break;
        }

        now++;
        if(now == 3) now = 0;
    }

    if(!valid) {
        cout << 0 << EL;
        return 0;
    }

    ll totLen = tot * 3;
    ll lim = totLen - s.length() + 1;

    ll ans = (lim - (start+1) + 1) / 3;
    if((lim - (start+1) + 1) % 3 != 0)
        ans++;

    cout << ans << EL;

    return 0;
}
