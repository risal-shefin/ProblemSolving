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

struct node {
    int id;
    char ch;
};

const bool operator <(const node &a, const node &b) {
    return a.id < b.id;
}
set <node> lst;

char s[sz], fDiff[sz];

struct info {
    ll len;
    string s;
};
vector <info> ans;

void make_string()
{
    string now = "";

    if(lst.size() <= 10) {
        for(const node &nd : lst)
            now.pb(nd.ch);

        ans.pb({now.size(), now});
        return;
    }

    auto it = lst.begin();
    for(ll i = 1; i <= 5; i++, ++it)
        now.pb(it->ch);

    now.pb('.'), now.pb('.'), now.pb('.');

    it = --lst.end();
    --it;
    for(ll i = 1; i <= 2; i++, ++it)
        now.pb(it->ch);

    ans.pb({lst.size(), now});
}

int main()
{
    scanf("%s", s+1);
    ll len = strlen(s+1);

    fDiff[len+1] = '\0';
    rep1(i, len) {

        lst.insert({i, s[i]});
        string now = "";

        if(lst.size() == 1) {

            now.pb(s[i]);
            ans.pb({now.size(), now});

            fDiff[i] = '\0';
            continue;
        }

        auto it1 = ++lst.begin();

        if(s[i] == it1->ch) {

            if(i+1 == it1->id && fDiff[i+1] < s[i]) {
                lst.erase(lst.begin()), lst.erase(lst.begin());
                fDiff[i] = fDiff[i+2];
            }
            else
                fDiff[i] = fDiff[i+1];
        }
        else
            fDiff[i] = it1->ch;

        make_string();
    }

    reverse(all(ans));
    for(info &Info : ans) {
        pf("%lld %s\n", Info.len, Info.s.c_str());
    }

    return 0;
}
