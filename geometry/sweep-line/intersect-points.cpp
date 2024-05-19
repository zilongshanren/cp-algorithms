// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/6/CGL_6_A

#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

#define MAXN 100005
#define BOTTOM 0
#define LEFT 1
#define RIGHT 2
#define TOP 3


class Point
{
public:
    double x, y;
    Point()
    {
    }
    Point(double x, double y)
    {
        (*this).x = x;
        (*this).y = y;
    }

    double operator^(const Point &p) const //叉乘
    {
        return x * p.y - y * p.x;
    }

    double operator*(const Point &p) const //点乘
    {
        return x * p.x + y * p.y;
    }

    Point operator*(const double &d) const
    {
        return Point(x * d, y * d);
    }

    Point operator/(const double &d) const
    {
        return Point(x / d, y / d);
    }

    Point operator-(const Point &p) const
    {
        return Point(x - p.x, y - p.y);
    }

    Point operator+(const Point &p) const
    {
        return Point(x + p.x, y + p.y);
    }

    double sqr()
    {
        return x * x + y * y;
    }
    double abs()
    {
        return sqrt(sqr());
    }

    double distance(const Point &p)
    {
        return fabs((*this - p).abs());
    }

    void read()
    {
        cin >> x >> y;
    }

    void print()
    {

        printf("%.10lf %.10lf\n", x, y);
    }
};

class Line
{
public:
    Point p1, p2;
    Line(){};
    Line(Point p1, Point p2)
    {
        (*this).p1 = p1;
        (*this).p2 = p2;
    }
};

class EndPoint
{
public:
    Point p;
    int seg, st; //线段的id、端点种类
    EndPoint(){};
    EndPoint(Point p, int seg, int st)
        : p(p), seg(seg), st(st){};

    bool operator<(const EndPoint &ep) const
    {
        //按y坐标升序排序
        if (p.y == ep.p.y)
            return st < ep.st; //y相同，按照下端点、左端点、右端点、上端点的顺序排列
        else
            return p.y < ep.p.y;
    }
};

EndPoint EP[2 * MAXN]; //端点列表

//线段相交问题：曼哈顿几何
int manhattan(vector<Line> S)
{
    int n = S.size();

    for (int i = 0, k = 0; i < n; ++i)
    {
        //调整p1、p2，保证左小右大
        if (S[i].p1.y == S[i].p2.y)
        {

            if (S[i].p1.x > S[i].p2.x)
                swap(S[i].p1, S[i].p2);
        }
        else if (S[i].p1.y > S[i].p2.y)
            swap(S[i].p1, S[i].p2);

        if (S[i].p1.y == S[i].p2.y) //把水平线段添加至列表
        {
            EP[k++] = EndPoint(S[i].p1, i, LEFT);
            EP[k++] = EndPoint(S[i].p2, i, RIGHT);
        }
        else
        {
            //把垂直线段添加至列表
            EP[k++] = EndPoint(S[i].p1, i, BOTTOM);
            EP[k++] = EndPoint(S[i].p2, i, TOP);
        }
    }

    sort(EP, EP + (2 * n)); //按照端点的y坐标升序排列

    set<int> BT; //二叉搜索树

    int cnt = 0;
    BT.insert(1000000001);

    for (int i = 0; i < 2 * n; ++i)
    {
        if (EP[i].st == TOP)
        {
            BT.erase(EP[i].p.x); //删除上端点
        }
        else if (EP[i].st == BOTTOM)
            BT.insert(EP[i].p.x); //添加下端点
        else if (EP[i].st == LEFT)
        {
            set<int>::iterator b = BT.lower_bound(S[EP[i].seg].p1.x);
            set<int>::iterator e = BT.upper_bound(S[EP[i].seg].p2.x);

            cnt += distance(b, e); //加上b、e之间的距离（点数）
        }
    }
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<Line> seg;
    for (int i = 0; i < n; ++i)
    {
        Line tmp;
        tmp.p1.read();
        tmp.p2.read();
        seg.push_back(tmp);
    }

    cout << manhattan(seg) << endl;
}
