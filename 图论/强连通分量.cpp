//简单说就是缩点
stack<int> stk;
// instk：是否在栈中  scc：每个点所属的强连通分量编号
int dfsn[MAXN], low[MAXN], instk[MAXN], scc[MAXN], cnt, cscc;
void tarjan(int p)
{
    low[p] = dfsn[p] = ++cnt;
    instk[p] = 1;
    stk.push(p); // 进栈
    for (auto q : edges[p])
    {
        if (!dfsn[q]) // 未访问过
        {
            tarjan(q); // 递归地搜索
            low[p] = min(low[p], low[q]);
        }
        else if (instk[q]) // 访问过，且q可达p
            low[p] = min(low[p], dfsn[q]);
    }
    if (low[p] == dfsn[p]) // 发现强连通分量的根
    {
        int top;
        cscc++;
        do
        {
            top = stk.top();
            stk.pop();
            instk[top] = 0;
            scc[top] = cscc; // 记录所属的强连通分量
        } while (top != p); // 直到弹出p才停止
    }
}
for (int i = 1; i <= n; ++i)//原图并不一定是强连通图
    if (!dfsn[i])
        tarjan(i);
