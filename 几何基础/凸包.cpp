/*
在一切包含所有点的凸多边形中，凸包的面积是最小的（显然），周长也是最小的

Graham扫描法
最左下角的一个点是必然在凸包上的。我们以这个点为极点进行极角排序。
维护一个栈，按照极角排序后的顺序遍历每个点。如果栈中点数小于3，就直接进栈；
否则，检查栈顶三个点组成的两个向量的旋转方向是否为逆时针
若是则进栈，若不是则弹出栈顶，直到栈中点数小于3或者满足逆时针条件为止。
*/
using Points = vector<Point>;
double theta(Point p) { return p == O ? -1 / 0. : atan2(p.y, p.x); } // 求极角
void psort(Points &ps, Point c = O)                                  // 极角排序
{
    sort(ps.begin(), ps.end(), [&](auto p1, auto p2) {
        return lt(theta(p1 - c), theta(p2 - c));
    });
}
bool check(Point p, Point q, Point r) // 检查三个点组成的两个向量的旋转方向是否为逆时针
{
    return lt(0, cross(q - p, r - q));
}
Points chull(Points &ps)
{
    psort(ps, *min_element(ps.begin(), ps.end())); // 以最左下角的点为极角排序
    Points H{ps[0]};
    for (int i = 1; i < ps.size(); i++)
    {
        while (H.size() > 1 && !check(H[H.size() - 2], H.back(), ps[i]))
            H.pop_back();
        H.push_back(ps[i]);
    }
    return H;
}

/*
Andrew算法(快一点)
直接以横坐标为第一关键词、纵坐标为第二关键词排序，这样将顶点依次相连,保证不交叉
按照这样的排序顺序，像刚刚那样调整，可以求得下凸包。
然后再倒过来走一遍（已经走过的点不走）,又可以得到上凸包，两者组合即得要求的凸包
*/
// DEPENDS eq, lt, cross, V-V, P<P
using Points = vector<Point>;
bool check(Point p, Point q, Point r) // 检查三个点组成的两个向量的旋转方向是否为逆时针
{
    return lt(0, cross(q - p, r - q));
}
Points chull(Points &ps)
{
    sort(ps.begin(), ps.end());
    vector<int> I{0}, used(ps.size());
    for (int i = 1; i < ps.size(); i++)
    {
        while (I.size() > 1 && !check(ps[I[I.size() - 2]], ps[I.back()], ps[i]))
            used[I.back()] = 0, I.pop_back();
        used[i] = 1, I.push_back(i);
    }
    for (int i = ps.size() - 2; i >= 0; i--)
    {
        if (used[i])
            continue;
        while (I.size() > 1 && !check(ps[I[I.size() - 2]], ps[I.back()], ps[i]))
            I.pop_back();
        I.push_back(i);
    }
    Points H;
    for (int i = 0; i < I.size() - 1; i++)
        H.push_back(ps[I[i]]);
    return H;
}

