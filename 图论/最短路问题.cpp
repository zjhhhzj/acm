//Floyd算法,解决多源最短路问题
int dist[400][400];
void Floyd(int n)
{
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

//SPFA算法,O(nm),
//可以判负权环,当一个顶点进队超过n次时，就说明存在负权环
void SPFA(int s)
{
    queue<int> Q;
    Q.push(s);
    while (!Q.empty())
    {
        int p = Q.front();
        Q.pop();
        inqueue[p] = 0;
        for (int e = head[p]; e != 0; e = edges[e].next)
        {
            int to = edges[e].to;
            if (dist[to] > dist[p] + edges[e].w)
            {
                dist[to] = dist[p] + edges[e].w;
                if (!inqueue[to])
                {
                    inqueue[to] = 1;
                    Q.push(to);
                }
            }
        }
    }
}

//Dijkstra算法,O(n^2)
void Dij(int s)
{
    dist[s] = 0;
    Q.push(make_pair(0, s));
    while (!Q.empty())
    {
        int p = Q.top().second;
        Q.pop();
        if (vis[p])continue;
        vis[p] = 1;
        for (int e = head[p]; e != 0; e = edges[e].next)
        {
            int to = edges[e].to;
            dist[to] = min(dist[to], dist[p] + edges[e].w);
            //if (edges[e].w + dist[p] < dist[to])pre[to] = p;  打印路径
            if (!vis[to])
                Q.push(make_pair(dist[to], to));
        }
    }
}
