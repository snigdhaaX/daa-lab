#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

void dijkstra(const vector<vector<pair<int, int>>> &graph, int source,
              vector<int> &dist, vector<int> &prev)
{
    int n = graph.size();
    dist.assign(n, numeric_limits<int>::max());
    prev.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<bool> visited(n, false);

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

vector<int> reconstructPath(const vector<int> &prev, int source, int target)
{
    vector<int> path;

    for (int at = target; at != -1; at = prev[at])
        path.push_back(at);

    reverse(path.begin(), path.end());

    if (!path.empty() && path[0] == source)
        return path;

    return {};
}

int main()
{
    // Graph Definition (Adjacency List)
    vector<vector<pair<int, int>>> graph(6);

    graph[0] = {{1, 4}, {2, 1}};
    graph[1] = {{3, 1}};
    graph[2] = {{1, 2}, {3, 5}};
    graph[3] = {{4, 3}};
    graph[4] = {{5, 2}};
    graph[5] = {};

    int source = 0;

    vector<int> dist, prev;

    dijkstra(graph, source, dist, prev);

    cout << "Shortest paths from vertex " << source << ":" << endl;
    cout << left << setw(8) << "Vertex"
         << setw(10) << "Distance"
         << "Path" << endl;

    cout << "-------------------------------------------------------" << endl;

    for (int v = 0; v < graph.size(); v++)
    {
        vector<int> path = reconstructPath(prev, source, v);

        cout << left << setw(8) << v;

        if (dist[v] == numeric_limits<int>::max())
            cout << setw(10) << "INF";
        else
            cout << setw(10) << dist[v];

        if (path.empty())
        {
            cout << "No path";
        }
        else
        {
            for (int i = 0; i < path.size(); i++)
            {
                cout << path[i];
                if (i != path.size() - 1)
                    cout << " -> ";
            }
        }

        cout << endl;
    }

    return 0;
}