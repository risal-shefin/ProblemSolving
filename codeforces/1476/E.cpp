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

const ll sz = 1e5 + 10, tsz = 4*sz + 10;
int nxt[tsz][27], root, idt, cnt[sz], ok=1, got;
vector <int> lst[tsz], g[sz], ans;

string s;

void add(ll id)
{
    ll cur = root;
    for(ll i = 0; i < s.size(); i++) {
        ll now;
        if(s[i] == '_') now = 26;
        else now = s[i] - 'a';

        if(!nxt[cur][now])
            nxt[cur][now] = ++idt;

        cur = nxt[cur][now];
    }

    lst[cur].pb(id);
}

void srch(ll cur, ll i, ll id)
{
    if(i == s.length()) {

        for(int &ind : lst[cur]) {
            if(ind == id)
                got = 1;
            else {
                g[id].pb(ind);
                cnt[ind]++;
            }
        }

        return;
    }

    ll now = s[i] - 'a';

    if(nxt[cur][now])
        srch(nxt[cur][now], i+1, id);

    if(nxt[cur][26])
        srch(nxt[cur][26], i+1, id);
}

void topsort(ll n)
{
    queue <ll> q;
    for1(i, n) {
        if(cnt[i] == 0)
            q.push(i);
    }

    while(!q.empty()) {
        ll u = q.front();
        q.pop();
        ans.pb(u);

        for(int &v : g[u]) {
            cnt[v]--;
            if(cnt[v] == 0)
                q.push(v);
        }
    }
}

int main()
{
    fastio;
    ll n, m, k;
    cin >> n >> m >> k;

    for1(i, n) {
        cin >> s;
        add(i);
    }

    for1(i, m) {
        ll indx;
        cin >> s >> indx;

        got = 0;
        srch(0, 0, indx);
        if(!got) ok = 0;
    }
    if(!ok) {
        cout << "NO" << EL;
        return 0;
    }

    topsort(n);

    if(ans.size() < n) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for0(i, n) {
        cout << ans[i] << " ";
    }
    cout << EL;

    return 0;
}

