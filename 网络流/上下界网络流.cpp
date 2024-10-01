/*
给定一个没有源点和汇点、每条边的流量有上下界的流量网络，问是否存在一种可行流使得流量平衡

无源汇有上下界可行流
拆成两个结构与原图相同的普通网络，一个每条边的容量为原网络对应边的流量下界，另一个为对应边的流量上界与下界之差
在差网络中新设一个源点,一个汇点
如果下界网络中某个点有x的净流入，在差网络中我们就从源点向它连一条容量为x的附加边
如果下界网络中某个点有x的净流出，在差网络中我们就从它向汇点连一条容量为x的附加边
在差网络上跑一遍最大流，把每条非附加边的流，加上下界网络的满流，就是一个可行流

有源汇有上下界可行流
从汇点到源点连一条下界为0，上界为inf的附加边，得到一张和原图等价的无源汇流量网络

有源汇有上下界最大流
在差网络中把所有附加边删除，然后以S与T为源点与汇点，再求残余网络的最大流(实际上S'与T'连接的附加边不需要删)
*/
int in[MAXN], out[MAXN];
int main()
{
    int s1, t1;
    cin >> n >> m >> s1 >> t1; // 先把s,t当作普通点，用s1,t1存储
    for (int i = 1; i <= m; ++i)
    {
        int from, to, lb, ub;
        cin >> from >> to >> lb >> ub;
        add(from, to, ub - lb);
        add(to, from, 0);
        in[to] += lb, out[from] += lb;
    }
    add(t1, s1, INF);
    add(s1, t1, 0);
    s = 300, t = 301;
    for (int i = 1; i <= n; ++i)
    {
        if (in[i] > out[i])
        {
            add(s, i, in[i] - out[i]);
            add(i, s, 0);
        }
        else if (in[i] < out[i])
        {
            add(i, t, out[i] - in[i]);
            add(t, i, 0);
        }
    }
    dinic();
    for (int e = head[s]; e; e = edges[e].next)
        if (edges[e].w != 0)return 0;
    s = s1, t = t1; // 切换源汇点
    int flow = 0;
    for (int e = head[t]; e; e = edges[e].next)
        if (edges[e].to == s)
        {
            flow = edges[e ^ 1].w;
            edges[e].w = edges[e ^ 1].w = 0; // 删除源汇点间的附加边
        }
    cout << dinic() + flow << endl;
    return 0;
}
/*
有源汇有上下界最小流
跟上面几乎完全相同，只需要在拆掉附加边后，从汇点到源点，而不是从源点到汇点跑一遍最大流。
可行流的流量，减去从汇点到源点的最大流即为答案

有上下界最小费用可行流
所有附加边的费用设为0。最后的费用是下界网络满流的费用(即所有边的容量与费用乘积的和)，加上在差网络上跑MCMF后得到的费用之和
*/