#include <GL/glut.h>
#include <iostream>
#include "func.h"
#include "vec_field.h"
#include "opengl_func.h"

using namespace std;

auto global = Tg(X) + Ctg(X) + Tg(10 ^ Sin(Pow(X, 4.567))) * Acos(Log(10, X)) - Atg(X) / Actg(X);

auto f1 = (X * Y) ^ Z;
auto f2 = Sin(Y);
auto f3 = Log(2, Z);

auto v = CreateVecField(f1, f2, f3);

int main(int argc, char **argv)
{
    auto d_global = derivative(derivative(derivative(derivative(derivative(global, X), X), X), X), X);

    v.print();
    cout << endl << "V * V :";
    (v*v).print();
    cout << endl << "V % V :";
    (v%v).print();
    cout << endl;
    cout << endl << "global * V:";
    (global * v).print();
    cout << endl;
    double *arr = v(1, 2, 3);
    cout << "(1,2,3) : " << arr[0] << ' ' << arr[1] << ' ' << arr[2] << endl;
    arr = rot(v)(1, 2, 3);
    auto divv = div(v);
    cout << "rot: ";
    rot(v).print();
    cout << endl << "rot(1,2,3): " << arr[0] << ' ' << arr[1] << ' ' << arr[2] << endl;
    cout << "div: ";
    divv.print();
    cout << endl << "div(1,2,3): " << divv(1, 2, 3) << endl;
    f1.print();
    cout << " = " << f1(5, -3, 2) << endl;
    cout << derivative(f1, -2.5, 5, 0.5, X) << endl;
    global.print();
    cout << " = " << global(5, 0, 0) << endl;
    auto d = d_global(3, 0, 0);
    cout << derivative(global, 3, 0, 0, X) << " " << d << endl;

    Init(argc, argv);

    /*char temp[4];
    cout << "\nPress ENTER to exit..." << endl;
    cin.getline(temp, 3);*/
    return 0;
}