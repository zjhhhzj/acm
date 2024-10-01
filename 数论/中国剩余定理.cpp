/*
本质上是解下面的同余方程组
{
ans≡b1(mod a1),
ans≡b2(mod a2),
ans≡b3(mod a3),,,
}
*/
inline ll inv(ll a, ll p)
{
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
inline ll CRT(ll a[], ll b[], ll n)  //求ans
{
    ll p = 1, ans = 0;
    for (int i = 0; i < n; ++i)
        p *= a[i];
    for (int i = 0; i < n; ++i)
    {
        ll r = p / a[i];
        ans += (b[i] * r * inv(r, a[i])) % p;
    }
    return ans % p;
}