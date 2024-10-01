/*
用于求一个排列在所有1~n的全随机排列间的字典序排名。
下标i的贡献为Ai(n-i)!,Ai表示i后面比ai小的数的个数
*/
ll fact[MAXN] = {1}, P[MAXN], A[MAXN], tree[MAXN];
//fact为(n-i)!,需要外面初始化
for(int i=1;i,=n;i++)fact[i]=fact[i-1]*i;
ll lowbit(ll x) { return x & -x; }
ll query(ll x)
{
    ll ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        ans += tree[i];
    return ans;
}
void update(ll x, ll d)
{
    for (int i = x; i < MAXN; i += lowbit(i))
        tree[i] += d;
}
ll cantor(int P[], int n)
{
    ll ans = 1;
    for (int i = n; i >= 1; i--)
    {
        A[i] = query(P[i]);
        update(P[i], 1);
    }
    for (int i = 1; i < n; i++)
        ans = (ans + A[i] * fact[n - i]) % MOD;
    return ans;
}

//逆康托展开
void decanter(ll x, int n)             // x为排列的排名，n为排列的长度
{
    x--;
    vector<int> rest(n, 0);
    iota(rest.begin(), rest.end(), 1); // 将rest初始化为1,2,...,n
    for (int i = 1; i <= n; ++i)
    {
        A[i] = x / fact[n - i];
        x %= fact[n - i];
    }
    for (int i = 1; i <= n; ++i)
    {
        P[i] = rest[A[i]];
        rest.erase(lower_bound(rest.begin(), rest.end(), P[i]));
    }
}
//使用各种平衡树优化
ll fact[MAXN] = {1}, P[MAXN], A[MAXN]; // fact需要在外部初始化
void decanter(ll x, int n)             // x为排列的排名，n为排列的长度
{
    x--;
    for (int i = 1; i <= n; ++i)
        insert(i);
    for (int i = 1; i <= n; ++i)
    {
        A[i] = x / fact[n - i];
        x %= fact[n - i];
    }
    for (int i = 1; i <= n; ++i)
    {
        P[i] = kth(A[i] + 1);
        remove(P[i]);
    }
}
