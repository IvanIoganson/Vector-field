#pragma once

#include <glm/vec3.hpp>

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
    glm::vec3 operator()(const glm::vec3 &v) const {
        return glm::vec3(i(v.x, v.y, v.z), j(v.x, v.y, v.z), k(v.x, v.y, v.z));
    }
    vec_field operator+ (const vec_field &vf) const {
        return vec_field(i + vf.i, j + vf.j, k + vf.k);
    }
    vec_field operator- (const vec_field &vf) const {
        return vec_field(i - vf.i, j - vf.j, k - vf.k);
    }
    auto operator* (const vec_field &vf) {
        return (i * vf.i + j * vf.j + k * vf.k);
    }
    template<class F>
    vec_field operator*(const F &f) const {
        return vec_field(i * f, j * f, k * f);
    }
};

template<class F11, class F12, class F13, class F21, class F22, class F23>
auto operator% (const vec_field<F11, F12, F13> &vf1, const vec_field<F21, F22, F23> &vf2) {
    auto ni = vf1.j * vf2.k - vf1.k * vf2.j;
    auto nj = vf1.k * vf2.i - vf1.i * vf2.k;
    auto nk = vf1.i * vf2.j - vf1.j * vf2.i;
    return CreateVecField(ni, nj, nk);
}

template<class F, class F1, class F2, class F3>
auto operator*(const F &f, const vec_field<F1, F2, F3> &vf1) {
    return CreateVecField(f * vf1.i, f * vf1.j, f * vf1.k);
}

template<class F1, class F2, class F3>
auto div(const vec_field<F1, F2, F3> &vf, double step = 1e-3) {
    return derivative(vf.i, X, step) + derivative(vf.j, Y, step) + derivative(vf.k, Z, step);
}

template<class F1, class F2, class F3>
auto rot(const vec_field<F1, F2, F3> &vf, double step = 1e-3) {
    return vec_field<Subtract<Derivative<F3>, Derivative<F2>>, Subtract<Derivative<F1>, Derivative<F3>>, Subtract<Derivative<F2>, Derivative<F1>>>
    (derivative(vf.k, Y, step) - derivative(vf.j, Z, step), derivative(vf.i, Z, step) - derivative(vf.k, X, step),
        derivative(vf.j, X, step) - derivative(vf.i, Y, step));
}

template<class F1, class F2, class F3>
auto CreateVecField(const F1 &i, const F2 &j, const F3 &k)
{
    return vec_field<F1, F2, F3>(i, j, k);
}

template <class F>
auto grad(const F &f) {
    return CreateVecField(derivative(f, X), derivative(f, Y), derivative(f, Z));
}