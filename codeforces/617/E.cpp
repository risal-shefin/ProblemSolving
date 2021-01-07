// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll int
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

#define LL long long

const ll sz = 1e5 + 10, block = 350, MAX_N = 2e6 + 10;
LL tot[block][block];
ll n, m, k, ara[sz], pre[sz], cnt[MAX_N], idx, vis[MAX_N];
vector <ll> pos[MAX_N];

void preprocess()
{
    for(ll b1 = 0; b1*block <= n; b1++) {

        ll pref = 0;
        LL counter = 0;
        idx++;

        for(ll i = b1*block; i <= n; i++) {

            pref ^= ara[i];
            ll need = pref^k;

            //if(b1 == 1) cout << i << " || " << pref << " " << need << endl;

            if(vis[need] == idx) {
                counter += cnt[need];
                //if(b1 == 1) cout << i << endl;
            }
            tot[b1][i/block] = counter;

            if(vis[pref] != idx)
                cnt[pref] = 0;

            cnt[pref]++, vis[pref] = idx;
        }
    }

    for(ll i = 0; i <= n; i++) {
        if(i != 0) pre[i] = ara[i] ^ pre[i-1];
        pos[ pre[i] ].pb(i);
    }
}

ll countX(ll l, ll r, ll X)
{
    if(l > r) return 0;

    ll lo = 0, hi = -1 + (ll)pos[X].size(), lft = -1, rgt = -1;
    while(lo <= hi) {
        ll mid = lo+hi >> 1;

        if(pos[X][mid] < l)
            lo = mid+1;
        else {
            hi = mid-1;
            if(pos[X][mid] <= r)
                lft = mid;
        }
    }
    if(lft == -1) return 0;

    lo = 0, hi = -1 + (ll)pos[X].size();
    while(lo <= hi) {
        ll mid = lo+hi>>1;

        if(pos[X][mid] > r)
            hi = mid-1;
        else {
            lo = mid+1;
            if(pos[X][mid] >= l)
                rgt = mid;
        }
    }
    if(rgt == -1) return 0;

    return (rgt-lft+1);
}

LL query(ll l, ll r)
{
    ll lb = l/block, rb = r/block;
    LL ret = 0;

    if(lb == rb) {
        idx++;
        ll pref = 0;

        for(ll i = l; i <= r; i++) {

            pref ^= ara[i];
            ll need = pref^k;

            if(vis[need] == idx)
                ret += cnt[need];

            if(vis[pref] != idx)
                cnt[pref] = 0;

            cnt[pref]++, vis[pref] = idx;
        }

        return ret;
    }

    if(lb+1 < rb)
        ret = tot[lb+1][rb-1];

    //cout << (lb+1)*block << " || " << rb*block-1 << " " << ret << EL;

    for(ll i = l; i < (lb+1)*block; i++) {
        ll need = pre[i]^k;
        ret += countX(i+1, rb*block-1, need);
    }

    for(ll i = r; i >= rb*block; i--) {
        ll need = pre[i]^k;
        ret += countX(l, i-1, need);
    }

    return ret;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    cin >> n >> m >> k;

    for1(i, n)
        si(ara[i]);

//    for1(i, n) {
//        ll now = 0;
//        for(ll j = i; j <= n; j++) {
//            now ^= ara[j];
//
//            if(now == k)
//                cout << i << " " << j << endl;
//        }
//    }

    preprocess();

    while(m--) {
        ll l, r;
        si(l), si(r);

        l--;
        pf("%lld\n", query(l, r));
    }

    return 0;
}
