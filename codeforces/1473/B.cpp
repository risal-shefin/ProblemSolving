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
    ll t;
    cin >> t;

    while(t--) {
        string a, b;
        cin >> a >> b;

        bool ok = 0;
        ll mxLen = a.length() * b.length();

        if(a.length() < b.length())
            swap(a, b);

        for(ll i = 1; i*a.length() <= mxLen; i++) {

            ll tot = i*a.length();

            if(tot % b.length() != 0)
                continue;

            bool done = 1;

            for(ll i = 1, j = 0, k = 0; i <= tot; i++) {

                if(a[j] != b[k]) {
                    done = 0;
                    break;
                }

                j++, k++;
                if(j == a.length()) j = 0;
                if(k == b.length()) k = 0;
            }

            if(done) {
                for(ll i = 1, j = 0; i <= tot; i++) {
                    cout << a[j];

                    j++;
                    if(j == a.length()) j = 0;
                }
                cout << EL;
                ok = 1;
                break;
            }
        }

        if(!ok) cout << -1 << EL;
    }

    return 0;
}
