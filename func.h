#pragma once

#include <iostream>
#include <cmath>
#include <functional>
#include <type_traits>

using namespace std;

//---------------------------------------------------
// base functions

class Const {
public:
    typedef Const Type;
    Const(double x)
        : m_const(x)
    {
    }
    Const(int x)
        : m_const(x)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return m_const;
    }
    operator double()
    {
        return m_const;
    }
    void print(void) const
    {
        cout << m_const;
    }
    double m_const;
};

const class Simple {
public:
    typedef Simple Type;
    const char id;
    Simple(const char id) : id(id)
    {
    }
    double operator()(double x, double y, double z) const
    {
        switch (id)
        {
        case 'x':
            return x;
        case 'y':
            return y;
        case 'z':
            return z;
        default:
            break;
        }
        return nan("Undefined value");
    }

    void print(void) const
    {
        cout << id;
    }
} X('x'), Y('y'), Z('z');

template <class F1, class F2>
class Add {
public:
    typedef Add<F1, F2> Type;
    Add(const F1& f1, const F2& f2)
        : m_f1(f1), m_f2(f2)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return m_f1(x, y, z) + m_f2(x, y, z);
    }
    void print(void) const
    {
        cout << "(", m_f1.print(), cout << " + ", m_f2.print(), cout << ")";
    }
    F1 m_f1;
    F2 m_f2;
};

template <class F1, class F2>
class Subtract {
public:
    typedef Subtract<F1, F2> Type;
    Subtract(const F1& f1, const F2& f2)
        : m_f1(f1), m_f2(f2)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return m_f1(x, y, z) - m_f2(x, y, z);
    }
    void print(void) const
    {
        cout << "(", m_f1.print(), cout << " - ", m_f2.print(), cout << ")";
    }
    F1 m_f1;
    F2 m_f2;
};

template <class F1, class F2>
class Multiply {
public:
    typedef Multiply<F1, F2> Type;
    Multiply(const F1& f1, const F2& f2)
        : m_f1(f1), m_f2(f2)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return m_f1(x, y, z) * m_f2(x, y, z);
    }
    void print(void) const
    {
        cout << "(", m_f1.print(), cout << " * ", m_f2.print(), cout << ")";
    }
    F1 m_f1;
    F2 m_f2;
};

template <class F1, class F2>
class Divide {
public:
    typedef Divide<F1, F2> Type;
    Divide(const F1& f1, const F2& f2)
        : m_f1(f1), m_f2(f2)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return m_f1(x, y, z) / m_f2(x, y, z);
    }
    void print(void) const
    {
        cout << "(", m_f1.print(), cout << " / ", m_f2.print(), cout << ")";
    }
    F1 m_f1;
    F2 m_f2;
};

template <class F>
class Power {
public:
    typedef Power<F> Type;
    Power(const F& f, double n)
        : m_f(f), m_n(n)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return pow(m_f(x, y, z), m_n);
    }
    void print(void) const
    {
        cout << "(",
        m_f.print();
        cout << "^" << m_n;
        cout << ")";
    }
    F m_f;
    double m_n;
};

template <class F>
class Exponent {
public:
    typedef Exponent<F> Type;
    Exponent(double base, const F& f)
        : m_base(base), m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return pow(m_base, m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "(",
        cout << m_base << "^";
        m_f.print();
        cout << ")";
    }
    double m_base;
    F m_f;
};

template <class F>
class Logarithm {
public:
    typedef Logarithm<F> Type;
    Logarithm(double base, const F& f)
        : m_base(base), m_factor(1 / log(base)), m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return log(m_f(x, y, z)) * m_factor;
    }
    void print(void) const
    {
        cout << "log(" << m_base << ", ";
        m_f.print();
        cout << ")";
    }
    double m_base, m_factor;
    F m_f;
};

