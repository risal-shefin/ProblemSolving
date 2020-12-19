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

char vict[100][100];

int main()
{
    vict['P']['R'] = vict['R']['P'] = vict['P']['P'] = 'P';
    vict['P']['S'] = vict['S']['P'] = vict['S']['S'] = 'S';
    vict['R']['S'] = vict['S']['R'] = vict['R']['R'] = 'R';

    fastio;

    ll n, k;
    string s;
    cin >> n >> k >> s;

    while(k--) {
        const string s2 = s+s;

        for0(i, s.length())
            s[i] = vict[s2[2*i]][s2[2*i+1]];
    }

    cout << s[0] << EL;

    return 0;
}