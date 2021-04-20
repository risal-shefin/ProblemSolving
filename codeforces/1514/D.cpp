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

// === Debug macro starts here ===
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
// === Debug macro ends here ===

#define ff first
#define ss second

#define block 707
const ll sz = 3e5 + 10, offset = 3e5+1;

ll ara[sz], ans[sz], mx, cnt[sz], occ[2*sz];

struct query {
    ll l, r, i;
} qry[sz];

const bool compare(const query &a, const query &b)
{
    ll tmp = a.l / block;
    if(tmp != b.l / block) {
        return a.l < b.l;
    }

    if( tmp & 1)
        return a.r < b.r;

    return a.r > b.r;
}

inline void del(ll indx)
{
    ll x = ara[indx];

    occ[offset+cnt[x]]--;
    cnt[x]--;
    occ[offset+cnt[x]]++;

    if(occ[offset+mx] <= 0) mx--;
}

inline void add(ll indx)
{
    ll x = ara[indx];

    occ[offset+cnt[x]]--;
    cnt[x]++;
    occ[offset+cnt[x]]++;

    if(cnt[x] > mx)
        mx = cnt[x];
}

int main()
{
    ll n, q;
    scanf("%d %d", &n, &q);

    for(ll i = 0; i < n; i++)
        scanf("%d", &ara[i]);

    for(ll i = 0; i < q; i++) {
        scanf("%d %d", &qry[i].l, &qry[i].r);
        qry[i].l--; qry[i].r--; qry[i].i = i;
     }
    sort(qry, qry + q, compare);

    ll curl = 0, curr = 0;
    for(ll i = 0; i < q; i++) {

        while(curl < qry[i].l) {
            del(curl);
            curl++;
        }

        while(curl > qry[i].l) {
            add(curl - 1);
            curl--;
        }

        while(curr <= qry[i].r) {
            add(curr);
            curr++;
        }

        while(curr > qry[i].r + 1) {
            del(curr - 1);
            curr--;
        }

        ll len = (qry[i].r - qry[i].l+1);
        ll baki = len-mx;

        if(mx <= baki+1) ans[qry[i].i] = 1;
        else {
            ll ext = mx-(baki+1);
            ans[qry[i].i] = ext+1;
        }
    }

    for(ll i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    return 0;
}
