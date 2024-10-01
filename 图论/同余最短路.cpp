/*
常常用于解决:
给出n个整数，每个整数可以取任意多次，询问关于它们能拼凑出的数的一些信息
例如，可能询问这些整数可以拼凑出多少[L,R]范围之内的数。
从同余的角度考虑问题。我们考虑模a1的每个同余类[x1],一旦我们能用[a2,,,an]凑出[x1]中的某个数 
那么[x1]中的每个大于等于这个数的数都可以凑出，只要我们知道每个同余类中能被凑出的最小数，就可以解决问题。
*/
sort(A+1,A+1+n);
for (int i = 0; i < A[1]; ++i)
    for (int j = 2; j <= n; ++j)
        G[i].emplace_back((i + A[j]) % A[1], A[j]);//F为v,S为w
// 跑单源最短路
ll R = 0, L = 0;
for (int i = 0; i < A[1]; ++i) {
    if (dis[i] != INF && dis[i] <= r) R += (r - dis[i]) / A[1] + 1;
    if (dis[i] != INF && dis[i] <= l - 1) L += (l - 1 - dis[i]) / A[1] + 1;
}
cout << R - L << endl;

//给定一个整数 K ，求一个 K 的整数倍 SUM ,使得 SUM 的数位累加和最小。
//==给出1个整数，整数可以取任意多次
int n,tot=0,first[N];
struct Edge{ int nxt,to,w; }e[N*10];
void add(int x,int y,int z){
	e[++tot]=(Edge){first[x],y,z};
	first[x]=tot;
}
priority_queue<PII> q;
int dis[N],inq[N];
void DIJ(){
	for(int i=0;i<n;i++) dis[i]=1e9,inq[i]=0;
	q.push((PII){1,0});dis[1]=0;
	while(!q.empty()){
		int u=q.top().id;q.pop();
		if(inq[u]) continue ;inq[u]=1;
		for(int i=first[u];i;i=e[i].nxt){
			int v=e[i].to,w=e[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!inq[v]) q.push((PII){v,dis[v]});
			}
		}
	}
}
void solve(){
	n=read();
	for(int i=1;i<n;i++) 
        for(int j=0;j<9;j++) 
            add(i,(i*10+j)%n,j);
	DIJ();
	printf("%d\n",dis[0]+1);
}
