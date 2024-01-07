#include <iostream>

using namespace std;

/*
 * forward() 구현
 */

namespace mystd
{
    /*
     * l-value 레퍼런스를 l-value 혹은 r-value 레퍼런스로 반환한다.
     * 
     * forward<int>(i)    ==>  int&&
     * forward<int&>(i)   ==>  int&
     * forward<int&&>(i)  ==>  int&&
     */
    template <typename T>
    T&& my_forward(remove_reference_t<T>& t)
    {
        return static_cast<T&&>(t);
    }

    /*
     * r-value 레퍼런스를 r-value 레퍼런스로 반환한다.
     * 
     * forward<int>(5)    ==>  int&&
     * forward<int&&>(5)  ==>  int&&
     */
    template <typename T>
    T&& my_forward(remove_reference_t<T>&& t)
    {
        // forward<int&>(5) 같은 비정상적인 호출
        static_assert(!is_lvalue_reference_v<T>, "bad forward call");

        return static_cast<T&&>(t);
    }
}

void Foo(int& num)  { cout << "Foo(int&)" << endl; }
void Foo(int&& num) { cout << "Foo(int&&)" << endl; }

template <typename T>
void Bar(T&& t)     { cout << "Bar(T&&)" << endl; Foo(forward<T>(t)); }

template <typename T>
void Car(T&& t)     { cout << "Car(T&&)" << endl; Foo(mystd::my_forward<T>(t)); }

int main(int argc, char* argv[])
{
    int i = 5;

    Bar(i);
    Bar(5);
    cout << endl;

    Car(i);
    Car(5);

    return 0;
}
