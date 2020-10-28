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

const ll sz = 3e5 + 10;
ll ara[sz], inv[30][2], node=1;

struct info {
    int nxt[2];
    vector <int> lst;
} trie[sz*30*2];

void add(int num, int idx)
{
    int cur = 1;
    rep0(i, 30) {
        int b = (num>>i) & 1;

        if(!trie[cur].nxt[b])
            trie[cur].nxt[b] = ++node;

        cur = trie[cur].nxt[b];

        trie[cur].lst.pb(idx);
    }
}

void calc_inv(int cur, int bit)
{
    int c1 = trie[cur].nxt[0], c2 = trie[cur].nxt[1];

    vector <int> &lst0 = trie[c1].lst;
    vector <int> &lst1 = trie[c2].lst;

    for(int &idx : lst1) {
        int pos = upper_bound(all(lst0), idx) - lst0.begin();
        inv[bit][0] += (lst0.size() - pos);
    }

    for(int &idx : lst0) {
        int pos = upper_bound(all(lst1), idx) - lst1.begin();
        inv[bit][1] += (lst1.size() - pos);
    }

    if(bit == 0) return;

    if(c1 != 0) calc_inv(c1, bit-1);
    if(c2 != 0) calc_inv(c2, bit-1);
}

int main()
{
    ll n; sl(n);

    for1(i, n) {
        sl(ara[i]);
        add(ara[i], i);
    }

    calc_inv(1, 29);

    ll ans = 0, x = 0;

    rep0(i, 30) {

        if(inv[i][1] < inv[i][0]) {
            ans += inv[i][1];
            x |= (1LL << i);
        }
        else
            ans += inv[i][0];
    }

    cout << ans << " " << x << EL;

    return 0;
}
