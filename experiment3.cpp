#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

// Edge Structure
struct Edge
{
    int w, u, v;
};

// Union Find (Disjoint Set)
class UnionFind
{
    vector<int> parent, Rank;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        Rank.assign(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    bool unite(int x, int y)
    {
        int rx = find(x);
        int ry = find(y);

        if (rx == ry)
            return false;

        if (Rank[rx] < Rank[ry])
            swap(rx, ry);

        parent[ry] = rx;

        if (Rank[rx] == Rank[ry])
            Rank[rx]++;

        return true;
    }
};

// Kruskal Algorithm
pair<vector<Edge>, int> kruskal(int n, vector<Edge> edges)
{
    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b)
         {
             return a.w < b.w;
         });

    UnionFind uf(n);

    vector<Edge> mst;
    int cost = 0;

    for (const auto &e : edges)
    {
        if (uf.unite(e.u, e.v))
        {
            mst.push_back(e);
            cost += e.w;

            if (mst.size() == n - 1)
                break;
        }
    }

    return {mst, cost};
}

// Prim Algorithm
pair<vector<Edge>, int> prim(int n, vector<vector<pair<int, int>>> &adj)
{
    vector<int> key(n, numeric_limits<int>::max());
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0});

    vector<Edge> mst;
    int cost = 0;

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        if (parent[u] != -1)
        {
            mst.push_back({weight, parent[u], u});
            cost += weight;
        }

        for (const auto &x : adj[u])
        {
            int v = x.first;
            int wt = x.second;

            if (!inMST[v] && wt < key[v])
            {
                key[v] = wt;
                parent[v] = u;
                pq.push({wt, v});
            }
        }
    }

    return {mst, cost};
}

int main()
{
    int n = 7;

    vector<Edge> edges = {
        {7, 0, 1},
        {5, 0, 3},
        {8, 1, 2},
        {9, 1, 3},
        {7, 1, 4},
        {5, 2, 4},
        {15, 3, 4},
        {6, 3, 5},
        {8, 4, 5},
        {9, 4, 6},
        {11, 5, 6}};

    vector<vector<pair<int, int>>> adj(n);

    for (const auto &e : edges)
    {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }

    auto kruskalResult = kruskal(n, edges);
    auto primResult = prim(n, adj);

    cout << "=== Kruskal's MST ===\n";

    for (const auto &e : kruskalResult.first)
    {
        cout << "Edge (" << e.u << " - " << e.v << ") Weight: " << e.w << endl;
    }

    cout << "Total MST Cost: " << kruskalResult.second << endl;

    cout << "\n=== Prim's MST ===\n";

    for (const auto &e : primResult.first)
    {
        cout << "Edge (" << e.u << " - " << e.v << ") Weight: " << e.w << endl;
    }

    cout << "Total MST Cost: " << primResult.second << endl;

    return 0;
}        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            cost += e.w;

            if (mst.size() == n - 1)
                break;
        }
    }

    return {mst, cost};
}

// ---------- Prim Algorithm ----------
pair<vector<Edge>, int> prim(int n, vector<vector<pair<int, int>>> &adj) {

    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    key[0] = 0;
    pq.push({0, 0});

    vector<Edge> mst;
    int cost = 0;

    while (!pq.empty()) {

        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        if (parent[u] != -1) {
            mst.push_back({weight, parent[u], u});
            cost += weight;
        }

        for (auto x : adj[u]) {

            int v = x.first;
            int wt = x.second;

            if (!inMST[v] && wt < key[v]) {

                key[v] = wt;
                parent[v] = u;
                pq.push({wt, v});
            }
        }
    }

    return {mst, cost};
}

// ---------- Main ----------
int main() {

    int n = 7;

    vector<Edge> edges = {
        {7, 0, 1},
        {5, 0, 3},
        {8, 1, 2},
        {9, 1, 3},
        {7, 1, 4},
        {5, 2, 4},
        {15, 3, 4},
        {6, 3, 5},
        {8, 4, 5},
        {9, 4, 6},
        {11, 5, 6}
    };

    // Adjacency List
    vector<vector<pair<int, int>>> adj(n);

    for (auto e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }

    auto kruskalResult = kruskal(n, edges);
    auto primResult = prim(n, adj);

    cout << "=== Kruskal's MST ===" << endl;

    for (auto e : kruskalResult.first) {
        cout << "Edge (" << e.u << " - " << e.v
             << ") Weight: " << e.w << endl;
    }

    cout << "Total MST Cost: "
         << kruskalResult.second << endl;

    cout << endl;

    cout << "=== Prim's MST ===" << endl;

    for (auto e : primResult.first) {
        cout << "Edge (" << e.u << " - " << e.v
             << ") Weight: " << e.w << endl;
    }

    cout << "Total MST Cost: "
         << primResult.second << endl;

    return 0;
}            mst.push_back(e);
            cost += e.w;

            if (mst.size() == n - 1)
                break;
        }
    }

    return {mst, cost};
}

// ---------- Prim Algorithm ----------
pair<vector<Edge>, int> prim(int n, vector<vector<pair<int, int>>> &adj) {

    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    key[0] = 0;
    pq.push({0, 0});

    vector<Edge> mst;
    int cost = 0;

    while (!pq.empty()) {

        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        if (parent[u] != -1) {
            mst.push_back({weight, parent[u], u});
            cost += weight;
        }

        for (auto x : adj[u]) {

            int v = x.first;
            int wt = x.second;

            if (!inMST[v] && wt < key[v]) {

                key[v] = wt;
                parent[v] = u;
                pq.push({wt, v});
            }
        }
    }

    return {mst, cost};
}

// ---------- Main ----------
int main() {

    int n = 7;

    vector<Edge> edges = {
        {7, 0, 1},
        {5, 0, 3},
        {8, 1, 2},
        {9, 1, 3},
        {7, 1, 4},
        {5, 2, 4},
        {15, 3, 4},
        {6, 3, 5},
        {8, 4, 5},
        {9, 4, 6},
        {11, 5, 6}
    };

    // Adjacency List
    vector<vector<pair<int, int>>> adj(n);

    for (auto e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }

    auto kruskalResult = kruskal(n, edges);
    auto primResult = prim(n, adj);

    cout << "=== Kruskal's MST ===" << endl;

    for (auto e : kruskalResult.first) {
        cout << "Edge (" << e.u << " - " << e.v
             << ") Weight: " << e.w << endl;
    }

    cout << "Total MST Cost: "
         << kruskalResult.second << endl;

    cout << endl;

    cout << "=== Prim's MST ===" << endl;

    for (auto e : primResult.first) {
        cout << "Edge (" << e.u << " - " << e.v
             << ") Weight: " << e.w << endl;
    }

    cout << "Total MST Cost: "
         << primResult.second << endl;

    return 0;
}
