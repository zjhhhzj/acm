/*
将若干元素划分到两个集合A,B中。对于元素被划分到A或B中分别能获得一个ai或bi的分值。
除此之外，还给出若干个组合，当组合中的元素被同时划分到一个集合可以获得额外的分值 
*/
int main()
{
    st=0,ed=n+1;//把st(A)作为源点，ed(B)作为汇点
    int sum = 0, cnt = ed;//sm为包括A,B贡献总和,cnt为总点数
    for (int i = 1; i <= n; i++)//与A连通的点代表放到A集合中
    {
        int x = read();
        add(st, i, x);
        add(i, st, 0);
        sum += x;
    }
    for (int i = 1; i <= n; i++)//与B连通的点代表放到B集合中
    {
        int x = read();
        add(i, ed, x);
        add(ed, 0, 0);
        sum += x;
    }
    m = read();
    for (int i = 0; i < m; ++i)//从A点伸出一条容量为w的边通向虚点 
 
    {
        int k = read(), wa = read(), wb = read();//wa为组合在a的贡献,wb为组合在b的贡献,k为组合点数数量
        add(st, ++cnt, wa);
        add(cnt, st, 0);
        add(++cnt, ed, wb);
        add(ed, cnt, 0);
        sum += wa;
        sum += wb;
        while (k--)//令X->中间的容量为INF
        {
            int c = read();
            add(cnt - 1, c, INF);
            add(c, cnt - 1, 0);
            add(c, cnt, INF);
            add(cnt, c, 0);
        }
    }
    cout << sum - dinic();//总贡献-最小割=最大贡献量(将总元素分成独立俩部分)
    return 0;
}
