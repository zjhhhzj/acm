/*
<cmath>中有一个atan2(y,x)函数，可以直接计算(x,y)的极角，值域是(-pi,pi],注意(0,0)
顺序为一，二，x负轴，x正轴，四，三。如果想减少常数，可以提前算出每个点的极角。
*/
using Points = vector<Point>;
double theta(auto p) { return atan2(p.y, p.x); } // 求极角
void psort(Points &ps, Point c = O)              // 极角排序
{
    sort(ps.begin(), ps.end(), [&](auto p1, auto p2) {
        return lt(theta(p1 - c), theta(p2 - c));
    });
}

/*
先比较象限再做叉乘
00:x正,y正,一   01:二,x负   10:三   11:四,y负   //从x正轴开始
*/
int qua(auto p) { return lt(p.y, 0) << 1 | lt(p.x, 0) ^ lt(p.y, 0); }    // 求象限
void psort(Points &ps, Point c = O)                               // 极角排序
{
    sort(ps.begin(), ps.end(), [&](auto v1, auto v2) {
        return qua(v1 - c) < qua(v2 - c) || qua(v1 - c) == qua(v2 - c) && lt(cross(v1 - c, v2 - c), 0);
    });
}

