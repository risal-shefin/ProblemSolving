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
#define inf (1LL << 29)
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

const ll sz = 2e5 + 10;
int tr[4*sz], tr2[4*sz], ara[sz];

void build(int lo, int hi, int node)
{
    if(lo == hi) {
        tr[node] = tr2[node] = inf;
        return;
    }

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    build(lo, mid, lft);
    build(mid+1, hi, rgt);

    tr[node] = min(tr[lft], tr[rgt]);
    tr2[node] = min(tr2[lft], tr2[rgt]);
}

void upd(int lo, int hi, int l, int r, int v, int node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr[node] = v;
        return;
    }

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd(lo, mid, l, r, v, lft);
    upd(mid+1, hi, l, r, v, rgt);

    tr[node] = min(tr[lft], tr[rgt]);
}

int qry(int lo, int hi, int l, int r, int node)
{
    if(lo > r || hi < l || l > r)
        return inf;
    if(lo >= l && hi <= r)
        return tr[node];

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    return min(qry(lo, mid, l, r, lft),
               qry(mid+1, hi, l, r, rgt));
}

void upd2(int lo, int hi, int l, int r, int v, int node)
{
    if(lo > r || hi < l)
        return;
    if(lo >= l && hi <= r) {
        tr2[node] = v;
        return;
    }

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    upd2(lo, mid, l, r, v, lft);
    upd2(mid+1, hi, l, r, v, rgt);

    tr2[node] = min(tr2[lft], tr2[rgt]);
}

int qry2(int lo, int hi, int l, int r, int node)
{
    if(lo > r || hi < l || l > r)
        return inf;
    if(lo >= l && hi <= r)
        return tr2[node];

    int mid = lo+hi>>1, lft=node<<1, rgt=lft|1;

    return min(qry2(lo, mid, l, r, lft),
               qry2(mid+1, hi, l, r, rgt));
}

int main()
{
    int t; si(t);

    while(t--) {
        int n; si(n);

        vector <int> lst;
        for1(i, n) {
            si(ara[i]);
            lst.pb(ara[i]);
        }
        sort(all(lst));
        lst.erase(unique(all(lst)), lst.end());

        build(0, n, 1);
        ll rng = n, ans = 0;
        stack <int> st1, st2;

        rep1(i, n) {
            int num = upper_bound(all(lst), ara[i]) - lst.begin();
            ll nxt1 = qry(0, n, num, n, 1);
            ll nxt2 = qry2(0, n, 0, num, 1);

            ll lim = min({rng, nxt1-1, nxt2-1});
            ans += (lim-i+1);
            //dbg(mp(i, lim));

            while(!st1.empty() && ara[st1.top()] < ara[i]) st1.pop();
            ll bg = n+1;
            if(!st1.empty()) bg = st1.top();

            while(!st2.empty() && ara[st2.top()] > ara[i]) st2.pop();
            ll sm = n+1;
            if(!st2.empty()) sm = st2.top();

            upd(0, n, num, num, bg, 1);
            upd2(0, n, num, num, sm, 1);

            rng = lim;
            st1.push(i), st2.push(i);
        }

        pf("%lld\n", ans);
    }

    return 0;
}

