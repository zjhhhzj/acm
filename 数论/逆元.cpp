//拓展欧几里得求逆元，p可不为质数
ll inv(ll a, ll p)
{
    ll x, y;
    if (exgcd(a, p, x, y) != 1) // 无解的情形
        return -1;
    return (x % p + p) % p;
}
//费马小定理求逆元,p必须为质数
ll ksm(ll x,ll y){
    ll ans=1;
    while(y){
        if(y&1ll)ans=(ans*x)%mod;
        y>>=1ll;x=(x*x)%mod;
    }
}
//线性求逆元
// 多次对不同的p使用需要清空Inv数组
ll Inv[MAXN] = {0, 1};
inline ll mod(ll a, ll p)
{
    return (a % p + p) % p;
}
ll inv(ll a, ll p)
{
    if (Inv[a])
        return Inv[a];
    Inv[a] = mod(-p / a * inv(p % a, p), p);
    return Inv[a];
}

