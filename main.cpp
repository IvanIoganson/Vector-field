#include <iostream>
#include "func.h"
#include "vec_field.h"

using namespace std;

auto global = Tg(X) + Ctg(X) + Asin(Sin(Pow(X, 4.567))) * Acos(Log(10, X)) - Atg(X) / Actg(X);

int main()
{
    auto f1 = Pow(X * Y, 4);
    auto f2 = Sin(Y);
    auto f3 = Log(2, Z);

    auto v = CreateVecField(f1, f2, f3);

    auto d_global = derivative(global, X);

    v.print();
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
    cout << " = " << f1(5, 0, 0) << endl;
    cout << derivative(f1, 1, 1, 0, X) << endl;
    global.print();
    cout << " = " << global(5, 0, 0) << endl;
    auto d = d_global(3, 0, 0);
    cout << derivative(global, 3, 0, 0, X) << " " << d << endl;

    char temp[4];
    cout << "\nPress ENTER to exit..." << endl;
    cin.getline(temp, 3);
    return 0;
}