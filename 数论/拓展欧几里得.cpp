ll gcd(ll x,ll y){
    while(x^=y^=x^=y%x);
    return y;
}
//ax+by=gcd(a,b)
int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x); //这里交换了x和y
    y -= (a / b) * x;
    return d;
}
