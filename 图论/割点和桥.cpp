//割点
int dfsn[MAXN], low[MAXN], cnt;
vector<int> cut; // 存储所有割点
void tarjan(int p, bool root = true)
{
    int tot = 0;
    low[p] = dfsn[p] = ++cnt;
    for (auto q : edges[p])
    {
        if (!dfsn[q])
        {
            tarjan(q, false);
            low[p] = min(low[p], low[q]);
            tot += (low[q] >= dfsn[p]); // 统计满足low[q] >= dfsn[p]的子节点数目
        }
        else
            low[p] = min(low[p], dfsn[q]);
    }
    if (tot > root) // 如果是根，tot需要大于1；否则只需大于0
        cut.push_back(p);
}

//桥
/*
修改一下low的定义：我们限定经过的那条非树边不能是从子节点直接到父节点的反向边
*/
vector<pair<int, int>> bridges;
int dfsn[MAXN], low[MAXN], fa[MAXN], cnt;
void tarjan(int p)
{
    low[p] = dfsn[p] = ++cnt;
    for (auto to : edges[p])
    {
        if (!dfsn[to])
        {
            fa[to] = p; // 记录父节点
            tarjan(to);
            low[p] = min(low[p], low[to]);
            if (low[to] > dfsn[p])
                bridges.emplace_back(p, to);
        }
        else if (fa[p] != to) // 排除父节点
            low[p] = min(low[p], dfsn[to]);
    }
}
