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

string s;

bool check(string s1, string s2)
{
    ll ptr = 0;
    for(ll i = 0; i < s1.length(); i++) {
        if(ptr >= s.length())
            return 0;

        if(s1[i] != s[ptr])
            return 0;

        ptr++;
    }

    ll ptr2 = s.length() - 1, len = s2.length();

    for(ll j = len-1; j >= 0; j--) {
        if(ptr2 < ptr)
            return 0;

        if(s2[j] != s[ptr2])
            return 0;

        ptr2--;
    }

    return 1;
}

int main()
{
    fastio;
    ll t;
    cin >> t;

    while(t--) {
        ll n;
        cin >> n >> s;

        if(check("2020", "") || check("202", "0") || check("20", "20") || check("2", "020") || check("", "2020"))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
