/*
网络上的每条边，除了容量外，还有一个属性：单位费用。一条边上的费用等于流量×单位费用
要求在保持流最大的同时，找到总费用最少的一种
只要建了反向边，无论增广的顺序是怎样，都能求出最大流
只需要每次都增广费用最少的一条路径即可。具体地，把EK算法里的BFS换成SPFA
*/
/*
注意建边,反向边的费用是正向边的相反数
add(x, y, v, c);
add(y, x, 0, -c);
*/
int head[MAXN], cnt = 1;  // 这里特意把存图也贴出来，记住额外存一个参数c（费用）
struct Edge
{
    int v, w, c, next;//v：到达点，w：最大流，c：费用，next：上(下)一条边
} edges[MAXM * 2];
void add(int u, int v, int w, int c)
{
    edges[++cnt] = {v, w, c, head[u]};
    head[u] = cnt;
}
int n, m, s, t, last[MAXN], flow[MAXN], inq[MAXN], dis[MAXN];
queue<int> Q;
bool SPFA()
{
    while (!Q.empty())Q.pop();
    memset(last, -1, sizeof(last));
    memset(inq, 0, sizeof(inq));
    memset(dis, 127, sizeof(dis));
    flow[s] = INF;
    dis[s] = 0;
    Q.push(s);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = 0;
        for (int eg = head[u]; eg != 0; eg = edges[eg].next)
        {
            int v = edges[eg].v, w = edges[eg].w;
            if (w > 0 && dis[v] > dis[u] + edges[eg].c) // 容量大于0才增广
            {
                last[v] = eg; // 记录上一条边
                flow[v] = min(flow[u], w); // 更新下一个点的流量
                dis[v] = dis[u] + edges[eg].c; // 注意这里是c不是w
                if (!inq[v])
                {
                    Q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return last[t] != -1;
}
int maxflow, mincost;
void MCMF() 
{
    while (SPFA())
    {
        maxflow += flow[t];//最大流
        mincost += dis[t] * flow[t];//最小费用
        for (int i = t; i != s; i = edges[last[i] ^ 1].v)
        {
            edges[last[i]].w -= flow[t];
            edges[last[i] ^ 1].w += flow[t];
        }
    }
}


//可以把EK用dinic取代
const int INF = 0x7fffffff;
int head[MAXN], cnt = 1;
struct Edge
{
    int to, w, c, next;
} edges[MAXM * 2];
void add(int from, int to, int w, int c)
{
    edges[++cnt] = {to, w, c, head[from]};
    head[from] = cnt;
}
void addEdge(int from, int to, int w, int c)
{
    add(from, to, w, c);
    add(to, from, 0, -c);
}
int s, t, dis[MAXN], cur[MAXN];
bool inq[MAXN], vis[MAXN];
queue<int> Q;
bool SPFA()
{
    while (!Q.empty())
        Q.pop();
    copy(head, head + MAXN, cur);
    fill(dis, dis + MAXN, INF);
    dis[s] = 0;
    Q.push(s);
    while (!Q.empty())
    {
        int p = Q.front();
        Q.pop();
        inq[p] = 0;
        for (int e = head[p]; e != 0; e = edges[e].next)
        {
            int to = edges[e].to, vol = edges[e].w;
            if (vol > 0 && dis[to] > dis[p] + edges[e].c)
            {
                dis[to] = dis[p] + edges[e].c;
                if (!inq[to])
                {
                    Q.push(to);
                    inq[to] = 1;
                }
            }
        }
    }
    return dis[t] != INF;
}
int dfs(int p = s, int flow = INF)
{
    if (p == t)
        return flow;
    vis[p] = 1;
    int rmn = flow;
    for (int eg = cur[p]; eg && rmn; eg = edges[eg].next)
    {
        cur[p] = eg;
        int to = edges[eg].to, vol = edges[eg].w;
        if (vol > 0 && !vis[to] && dis[to] == dis[p] + edges[eg].c)
        {
            int c = dfs(to, min(vol, rmn));
            rmn -= c;
            edges[eg].w -= c;
            edges[eg ^ 1].w += c;
        }
    }
    vis[p] = 0;
    return flow - rmn;
}
int maxflow, mincost;
void run(int s, int t)
{
    MCMF::s = s, MCMF::t = t;
    while (SPFA())
    {
        int flow = dfs();
        maxflow += flow;
        mincost += dis[t] * flow;
    }
}

//使用dijkstra算法
#define out(i,a,now) for(int i=a.be[now],to=a.v[i];~i;i=a.ne[i],to=a.v[i])
#define fo(i,a,b) for(i=a;i<=b;i++)
struct adj_list
{
	LL be[maxn],ne[maxm<<4],v[maxm<<4],w[maxm<<4],c[maxm<<4],cnt;
	void init()
	{
		memset(be,-1,sizeof(be));
		cnt=0;
	}
	void add(LL pre,LL nxt,LL wei,LL cost)
	{
		v[cnt]=nxt;
		ne[cnt]=be[pre];
		be[pre]=cnt;
		w[cnt]=wei;
		c[cnt]=cost;
		++cnt;
	}
};
struct NetWork
{
	adj_list v;
	LL dis[maxn],h[maxn],pre_node[maxn],pre_edge[maxn],inque[maxn];
	void SPFA(LL be,LL en)
	{
		queue<LL> q;
		qk(inque);
		LL i;
		fo(i,1,n) h[i]=LLONG_MAX>>1;
		h[be]=0; inque[be]=1;
		q.push(be);
		while (!q.empty())
		{
			LL now=q.front();
			q.pop();
			out(i,v,now)
			if (h[now]+v.c[i]<h[to] && v.w[i])
			{
				h[to]=h[now]+v.c[i];
				if (!inque[to])
				{
					q.push(to);
					inque[to]=1;
				}
			}
			inque[now]=0;
		}
	}
	void MCMF(LL s,LL t,LL &flow,LL &cost)
	{
		flow=cost=0;
		SPFA(s,t);//用一次SPFA更新h数组
		while (1)
		{
			pre_node[s]=pre_edge[s]=-1;//开始堆优化dijkstra算法
			LL i;
			fo(i,1,n) dis[i]=LLONG_MAX>>1;
			dis[s]=0;
			priority_queue<Pair,vector<Pair>,greater<Pair> > pq;
			pq.push(mp(0,s));
			while(!pq.empty())
			{
				Pair now=pq.top();
				pq.pop();
				if (now.first!=dis[now.second]) continue;
				if (now.second==t) break;
				out(i,v,now.second)
				{
					LL len=v.c[i]+h[now.second]-h[to];
					if (v.w[i] && dis[now.second]+len<dis[to])
					{
						dis[to]=dis[now.second]+len;
						pq.push(mp(dis[to],to));
						pre_node[to]=now.second;//记录从哪个点来
						pre_edge[to]=i;//记录从哪条边来
					}
				}
			}
			if (dis[t]>=(LLONG_MAX>>1)) break;
			LL miflow=LLONG_MAX>>1;
			for(i=t;i!=s;i=pre_node[i])
				cmin(miflow,v.w[pre_edge[i]]);//找到路径上流量最小值
			for(i=t;~i;i=pre_node[i])
			{
				v.w[pre_edge[i]]-=miflow;
				v.w[pre_edge[i]^1]+=miflow;//更新反向边
			}
			flow+=miflow;
			cost+=miflow*(h[t]+dis[t]);
			fo(i,1,n) h[i]=min(h[i]+dis[i],LLONG_MAX>>1);//更新h数组
		}
	}
	void sol()
	{
		v.init();
		LL i,x,y,z,w;
		scanf("%lld%lld%lld%lld",&n,&m,&s,&t);
		fo(i,1,m)
		{
			scanf("%lld%lld%lld%lld",&x,&y,&z,&w);
			v.add(x,y,z,w);
			v.add(y,x,0,-w);
		}
		LL flow,cost;
		MCMF(s,t,flow,cost);
		printf("%lld %lld",flow,cost);
	}
}