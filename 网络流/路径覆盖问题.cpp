/*
路径覆盖，是在DAG（有向无环图）上进行的
找出尽可能少的一系列路径，使这些路径经过DAG上的所有点恰好各一次。

原图上的每个点拆成两个点（对于点x，可以把从它拆出去的点记为x+n），其中一个点与源点相连，另一个与汇点相连。容量均为1。
跑一遍最大流，便能得到最大合并路径数，再用点数去减即得最小路径覆盖数（本质上就是二分图匹配）

//怎么输出方案？https://www.luogu.com.cn/problem/P2764
*/
int n,m,h[1000],cnt=1,s,t,dfn[1000],ans,f[1000],son[1000],nh[1000];
queue<int>q;
struct node
{
    int to,nt,w;
}e[100000];
void add(int u,int v,int w){
    e[++cnt]=z{v,h[u],w};
    h[u]=cnt;
}
bool bfs()
{
    memset(dfn,0,sizeof(dfn));
    dfn[s]=1;q.push(s);
    while (!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=h[u];i;i=e[i].nt){
            int v=e[i].to,w=e[i].w;
            if(w&&!dfn[v]){
                dfn[v]=dfn[u]+1;
                q.push(v);
            }
        }
    }
    return dfn[t];
}
int dfs(int u=s,int flow=mod)
{
    if(flow==0||u==t)return flow;
    int zs=0;
    for(int i=nh[u];i&&zs<flow;i=e[i].nt){
    	nh[u]=i;
        int v=e[i].to,w=e[i].w;
        if(w&&dfn[v]==dfn[u]+1){
            int ff=dfs(v,min(w,flow-zs));
            if(ff){
            	if(u!=0)son[u]=v-n;
            	f[v-n]=1;
                zs+=ff;
            	e[i].w-=ff;
            	e[i^1].w+=ff;
            }
        }
    }
    return zs;
}
int main()
{
    cin>>n>>m;
    t=2*n+1;
    for(int i=1;i<=n;i++){
        add(0,i,1);
        add(i,0,0);
        add(i+n,t,1);
        add(t,i+n,0);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v+n,1);
        add(v+n,u,0);
    }
    while (bfs())
    {
    	memcpy(nh,h,sizeof(h));
        ans+=dfs();
    }
    for(int i=1;i<=n;i++){
    	if(!f[i]){
    		int ii=i;
    		while(ii){
    			cout<<ii<<' ';
    			ii=son[ii];
			}
			cout<<'\n';
		}
	}
    cout<<n-ans;
}