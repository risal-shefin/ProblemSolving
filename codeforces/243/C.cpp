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
#ifdef LOCALXOX
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

const ll sz = 3e3+10, lim = 1e10+1;
ll vis[sz][sz];

const ll dr[] = {1, -1, 0, 0};
const ll dc[] = {0, 0, 1, -1};

vector <ll> R, C;
vector <pll> lst;

void dfs(ll r, ll c)
{
    if(r < 0 || r >= R.size() || c < 0 || c >= C.size() || vis[r][c])
        return;

    vis[r][c] = 2;

    dfs(r-1, c), dfs(r+1, c);
    dfs(r, c-1), dfs(r, c+1);
}

int main()
{
    ll n; sl(n);
    R.pb(1), R.pb(lim), C.pb(1), C.pb(lim);

    ll pr = lim/2 + 1, pc = pr;

    R.pb(pr-1), R.pb(pr);
    C.pb(pr-1), C.pb(pc);

    lst.pb({pr, pc});

    for1(i, n) {
        char ch; ll d;
        scanf(" %c %lld", &ch, &d);

        ll nr = pr, nc = pc;

        if(ch == 'U') nr -= d;
        else if(ch == 'D') nr += d;
        else if(ch == 'L') nc -= d;
        else nc += d;

        if(nr-1 > 0) R.pb(nr-1);
        R.pb(nr);

        if(nc-1 > 0) C.pb(nc-1);
        C.pb(nc);

        pr = nr, pc = nc;
        lst.pb({pr, pc});
    }
    sort(all(R)), sort(all(C));
    R.erase(unique(all(R)), R.end());
    C.erase(unique(all(C)), C.end());

    for(ll i = 0; i < lst.size(); i++) {
        pll &p = lst[i];
        p.ff = lower_bound(all(R), p.ff) - R.begin();
        p.ss = lower_bound(all(C), p.ss) - C.begin();

        vis[p.ff][p.ss] = 1;

        if(i > 0) {
            ll p1 = lst[i-1].ff, p2 = p.ff;
            if(p1 > p2) swap(p1, p2);
            while(p1 <= p2) vis[p1][p.ss] = 1, p1++;

            p1 = lst[i-1].ss, p2 = p.ss;
            if(p1 > p2) swap(p1, p2);
            while(p1 <= p2) vis[p.ff][p1] = 1, p1++;
        }
    }

    dfs(0, 0);

    ll ans = 0;

    for(ll i = 0; i < R.size(); i++) {
        for(ll j = 0; j < C.size(); j++) {
            if(vis[i][j] == 2)
                continue;

            ll prvr = 0, prvc = 0;
            if(i != 0) prvr = R[i-1];
            if(j != 0) prvc = C[j-1];

            ans += (R[i]-prvr) * (C[j]-prvc);
            //dbg(mp(C[j], prvc));
        }
    }

    cout << ans << EL;

    return 0;
}
