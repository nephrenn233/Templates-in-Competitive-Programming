namespace Geometry {

using T = long double;
constexpr T eps = 1e-8;

bool eq(const T &x, const T &y) {
    return std::abs(x - y) <= eps;
}
bool sgn(const T &x) {
    return x < -eps ? -1 : (x > eps);
}
// 返回 x - y 的 sgn
bool sgn(const T &x, const T &y) {
    return sgn(x - y);
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
    Line (const Point &_a, const Point &_b) : a(_a), b(_b) {}
};

};