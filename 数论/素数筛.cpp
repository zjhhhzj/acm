bool isnp[MAXN];
vector<int> primes; // 质数表
void init(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!isnp[i])primes.push_back(i);
        for (int p : primes)
        {
            if (p * i > n)break;
            isnp[p * i] = 1;
            if (i % p == 0)break;
        }
    }
}
