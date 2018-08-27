#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll dist[100009], train[100009], city[100009], route[100009];

struct node {
    ll v, c;
    node(ll _v, ll _c) {
        v = _v;
        c = _c;
    }
};

bool operator <(node a, node b)

{
    return a.c > b.c;
}

vector <node> graph[100009];

int main()

{
    ll n, m, k;
    cin >> n >> m >> k;
    for(ll i = 1; i <= m; i++) {
        ll u, v, c;
        scanf("%lld %lld %lld", &u, &v, &c);
        graph[u].push_back( node(v, c) );
        graph[v].push_back( node(u, c) );
    }

    ll cnt = 0;
    for(ll i = 1; i <= k; i++) {
        ll u, c;
        scanf("%lld %lld", &u, &c);
        train[i] = c;
        city[i] = u;

        graph[u].push_back( node(1, c));
        graph[1].push_back( node(u, c));
    }

    for(ll i = 1; i <= n; i++)
        dist[i] = 1e18;

    dist[1] = 0;
    priority_queue <node> q;
    q.push( node(1, 0) );

    while(!q.empty()) {
        node u = q.top();
        q.pop();

        if(u.c != dist[u.v])
            continue;

        for(ll i = 0; i < graph[u.v].size(); i++) {
            node v = graph[u.v][i];

            if(u.c + v.c < dist[v.v]) {
                dist[v.v] = u.c + v.c;
                q.push( node(v.v, dist[v.v]) );
                route[v.v] = 1;
            }
            else if(u.c + v.c == dist[v.v])
                route[v.v]++;
        }

    }


    for(ll i = 1; i <= k; i++) {
        if(train[i] != dist[ city[i] ])
            cnt++;
        else if(train[i] == dist[ city[i] ] && route[ city[i] ] > 1) {
            route[ city[i] ]--;
            cnt++;
        }
    }

    cout << cnt << endl;

    return 0;
}
