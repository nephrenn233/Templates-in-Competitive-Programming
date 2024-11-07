namespace Geometry {
using T = long double;
constexpr T eps = 1e-8;
 
bool eq(const T &x, const T &y) {
    return std::abs(x - y) <= eps;
}
bool sgn(const T &x) {
    return x < -eps ? -1 : (x > eps);
}
bool sgn(const T &x, const T &y) {
    return x - y < -eps ? -1 : (x - y > eps);
}
struct Point {
    T x, y;
    Point(const T &_x = 0, const T &_y = 0) : x(_x), y(_y) {}
    
    Point &operator += (const Point &p) & {
        x += p.x, y += p.y;
        return *this;
    }
    Point &operator -= (const Point &p) & {
        x -= p.x, y -= p.y;
        return *this;
    }
    Point &operator *= (const T &v) & {
        x *= v, y *= v;
        return *this;
    }
    Point &operator /= (const T &v) & {
        x /= v, y /= v;
        return *this;
    }
    Point operator - () const {
        return Point(-x, -y);
    }
    friend Point operator + (Point a, const Point &b) {
        return a += b;
    }
    friend Point operator - (Point a, const Point &b) {
        return a -= b;
    }
    friend Point operator * (Point a, const T &b) {
        return a *= b;
    }
    friend Point operator / (Point a, const T &b) {
        return a /= b;
    }
    friend Point operator * (const T &a, Point b) {
        return b *= a;
    }
    friend bool operator == (const Point &a, const Point &b) {
        return eq(a.x, b.x) && eq(a.y, b.y);
    }
    friend bool operator != (const Point &a, const Point &b) {
        return !(a == b);
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

struct Line {
    Point a, b;
    Line(Point a, Point b) : a(a), b(b) {}
    // ax + by = c
    Line(T A, T B, T C) {
        if(A == 0) {
            a = Point(0, C / B), b = Point(1, C / B);
        } else if(B == 0) {
            a = Point(C / A, 0), b = Point(C / A, 1);
        } else {
            a = Point(0, C / B), b = Point(C / A, 0);
        }
    }
};

struct Segment : Line {
    Segment(Point a, Point b) : Line(a, b) {}
};
 
struct Circle {
    Point p;
    T r;
    Circle() = default;
    Circle(Point p, T r) : p(p), r(r) {}
};

T dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}

T cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

T square(const Point &p) {
    return dot(p, p);
}

double length(const Point &p) {
    return std::sqrt(square(p));
}

double length(const Line &l) {
    return length(l.a - l.b);
}

Point normalize(const Point &p) {
    return p / length(p);
}

bool parallel(const Line &l1, const Line &l2) {
    return sgn(cross(l1.b - l1.a, l2.b - l2.a)) == 0;
}

bool orthogonal(const Line &a, const Line &b) {
    return sgn(dot(a.a - a.b, b.a - b.b)) == 0;
}

double distance(const Point &a, const Point &b) {
    return length(a - b);
}

double distancePL(const Point &p, const Line &l) {
    return std::abs(cross(l.a - l.b, l.a - p)) / length(l);
}

double distancePS(const Point &p, const Line &l) {
    if (dot(p - l.a, l.b - l.a) < 0) {
        return distance(p, l.a);
    }
    if (dot(p - l.b, l.a - l.b) < 0) {
        return distance(p, l.b);
    }
    return distancePL(p, l);
}

// 逆时针旋转九十度
Point rotate(const Point &a) {
    return Point(-a.y, a.x);
}

// 点在直线的逆时针方向
bool pointOnLineLeft(const Point &p, const Line &l) {
    return sgn(cross(l.b - l.a, p - l.a)) > 0;
}

// 两直线交点
Point lineIntersection(const Line &l1, const Line &l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

// 点在线段上
bool pointOnSegment(const Point &p, const Line &l) {
    return sgn(cross(p - l.a, l.b - l.a)) == 0 && sgn(std::min(l.a.x, l.b.x), p.x) <= 0 && sgn(std::max(l.a.x, l.b.x), p.x) >= 0
        && sgn(std::min(l.a.y, l.b.y), p.y) <= 0 && sgn(std::max(l.a.y, l.b.y), p.y) >= 0;
}

// 点在多边形内
bool pointInPolygon(const Point &a, const std::vector<Point> &p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    
    int t = 0;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (sgn(u.x, a.x) < 0 && sgn(v.x, a.x) >= 0 && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if (sgn(u.x, a.x) >= 0 && sgn(v.x, a.x) < 0 && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }
    
    return t == 1;
}

// 线段相交
// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
std::tuple<int, Point, Point> segmentIntersection(const Line &l1, const Line &l2) {
    if (sgn(std::max(l1.a.x, l1.b.x), std::min(l2.a.x, l2.b.x)) < 0) {
        return {0, Point(), Point()};
    }
    if (sgn(std::min(l1.a.x, l1.b.x), std::max(l2.a.x, l2.b.x)) > 0) {
        return {0, Point(), Point()};
    }
    if (sgn(std::max(l1.a.y, l1.b.y), std::min(l2.a.y, l2.b.y)) < 0) {
        return {0, Point(), Point()};
    }
    if (sgn(std::min(l1.a.y, l1.b.y), std::max(l2.a.y, l2.b.y)) > 0) {
        return {0, Point(), Point()};
    }
    if (sgn(cross(l1.b - l1.a, l2.b - l2.a)) == 0) {
        if (sgn(cross(l1.b - l1.a, l2.a - l1.a)) != 0) {
            return {0, Point(), Point()};
        } else {
            auto maxx1 = std::max(l1.a.x, l1.b.x);
            auto minx1 = std::min(l1.a.x, l1.b.x);
            auto maxy1 = std::max(l1.a.y, l1.b.y);
            auto miny1 = std::min(l1.a.y, l1.b.y);
            auto maxx2 = std::max(l2.a.x, l2.b.x);
            auto minx2 = std::min(l2.a.x, l2.b.x);
            auto maxy2 = std::max(l2.a.y, l2.b.y);
            auto miny2 = std::min(l2.a.y, l2.b.y);
            Point p1(std::max(minx1, minx2), std::max(miny1, miny2));
            Point p2(std::min(maxx1, maxx2), std::min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) {
                std::swap(p1.y, p2.y);
            }
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    
    if ((sgn(cp1) > 0 && sgn(cp2) > 0) || (sgn(cp1) < 0 && sgn(cp2) < 0) || (sgn(cp3) > 0 && sgn(cp4) > 0) || (sgn(cp3) < 0 && sgn(cp4) < 0)) {
        return {0, Point(), Point()};
    }
    
    Point p = lineIntersection(l1, l2);
    if (sgn(cp1) != 0 && sgn(cp2) != 0 && sgn(cp3) != 0 && sgn(cp4) != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}

double distanceSS(const Line &l1, const Line &l2) {
    if (std::get<0>(segmentIntersection(l1, l2)) != 0) {
        return 0.0;
    }
    return std::min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}

bool segmentInPolygon(const Line &l, const std::vector<Point> &p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) {
        return false;
    }
    if (!pointInPolygon(l.b, p)) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));
        
        if (t == 1) {
            return false;
        }
        if (t == 0) {
            continue;
        }
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b) {
                if (sgn(cross(v - u, w - v)) > 0) {
                    return false;
                }
            }
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u))
                    || pointOnLineLeft(l.b, Line(v, u))) {
                    return false;
                }
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l)
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            && pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

