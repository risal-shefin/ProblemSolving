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

const ll sz = 1e4 + 10;
ll ara[sz];
stack <int> v;
bool used[sz];

inline ll query(ll x, ll y)
{
    cout << "? " << x << " " << y << endl;
    ll got; cin >> got;
    return got;
}

int main()
{
    fastio;
    ll n; cin >> n;

    for1(i, n) v.push(i);

    while(v.size() >= 2) {
        ll j = v.top(); v.pop();
        ll i = v.top(); v.pop();

        ll q1 = query(i, j), q2 = query(j, i);

        if(q1 > q2) ara[i] = q1, used[q1] = 1, v.push(j);
        else ara[j] = q2, used[q2] = 1, v.push(i);
    }

    for1(i, n) if(!used[i]) ara[ v.top() ] = i;

    cout << "!";
    for1(i, n) cout << " " << ara[i];
    cout << endl;

    return 0;
}
