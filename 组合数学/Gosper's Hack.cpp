/*
Gosper's Hack是一种生成n元集合所有k元子集的算法
如果调用GospersHack(3, 5)，会依次遍历到以下二进制数：
00111
01011
01101
01110
10011
10101
10110
11001
11010
11100
*/
void GospersHack(int k, int n)
{
    int cur = (1 << k) - 1;
    int limit = (1 << n);
    while (cur < limit)
    {
        // do something
        int lb = cur & -cur;
        int r = cur + lb;
        cur = ((r ^ cur) >> __builtin_ctz(lb) + 2) | r;
        // 或：cur = (((r ^ cur) >> 2) / lb) | r;
    }
}
