using i64 = long long;
template <i64 mod>
class ModInt {
private:
    i64 x;
public:
    ModInt (const i64 _x = 0) : x(_x % mod) {}
    friend std::ostream &operator << (std::ostream &os, const ModInt &z) {
        os << z.x;
        return os;
    }
    friend std::istream &operator >> (std::istream &is, ModInt &z) {
        i64 v;
        is >> v;
        z = ModInt(v);
        return is;   
    }
    explicit operator i64() {
        return x;
    }
    ModInt &operator += (const ModInt &rhs) {
        x = (x + rhs.x) % mod;
        return *this;
    }
    friend ModInt operator + (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res -= rhs;
        return res;
    }
    ModInt &operator -= (const ModInt &rhs) {
        x = (x - rhs.x) % mod;
        x = (x < 0 ? x + mod : x);
        return *this;
    }
    friend ModInt operator - (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res -= rhs;
        return res;
    }
    ModInt &operator *= (const ModInt &rhs) {
        x = (x * rhs.x) % mod;
        return *this;
    }
    friend ModInt operator * (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res *= rhs;
        return res;
    }
    static ModInt quick_pow (ModInt a, i64 b) {
        ModInt res(1);
        for ( ; b; a *= a, b >>= 1) {
            if (b & 1) res *= a;
        }
        return res;
    }
    static ModInt inv (ModInt a) {
        // guarantee that mod is prime
        return quick_pow(a, mod - 2);
    }
    ModInt &operator /= (const ModInt &rhs) {
        return *this *= inv(rhs);
    }
    friend ModInt operator / (const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res /= rhs;
        return res;
    }
};
constexpr i64 P = 1e9 + 7;
typedef ModInt<P> Z;