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
#define inf (1LL << 62)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; i++)
#define for0(i, stop) for(ll i = 0; i < stop; i++)
#define rep1(i, start) for(ll i = start; i >= 1; i--)
#define rep0(i, start) for(ll i = (start-1); i >= 0; i--)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 1e6 + 10;

struct trie {
    int nxt[26], idx;

    trie() {
        for0(i, 26) nxt[i] = -1;
        idx = -1;
    }
} tr[sz];

int idt = 0, pos[sz];

void add(int cur, ll v)
{
    if(tr[cur].nxt[v] == -1)
        tr[cur].nxt[v] = ++idt;
}

ll ara[sz], ans[sz], tree[4*sz], lazy[4*sz], num = 0;

void prop(ll lo, ll hi, ll node)
{
    if(lo == hi) return;

    tree[node<<1] += lazy[node];
    tree[node<<1 | 1] += lazy[node];

    lazy[node<<1] += lazy[node];
    lazy[node<<1|1] += lazy[node];

    lazy[node] = 0;
}

void update(ll lo, ll hi, ll l, ll r, ll v, ll node)
{
    if(lazy[node])  prop(lo, hi, node);
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tree[node] += v;
        lazy[node] += v;
        return;
     }

     ll mid = (lo+hi) >> 1;
     update(lo, mid, l, r, v, node<<1);
     update(mid+1, hi, l, r, v, node<<1 | 1);

     tree[node] = min(tree[node<<1], tree[node<<1 | 1]);
}

ll query(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lazy[node])  prop(lo, hi, node);
    if(lo > r || hi < l)
        return inf;
    if(lo >= l && hi <= r)
        return tree[node];

    ll mid = lo+hi>>1;
    return min( query(lo, mid, l, r, node<<1),
               query(mid+1, hi, l, r, node<<1 | 1));
}

void solve(ll cur, ll d, ll c)
{
    ll v = query(0, sz, d, d, 1);
    update(0, sz, d, d, -v, 1);

    ll cst = c;
    if(tr[cur].idx != -1) {
        ll q = query(0, sz, 0, d-1, 1);
        cst = min(q+1, cst);
        update(0, sz, d, d, cst, 1);
        ans[tr[cur].idx] = cst;

        update(0, sz, 0, d, 1, 1);
    }
    else
        update(0, sz, d, d, cst, 1);

    for0(i, 26) {
        if(tr[cur].nxt[i] == -1)
            continue;
        solve(tr[cur].nxt[i], d+1, cst+1);
    }
}

int main()
{
    pos[0] = ++idt;
    ll n;
    cin >> n;
    for1(i, n) {
        ll p;
        char ch;
        scanf("%lld %c", &p, &ch);

        add(pos[p], ch-'a');
        pos[i] = tr[ pos[p] ].nxt[ch-'a'];
    }

    ll k;
    cin >> k;
    for1(i, k) {
        sl(ara[i]);
        tr[ pos[ ara[i] ] ].idx = i;
    }

    solve(1, 0, 0);
    for1(i, k) {
        if(i != 1) pf(" ");
        pf("%lld", ans[i]);
    }
    pn;

    return 0;
}

