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

//unordered_set <int> lst;
//
//void dfs(ll u, ll d=0)
//{
//    if(lst.find(u) != lst.end() || d == 13)
//        return;
//
//    lst.insert(u);
//    mx = max(mx, d);
//
//    for(ll i = u; i > 0 && !done; i = (i-1)&u) {
//        ll nxt = u+i, got;
//        if(nxt > v)
//            continue;
//        if(nxt == v) {
//            done = 1;
//            return;
//        }
//
//        for0(i, 31) {
//            if((nxt >> i) & 1) {
//                got = i;
//                break;
//            }
//        }
//
//        //cout << got << " " << f << EL;
//        if(got > f)
//            continue;
//
//        ll diff = v-nxt;
//        if(!(diff&nxt))
//            continue;
//
//        dfs(nxt,d+1);
//    }
//}

int main()
{
    ll q;
    cin >> q;

    while(q--) {
        ll u, v;
        sl(u), sl(v);

//        if(u == v) {
//            pf("YES\n");
//            continue;
//        }
        if(v < u) {
            pf("NO\n");
            continue;
        }

        ll cnt1 = 0, cnt2 = 0;
        ll f = -1, done = 1;

        for0(i, 31) {
            bool b1 = (u>>i) & 1, b2 = (v>>i)&1;

//            if(b1 && f == -1) f = i;
//
//            if(b2 && f == -1) {
//                done = 0;
//                break;
//            }

            if(b1) cnt1++;
            if(b2) cnt2++;

            if(cnt2 > cnt1) done = 0;
        }

        //if(cnt1 < cnt2) done = 0;

        if(done) pf("YES\n");
        else pf("NO\n");
    }

    return 0;
}
