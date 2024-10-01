/*
定义为小于（或不大于，这里是一样的）x但与x互质的正整数的数量
1.若p为质数，f(p**n)=(p-1)(p**(n-1))
2.若a%x==0,则f(ax)=af(x)
3.若a,b互质,f(ab)=f(a)f(b)
*/
void init(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!isnp[i])
            primes.push_back(i), phi[i] = i - 1; // 性质一，指数为1的情形
        for (int p : primes)
        {
            if (p * i > n)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
            {
                phi[p * i] = phi[i] * p; // 性质二
                break;
            }
            else
                phi[p * i] = phi[p] * phi[i]; // 这时肯定互质，用性质三
        }
    }
}
