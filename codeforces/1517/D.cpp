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

const ll sz = 505;
ll cst[sz][sz][4], n, m, k, h;
ll dist[sz][sz][22];

const ll dr[] = {0, -1, 0, 1};
const ll dc[] = {-1, 0, 1, 0};

struct info {
    int r, c, lv, w;
};
const bool operator <(const info &a, const info &b) {
    return a.w > b.w;
}

void dijkstra()
{
    for1(i, n)
        for1(j, m)
            for(ll k = 0; k <= h; k++)
                dist[i][j][k] = inf;

    priority_queue <info> pq;
    for1(i, n) {
        for1(j, m) {
            dist[i][j][0] = 0;
            pq.push({i, j, 0, 0});
        }
    }

    while(!pq.empty()) {
        info u = pq.top();
        pq.pop();

        if(dist[u.r][u.c][u.lv] != u.w)
            continue;

        for0(i, 4) {
            ll nr = u.r+dr[i], nc = u.c+dc[i];
            if(nr < 1 || nc < 1 || nr > n || nc > m)
                continue;

            if(dist[nr][nc][u.lv+1] > u.w + cst[u.r][u.c][i]) {

                dist[nr][nc][u.lv+1] = u.w + cst[u.r][u.c][i];

                if(u.lv+1 < h)
                    pq.push({nr, nc, u.lv+1, dist[nr][nc][u.lv+1]});
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;

    for1(i, n) {
        for1(j, m-1) {
            ll c; sl(c);

            cst[i][j][2] = cst[i][j+1][0] = c;
        }
    }

    for1(i, n-1) {
        for1(j, m) {
            ll c; sl(c);

            cst[i][j][3] = cst[i+1][j][1] = c;
        }
    }

    if(k & 1) {
        for1(i, n) {
            for1(j, m) {
                pf("-1 ");
            }
            pn;
        }

        return 0;
    }

    h = k/2;
    dijkstra();

    for1(i, n) {
        for1(j, m) {
            ll c = inf;

            for1(x, h) {
                ll rest = k-2*x;
                if(rest < 0) break;

                if(rest&1)
                    continue;

                c = min(c, 2*dist[i][j][x] + 2*dist[i][j][rest/2]);
            }

            pf("%lld ", c);
        }
        pn;
    }

    return 0;
}
