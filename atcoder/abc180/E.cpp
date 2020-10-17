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

const ll sz = 20;
ll dist[(1<<17)][sz], n, lim;
ll ara[sz][3];

struct node {
    ll msk, id, d;
};
const bool operator <(const node &a, const node &b) {
    return a.d > b.d;
}

int main()
{
    sl(n);
    lim = (1 << n);

    for0(i, lim)
        for0(j, n)
            dist[i][j] = inf;

    for0(i, n) {
        for0(j, 3) sl(ara[i][j]);
    }

    priority_queue <node> pq;
    pq.push({1, 0, 0});
    dist[1][0] = 0;

    while(!pq.empty()) {
        node now = pq.top();
        pq.pop();

        if(dist[now.msk][now.id] != now.d)
            continue;

        for0(i, n) {
            ll nmsk = now.msk | (1<<i);
            ll ndist = abs(ara[now.id][0] - ara[i][0]) + abs(ara[now.id][1] - ara[i][1]) + max(0LL, ara[i][2] - ara[now.id][2]);

            if(dist[nmsk][i] > now.d + ndist) {
                dist[nmsk][i] = now.d + ndist;
                pq.push({nmsk, i, now.d + ndist});
            }
        }
    }

    cout << dist[lim-1][0] << EL;

    return 0;
}
