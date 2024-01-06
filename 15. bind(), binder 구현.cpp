#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

/*
 * bind(), binder 구현
 */

int print(int i) { cout << i << endl; return i; }

class Widget
{
public:
    int print(int i)         { cout << i << endl; return i; }
    int print2(int i, int j) { cout << i << " " << j << endl; return i + j; }
};

namespace mystd
{
    template <typename T>
    class mybinder
    {
        using type = T;
    };

    // 함수 포인터에 대한 특수화
    template <typename T>
    class mybinder<T(*)>
    {
    public:
        int operator() (T pred, int i)
        {
            return pred(i);
        }
    };

    // 멤버 함수 포인터에 대한 특수화
    template <typename T, typename U>
    class mybinder<T(U::*)>
    {
    public:
        using PRED = int (U::*)(int);

    private:
        PRED mpred;

    public:
        mybinder(PRED pred = nullptr) : mpred(pred) { }

        int operator() (U& lhs, int i)
        {
            return (lhs.*mpred)(i);
        }

        int operator() (PRED pred, U& lhs, int i)
        {
            return (lhs.*pred)(i);
        }
    };

    template <typename T>
    typename mybinder<T> mybind(T pred)
    {
        return mybinder<T>(pred);
    }
};

int main(int argc, char* argv[])
{
    using namespace mystd;

    mybinder<decltype(print)*> mbd;
    mbd(print, 5);

    Widget w;

    mybinder<decltype(&Widget::print)> mbdm(&Widget::print);
    mbdm(w, 5);

    mybinder<decltype(&Widget::print)> mbdm2;
    mbdm2(&Widget::print, w, 5);

    mybind(&Widget::print)(w, 5);

    return 0;
}
