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

const ll sz = 305;
ll marked[sz], edge, notMarked;
bool check[sz][sz], got[sz];

void addEdge(ll u, ll v)
{
    if(u > v) swap(u, v);
    if(check[u][v]) return;

    check[u][v] = 1;
    pf("%lld %lld\n", u, v);
    edge++;
}

int main()
{
    ll n, m, k;
    cin >> n >> m >> k;

    for1(i, k) sl(marked[i]), got[ marked[i] ] = 1;

    ll validEdge = n*(n-1) / 2 - (k-1);

    if(m > validEdge || k == n) {
        pf("-1\n");
        return 0;
    }

    edge = 1, notMarked = -1;

    for1(i, n) {

        if(!got[i]) {
            addEdge(marked[1], i);

            if(notMarked == -1) notMarked = i;
        }
    }

    for(ll i = 2; i <= k; i++)
        addEdge(marked[i], notMarked);

    for(ll i = 1; i <= n && edge <= m; i++) {

        if(i == marked[1]) continue;

        for(ll j = i+1; j <= n && edge <= m; j++) {

            if(j == marked[1])
                continue;

            addEdge(i, j);
        }
    }

    return 0;
}
