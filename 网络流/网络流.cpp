/*
n个点m条边
先用BFS分层，再用DFS寻找,时间复杂度上界是 O(mn**2)
多路增广:在某点DFS找到一条增广路后，如果还剩下多余的流量未用，继续在该点DFS尝试找到更多增广路
弧优化:一条边增广一次后就不会再次增广了，所以下次增广时不需要再考虑这条边。我们把head数组复制一份，但不断更新增广的起点。

最大流最小割定理。割就是从网络中选择一些边，使得去掉这些边后，剩下两个不连通的分别包含源点和汇点的点集。割的大小是这些边的容量之和。最大流等于最小割。
*/
int n, m, s, t, dfn[N], cur[N]; // lv是每个点的层数，cur用于当前弧优化标记增广起点
int head[N];
struct node
{
    int to,next,w;
}edges[10005];
void add(int u,int v,int w)
{
    e[++cnt]=z{v,h[u],w};
    h[u]=cnt;
}
inline bool bfs() // BFS分层
{
    memset(lv, -1, sizeof(lv));
    dfn[s] = 0;
    memcpy(cur, head, sizeof(head)); // 当前弧优化初始化
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int p = q.front();
        q.pop();
        for (int eg = head[p]; eg; eg = edges[eg].next)
        {
            int to = edges[eg].to, vol = edges[eg].w;
            if (vol > 0 && dfn[to] == -1)
                dfn[to] = dfn[p] + 1, q.push(to);
        }
    }
    return dfn[t] != -1; // 如果汇点未访问过说明已经无法达到汇点，此时返回false
}
int dfs(int p = s, int flow = INF)
{
    if (p == t)
        return flow;
    int rmn = flow; // 剩余的流量
    for (int eg = cur[p]; eg && rmn; eg = edges[eg].next) // 如果已经没有剩余流量则退出
    {
        cur[p] = eg; // 当前弧优化，更新当前弧
        int to = edges[eg].to, vol = edges[eg].w;
        if (vol > 0 && dfn[to] == dfn[p] + 1) // 往层数高的方向增广
        {
            int c = dfs(to, min(vol, rmn)); // 尽可能多地传递流量
            rmn -= c; // 剩余流量减少
            edges[eg].w -= c; // 更新残余容量
            edges[eg ^ 1].w += c; // 再次提醒，链式前向星的cnt需要初始化为1（或-1）才能这样求反向边
        }
    }
    return flow - rmn; // 返回传递出去的流量的大小
}
inline int dinic()
{
    int ans = 0;
    while (bfs())
        ans += dfs();
    return ans;
}
