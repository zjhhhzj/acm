/*
用于求多元一次不等式组的一组解，例如：
v1-u1<=w1,
v2-u2<=w2,
v3-u3<=w3,,,
人为地增加一个超级源点,向所有顶点连一条边权为w的边,满足u1,u2,u3<=w的最大解
求最小解==求最长路，满足三角形不等式dis[u]>=dis[v]+w,需要把小于等于符号换成大于等于符号
*/
int cnt_edge, head[MAXN];
struct
{
    int to, next, w;
} edges[MAXM];
void add_edge(int from, int to, int w)
{
    edges[++cnt_edge].next = head[from];
    edges[cnt_edge].to = to;
    edges[cnt_edge].w = w;
    head[from] = cnt_edge;
}
bool inq[MAXN];
int cnt[MAXN], dis[MAXN];
queue<int> Q;
bool SPFA(int s, int n)
{
    memset(dis, 127, sizeof(dis));
//  memset(dis, -127, sizeof(dis));
    dis[s] = 0;
    Q.push(s);
    while (!Q.empty())
    {
        int p = Q.front();
        if (cnt[p] > n)
            return false;
        Q.pop();
        inq[p] = false;
        for (int eg = head[p]; eg != 0; eg = edges[eg].next)
        {
            int to = edges[eg].to;
            if (edges[eg].w + dis[p] < dis[to])
//          if (edges[eg].w + dis[p] > dis[to])
            {
                dis[to] = edges[eg].w + dis[p];
                if (!inq[to])
                {
                    Q.push(to);
                    inq[to] = true;
                    cnt[to]++;
                }
            }
        }
    }
    return true;
}
int main()
{
    int n = read(), m = read();
    for (int i = 0; i < m; ++i)
    {
        int x = read(), y = read(), w = read();
        add_edge(y, x, w);
//      add_edge(x, y, -w);
    }
    for (int i = 1; i <= n; ++i)add_edge(0, i, 0);
    if (SPFA(0, n))
    {
        for (int i = 1; i <= n; ++i)
            printf("%d ", dis[i]);
    }
    else
        puts("NO");
    return 0;
}