template <class F>
class Sine {
public:
    typedef Sine<F> Type;
    Sine(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return sin(m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "sin(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

template <class F>
class Cosine {
public:
    typedef Cosine<F> Type;
    Cosine(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return cos(m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "cos(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

template <class F>
class Tangent {
public:
    typedef Tangent<F> Type;
    Tangent(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return tan(m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "tan(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

template <class F>
class Cotangent {
public:
    typedef Cotangent<F> Type;
    Cotangent(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return 1 / tan(m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "ctan(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

template <class F>
class Arcsine {
public:
    typedef Arcsine<F> Type;
    Arcsine(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return asin(m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "arcsin(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

template <class F>
class Arccosine {
public:
    typedef Arccosine<F> Type;
    Arccosine(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return acos(m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "arccos(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

template <class F>
class Arctangent {
public:
    typedef Arctangent<F> Type;
    Arctangent(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return atan(m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "arctan(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

template <class F>
class Arccotangent {
public:
    typedef Arccotangent<F> Type;
    Arccotangent(const F& f)
        : m_f(f)
    {
    }
    double operator()(double x, double y, double z) const
    {
        return atan(1 / m_f(x, y, z));
    }
    void print(void) const
    {
        cout << "arcctan(";
        m_f.print();
        cout << ")";
    }
    F m_f;
};

//---------------------------------------------------
// helpers

template <class F1, class F2>
Add<F1, F2> operator+(const F1& f1, const F2& f2)
{
    return Add<F1, F2>(f1, f2);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(double value, const F& f)
{
    return Add<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(const F& f, int value)
{
    return Add<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(int value, const F& f)
{
    return Add<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Add<F, Const>>::type operator+(const F& f, double value)
{
    return Add<F, Const>(f, Const(value));
}

template <class F1, class F2>
Subtract<F1, F2> operator-(const F1& f1, const F2& f2)
{
    return Subtract<F1, F2>(f1, f2);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<F, Const>>::type operator-(const F& f, double value)
{
    return Subtract<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<Const, F>>::type operator-(double value, const F& f)
{
    return Subtract<Const, F>(Const(value), f);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<F, Const>>::type operator-(const F& f, int value)
{
    return Subtract<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Subtract<Const, F>>::type operator-(int value, const F& f)
{
    return Subtract<Const, F>(Const(value), f);
}

template <class F1, class F2>
Multiply<F1, F2> operator*(const F1& f1, const F2& f2)
{
    return Multiply<F1, F2>(f1, f2);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(const F& f, double value)
{
    return Multiply<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(double value, const F& f)
{
    return Multiply<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(const F& f, int value)
{
    return Multiply<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Multiply<F, Const>>::type operator*(int value, const F& f)
{
    return Multiply<F, Const>(f, Const(value));
}

template <class F1, class F2>
Divide<F1, F2> operator/(const F1& f1, const F2& f2)
{
    return Divide<F1, F2>(f1, f2);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Divide<F, Const>>::type operator/(const F& f1, double value)
{
    return Divide<F, Const>(f1, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Divide<Const, F>>::type operator/(double value, const F& f)
{
    return Divide<Const, F>(Const(value), f);
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Divide<F, Const>>::type operator/(const F& f, int value)
{
    return Divide<F, Const>(f, Const(value));
}

template <class F>
typename std::enable_if<!std::is_arithmetic<F>::value, Divide<Const, F>>::type operator/(int value, const F& f)
{
    return Divide<Const, F>(Const(value), f);
}

template <class F>
Multiply<F, F> Sqr(const F& f)
{
    return Multiply<F, F>(f, f);
}

inline double Sqr(double x)
{
    return x * x;
}

template <class F, class Numeric>
Power<F> Pow(const F& f, Numeric n)
{
    return Power<F>(f, n);
}

inline double Pow(double x, double y)
{
    return pow(x, y);
}

template <class F>
Power<F> Sqrt(const F& f)
{
    return Power<F>(f, 0.5);
}

inline double Sqrt(double x)
{
    return sqrt(x);
}

template <class F>
Exponent<F> Exp(double base, const F& f)
{
    return Exponent<F>(base, f);
}

template <class F>
Exponent<F> Exp(int base, const F& f)
{
    return Exponent<F>(base, f);
}

inline double Exp(double base, double x)
{
    return pow(base, x);
}

template <class F>
Logarithm<F> Log(double base, const F& f)
{
    return Logarithm<F>(base, f);
}

template <class F>
Logarithm<F> Log(int base, const F& f)
{
    return Logarithm<F>(base, f);
}

inline double Log(double base, double x)
{
    return log(x) / log(base);
}

template <class F>
Sine<F> Sin(const F& f)
{
    return Sine<F>(f);
}

inline double Sin(double x)
{
    return sin(x);
}

template <class F>
Cosine<F> Cos(const F& f)
{
    return Cosine<F>(f);
}

inline double Cos(double x)
{
    return cos(x);
}

template <class F>
Tangent<F> Tg(const F& f)
{
    return Tangent<F>(f);
}

inline double Tg(double x)
{
    return tan(x);
}

template <class F>
Cotangent<F> Ctg(const F& f)
{
    return Cotangent<F>(f);
}

inline double Ctg(double x)
{
    return 1 / tan(x);
}

template <class F>
Arcsine<F> Asin(const F& f)
{
    return Arcsine<F>(f);
}

inline double Asin(double x)
{
    return asin(x);
}

template <class F>
Arccosine<F> Acos(const F& f)
{
    return Arccosine<F>(f);
}

inline double Acos(double x)
{
    return acos(x);
}

template <class F>
Arctangent<F> Atg(const F& f)
{
    return Arctangent<F>(f);
}

inline double Atg(double x)
{
    return atan(x);
}

template <class F>
Arccotangent<F> Actg(const F& f)
{
    return Arccotangent<F>(f);
}

inline double Actg(double x)
{
    return atan(1 / x);
}

//---------------------------------------------------
// derivative

template <class F>
class Derivative {
public:
    Derivative(const F& f, Simple d, double step = 1e-3)
        : m_f(f), m_d(d), m_step(step)
    {
    }
    double operator()(double x, double y, double z) const
    {
        switch (m_d.id)
        {
        case 'x':
            return (m_f(x + m_step / 2, y, z) - m_f(x - m_step / 2, y, z)) / m_step;
        case 'y':
            return (m_f(x, y + m_step / 2, z) - m_f(x, y - m_step / 2, z)) / m_step;
        case 'z':
            return (m_f(x, y, z + m_step / 2) - m_f(x, y, z - m_step / 2)) / m_step;
        default:
            break;
        }
        return 0;
    }
    F m_f;
    const double m_step;
    Simple m_d;
    typedef std::function<double(double, double, double)> Type;
    Type expression() const
    {
        switch (m_d.id)
        {
        case 'x':
            return [this](double x, double y, double z) -> double
            {
                return (m_f(x + this->m_step / 2, y, z) - m_f(x - m_step / 2, y, z)) / m_step;
            };
        case 'y':
            return [this](double x, double y, double z) -> double
            {
                return (m_f(x, y + m_step / 2, z) - m_f(x, y - m_step / 2, z)) / m_step;
            };
        case 'z':
            return [this](double x, double y, double z) -> double
            {
                return (m_f(x, y, z + m_step / 2) - m_f(x, y, z - m_step / 2)) / m_step;
            };
        default:
            break;
        }
        return [this](double x, double y, double z) -> double
        {
            return 0;
        };
    }
    void print(void) const {
        cout << "d(";
        m_f.print();
        cout << ")/d" << m_d.id;
    }
};

template <class F>
double derivative(F f, double x, double y, double z, Simple d, double step = 1e-3)
{
    switch (d.id)
    {
    case 'x':
        return (f(x + step / 2, y, z) - f(x - step / 2, y, z)) / step;
    case 'y':
        return (f(x, y + step / 2, z) - f(x, y - step / 2, z)) / step;
    case 'z':
        return (f(x, y, z + step / 2) - f(x, y, z - step / 2)) / step;
    default:
        break;
    }
    return 0;
}

template <class F>
Derivative<F> derivative(F f, Simple d, double step = 1e-3)
{
    return Derivative<F>(f, d, step);
}