// for halfplane_intersection
int sgn(const Point &a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

std::vector<Point> halfplane_intersection(std::vector<Line> lines) {
    std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        
        if (sgn(d1) != sgn(d2)) {
            return sgn(d1) == 1;
        }
        
        return sgn(cross(d1, d2)) > 0;
    });
    
    std::deque<Line> ls;
    std::deque<Point> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }
        
        while (!ps.empty() && !pointOnLineLeft(ps.back(), l)) {
            ps.pop_back();
            ls.pop_back();
        }
        
        while (!ps.empty() && !pointOnLineLeft(ps[0], l)) {
            ps.pop_front();
            ls.pop_front();
        }
        
        if (sgn(cross(l.b - l.a, ls.back().b - ls.back().a)) == 0) {
            if (sgn(dot(l.b - l.a, ls.back().b - ls.back().a)) > 0) {
                
                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }
        
        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }
    
    while (!ps.empty() && !pointOnLineLeft(ps.back(), ls[0])) {
        ps.pop_back();
        ls.pop_back();
    }
    if (ls.size() <= 2) {
        return {};
    }
    ps.push_back(lineIntersection(ls[0], ls.back()));
    
    return std::vector(ps.begin(), ps.end());
}

std::vector<Point> convexHullAndrew(std::vector<Point> p) {
    if(p.size() <= 2) return {}; // 或 return p
    std::sort(p.begin(), p.end(),
        [&](auto a, auto b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        });
    std::vector<Point> res;
    for(int i = 0; i < p.size(); ++i) {
        while(res.size() > 1 && sgn(cross(res[res.size() - 1] - res[res.size() - 2], p[i] - res[res.size() - 1]) <= 0)) {
            res.pop_back();
        }
        res.push_back(p[i]);
    }
    int fix = res.size();
    for(int i = p.size() - 2; i >= 0; --i) {
        while(res.size() > fix && sgn(cross(res[res.size() - 1] - res[res.size() - 2], p[i] - res[res.size() - 1]) <= 0)) {
            res.pop_back();
        }
        res.push_back(p[i]);
    }
    res.pop_back();
    return res;
}

// 不严格凸性
bool isConvex(const std::vector<Point> &p) {
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        Point a = p[(i - 1 + n) % n], b = p[i], c = p[(i + 1) % n];
        if (sgn(cross(b - a, c - a)) < 0) return false;
    }
    return true;
}

// 面积的两倍
T area2(const std::vector<Point> &p) {
    T res = 0;
    for(int i = 0; i < p.size(); ++i) {
        int j = (i + 1) % p.size();
        res += cross(p[i], p[j]);
    }
    return res;
}

std::vector<Point> minkovskiSum(std::vector<std::vector<Point>> a) {
    // a[0], a[1] 起点为左下角的逆时针凸包
    for(int i = 0; i < 2; ++i) a[i].push_back(a[i].front());
    int i[2] = {0, 0}, len[2] = {(int)a[0].size() - 1, (int)a[1].size() - 1};
    std::vector<Point> res;
    res.push_back(a[0][0] + a[1][0]);
    do { // 凸包退化时会死循环
        int d = sgn(cross(a[1][i[1] + 1] - a[1][i[1]], a[0][i[0] + 1] - a[0][i[0]])) >= 0;
        res.push_back(a[d][i[d] + 1] - a[d][i[d]] + res.back());
        i[d] = (i[d] + 1) % len[d];
    } while(i[0] || i[1]);
    return res; // 结果不是严格凸包
}
}
using namespace Geometry;