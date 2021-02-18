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

const ll sz = 1009;
struct info {
    ll x, y;
} ara[sz];

vector <ll> X, Y, dx, dy;

void clr()
{
    X.clear(), Y.clear(), dx.clear(), dy.clear();
}

int main()
{
    ll t;
    cin >> t;

    while(t--) {
        ll n; sl(n);

        for1(i, n) {
            ll x, y;
            sl(x), sl(y);

            ara[i] = {x, y};

            X.pb(x), Y.pb(y);
        }
        sort(all(X)), sort(all(Y));
        X.erase(unique(all(X)), X.end());
        Y.erase(unique(all(Y)), Y.end());

//        if(Y.size() == 1) {
//            ll mx = X.back(), mn = X[0];
//            pf("%lld\n", mx-mn+1);
//            clr();
//            continue;
//        }
//        if(X.size() == 1) {
//            ll mx = Y.back(), mn = Y[0];
//            pf("%lld\n", mx-mn+1);
//            clr();
//            continue;
//        }

        for(ll i = 0; i < X.size(); i++) {
            ll sum = 0;
            for1(j, n) {
                sum += abs(ara[j].x - X[i]);
            }

            dx.pb(sum);
        }

        for(ll i = 0; i < Y.size(); i++) {
            ll sum = 0;
            for1(j, n) {
                sum += abs(ara[j].y - Y[i]);
            }

            dy.pb(sum);
        }

        sort(all(dx));
        sort(all(dy));

        ll mn = dx[0] + dy[0];

        ll mnX = inf, mxX = -inf, mnY = inf, mxY = -inf;

        for(ll i = 0; i < X.size(); i++) {
            ll sum = 0;
            for1(j, n) {
                sum += abs(ara[j].x - X[i]);
            }

            if(sum == dx[0]) {
                mnX = min(mnX, X[i]);
                mxX = max(mxX, X[i]);
            }
        }

        for(ll i = 0; i < Y.size(); i++) {
            ll sum = 0;
            for1(j, n) {
                sum += abs(ara[j].y - Y[i]);
            }

            if(sum == dy[0]) {
                mnY = min(mnY, Y[i]);
                mxY = max(mxY, Y[i]);
            }
        }

        pf("%lld\n", (mxY-mnY+1)*(mxX-mnX+1));

        clr();
    }

    return 0;
}
