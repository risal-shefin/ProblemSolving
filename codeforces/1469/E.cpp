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

const ll sz = 1e6 + 10;
char s[sz];
ll zsum[sz];

vector <string> lst;
string make;

void gen(ll pos, ll n)
{
    if(pos > n) {
        lst.pb(make);
        return;
    }

    make.pb('0');
    gen(pos+1, n);
    make.pop_back();

    make.pb('1');
    gen(pos+1, n);
    make.pop_back();
}

int main()
{
    ll t; sl(t);

    while(t--) {
        ll n, k;
        sl(n), sl(k);

        scanf("%s", s+1);

        ll z = 0, got = 1;
        for1(i, n) {
            z += (s[i] == '0');
            zsum[i] = zsum[i-1] + (s[i] == '0');

            if(i < k)
                continue;

            if(i-k >= 1) z -= (s[i-k] == '0');

            if(z == 0)
                got = 0;
        }

        if(got) {
            pf("YES\n");
            for1(i, k) pf("0");
            pn;
            continue;
        }

        ll totSub = n-k+1, minNeed = k;

        for1(i, k) {

            if((1LL << i) > totSub) {
                minNeed = i;
                break;
            }
        }

        make = "";
        lst.clear();
        gen(1, minNeed);

        unordered_set <string> bad;

        for(ll i = n-minNeed+1; i >= 1; i--) {

            ll rest = k-minNeed, start = i-rest;
            if(start < 1) break;

            if((zsum[i-1] - zsum[start-1]) > 0)
                continue;

            string now = "";

            for(ll j = i; j <= i+minNeed-1; j++) {
                if(s[j] == '0') now.pb('1');
                else now.pb('0');
            }

            bad.insert(now);
        }

        got = 0;
        for(string &s : lst) {
            if(bad.find(s) == bad.end()) {

                pf("YES\n");
                for(ll i = 1; i <= k-minNeed; i++) pf("0");
                pf("%s\n", s.c_str());

                got = 1;
                break;
            }
        }

        if(!got) pf("NO\n");
    }

    return 0;
}
