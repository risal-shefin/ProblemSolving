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
#define inf (1LL << 30)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; i++)
#define for0(i, stop) for(ll i = 0; i < stop; i++)
#define rep1(i, start) for(ll i = start; i >= 1; i--)
#define rep0(i, start) for(ll i = (start-1); i >= 0; i--)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

const ll sz = 1e4 + 10;
ll vis[sz][1009];

int land[sz];

struct node {
    int pos, tim;
    ll tot;
};
const bool operator <(const node &a, const node &b) {
    return a.tot > b.tot;
}

int main()
{
    ll n, m;
    cin >> n >> m;

    for1(i, m) si(land[i]);
    sort(land + 1, land + m+1);

    ll g, r;
    cin >> g >> r;

    ll f = land[1];
    if(f > g) {
        //cout << g << " " << f << endl;
        cout << -1 << endl;
        return 0;
    }

    for0(i, sz) {
        for(ll j = 0; j <= 1000; j++)
            vis[i][j] = inf;
    }

    priority_queue <node> pq;
    pq.push({1, f, f});
    vis[1][f] = f;

    ll ans = inf, tot;
    int baki, lagbe, lft, rgt, rest, need, now;
    node u;
    while(!pq.empty()) {
        u = pq.top();
        pq.pop();

        //cout << u.pos << " || " << u.tot << endl;
        if(land[u.pos] == n) {
            ans = min(ans, u.tot);
            continue;
        }

        baki = g - u.tim;
        if(baki == 0) {
            u.tot += r, u.tim = 0;
            if(vis[u.pos][u.tim] <= u.tot)
                continue;

            vis[u.pos][u.tim] = u.tot;
            pq.push({u.pos, u.tim, u.tot});
            continue;
        }
        lagbe = n - land[u.pos];
        if(lagbe <= baki) {
            ans = min(ans, u.tot + lagbe);
        }

        if(vis[u.pos][u.tim] < u.tot)
            continue;

        lft = u.pos - 1, rgt = u.pos + 1;

        if(lft >= 1) {
            rest = g - u.tim;
            need = abs(land[u.pos] - land[lft]);
            if(need <= rest) {
                now = u.tim + need;
                tot = u.tot + need;

                if(vis[lft][now] > tot) {
                    vis[lft][now] = tot;
                    pq.push({lft, now, tot});
                }
            }
        }
        if(rgt <= n) {

            rest = g - u.tim;
            need = abs(land[u.pos] - land[rgt]);
            if(need <= rest) {
                now = u.tim + need;
                tot = u.tot + need;

                //cout << tot <<"   " << vis[rgt][now] << endl;
                if(vis[rgt][now] > tot) {
                    vis[rgt][now] = tot;
                    //cout << tot << endl;
                    pq.push({rgt, now, tot});
                }
            }
        }
    }

    if(ans == inf)
        cout << -1 << endl;
    else
        cout << ans << endl;

    return 0;
}