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

// === DEBUG MACRO STARTS HERE === //
#ifndef ONLINE_JUDGE
#define DEBUG
#define SYS_COL system("COLOR")
#endif

int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; \
                cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":" \
                <<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value,
            Ostream&>::type operator<<(Ostream& os,  const Cont& v) {
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
#else
#define dbg(x)
#endif
// === DEBUG MACRO ENDS HERE === //

#define ff first
#define ss second

const ll sz = 1e5 + 10;
ll par[sz], lev[sz], tr[4*sz], val[sz];

struct info {
    int a, b, c, d;
} ara[sz];

vector <int> num;
vector <pll> lst[sz];

void upd(ll lo, ll hi, ll idx, ll v, ll node)
{
    if(lo > idx || hi < idx)
        return;
    if(lo == hi) {
        tr[node] = lo, val[lo] = v;
        return;
    }

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, idx, v, lft);
    upd(mid+1, hi, idx, v, rgt);

    tr[node] = (val[ tr[lft] ] < val[ tr[rgt] ])? tr[lft] : tr[rgt];
}

ll qry(ll lo, ll hi, ll l, ll r, ll node)
{
    if(lo > r || hi < l)
        return inf;
    if(lo >= l && hi <= r)
        return tr[node];

    ll mid = lo+hi>>1, lft=node<<1, rgt=lft|1, ret = inf;

    ll p1 = qry(lo, mid, l, r, lft);
    ll p2 = qry(mid+1, hi, l, r, rgt);

    if(p1 == inf) return p2;
    else if(p2 == inf) return p1;
    else return (val[p1]<val[p2])? p1 : p2;
}

int main()
{
    ll n;
    cin >> n;

    ara[0] = {0, 0, 0, 0};
    for1(i, n) {
        scanf("%d %d %d %d", &ara[i].a, &ara[i].b, &ara[i].c, &ara[i].d);
        num.pb(ara[i].a);
    }
    sort(all(num));
    num.erase(unique(all(num)), num.end());

    for1(i, n) {
        ll x = lower_bound(all(num), ara[i].a) - num.begin();
        lst[x].pb(mp(ara[i].b, i));
    }

    for0(i, num.size()) {
        lst[i].pb(mp(inf, inf));
        sort(all(lst[i]), greater<pll>());

        upd(0, num.size()-1, i, lst[i].back().ff, 1);
    }

    queue <ll> q;
    q.push(0);

    while(!q.empty()) {
        ll u = q.front();
        q.pop();

        ll px = ara[u].c, py = ara[u].d;
        ll pos = upper_bound(all(num), px) - num.begin() - 1;
        if(pos < 0) continue;

        while(1) {
            ll x = qry(0, num.size()-1, 0, pos, 1);
            if(lst[x].back().ff > py)
                break;

            pll v = lst[x].back();
            lst[x].pop_back();

            lev[v.ss] = lev[u] + 1;
            par[v.ss] = u;
            q.push(v.ss);

            upd(0, num.size()-1, x, lst[x].back().ff, 1);
        }
    }

    if(lev[n] == 0) {
        pf("-1\n");
        return 0;
    }

    vector <int> ans;
    ll cur = n;
    while(cur != 0) {
        ans.pb(cur);
        cur = par[cur];
    }
    reverse(all(ans));

    pf("%lld\n", lev[n]);
    for(int &x : ans) pf("%d ", x);
    pn;

    return 0;
}
