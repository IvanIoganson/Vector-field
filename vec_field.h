#pragma once

#include "func.h"

template<class F1, class F2, class F3>
class vec_field {
public:
    F1 i;
    F2 j;
    F3 k;
    vec_field(const F1 &i, const F2 &j, const F3 &k): i(i), j(j), k(k){}
    void print(void) const {
        cout << "(";
        i.print();
        cout << ") * i + ";
        cout << "(";
        j.print();
        cout << ") * j + ";
        cout << "(";
        k.print();
        cout << ") * k";
    }
    double *operator()(double x, double y, double z) const {
        double *arr = new double[3];
        arr[0] = i(x, y, z), arr[1] = j(x, y, z), arr[2] = k(x, y, z);
        return arr;
    }
    vec_field operator+ (const vec_field &vf) const {
        return vec_field(i + vf.i, j + vf.j, k + vf.k);
    }
    vec_field operator- (const vec_field &vf) const {
        return vec_field(i - vf.i, j - vf.j, k - vf.k);
    }
    template<class F>
    F operator* (const vec_field &vf) {
        return (i * vf.i + j * vf.j + k * vf.k);
    }
    vec_field operator% (const vec_field &vf) const {
        return vec_field(j * vf.k - k * vf.j, k * vf.i - i * vf * k, i * vf.j - j * vf.i );
    }
    template<class F>
    vec_field operator*(const F &f) const {
        return vec_field(i * f, j * f, k * f);
    }
};

template<class F1, class F2, class F3>
Add<Add<Derivative<F1>, Derivative<F2>>, Derivative<F3>> div(const vec_field<F1, F2, F3> &vf, double step = 1e-3) {
    return derivative(vf.i, X, step) + derivative(vf.j, Y, step) + derivative(vf.k, Z, step);
}

template<class F1, class F2, class F3>
vec_field<Subtract<Derivative<F3>, Derivative<F2>>, Subtract<Derivative<F1>, Derivative<F3>>, Subtract<Derivative<F2>, Derivative<F1>>>
  rot(const vec_field<F1, F2, F3> &vf, double step = 1e-3) {
    return vec_field<Subtract<Derivative<F3>, Derivative<F2>>, Subtract<Derivative<F1>, Derivative<F3>>, Subtract<Derivative<F2>, Derivative<F1>>>
    (derivative(vf.k, Y, step) - derivative(vf.j, Z, step), derivative(vf.i, Z, step) - derivative(vf.k, X, step),
        derivative(vf.j, X, step) - derivative(vf.i, Y, step));
}

template<class F1, class F2, class F3>
vec_field<F1, F2, F3> CreateVecField(const F1 &i, const F2 &j, const F3 &k)
{
    return vec_field<F1, F2, F3>(i, j, k);
}