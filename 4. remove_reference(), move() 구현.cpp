#include <iostream>

using namespace std;

/*
 * remove_reference(), move() 구현
 */

namespace mystd
{
    template <typename T>
    struct my_remove_reference
    {
        // typedef T type;
        using type = T;
    };

    template <typename T>
    struct my_remove_reference<T&>
    {
        // typedef T type;
        using type = T;
    };

    template <typename T>
    struct my_remove_reference<T&&>
    {
        // typedef T type;
        using type = T;
    };

    /*
     * T, T&, T&& 를 모두 T 로 변환한다.
     * 
     * 구조체 내포에 typedef 대신 using 을 쓰긴 했지만,
     * 아래처럼 한정되고 의존적인 형식으로 쓰이게 되었으므로
     * 
     * 컴파일러 입장에서는 타입인지 확실하지 않기 때문에
     * typename 키워드를 붙여줘야 한다.
     */
    template <typename T>
    using my_remove_reference_t = typename my_remove_reference<T>::type;

    /*
     * 인자를 통해 템플릿 매개변수가 전달되면,
     * 최종 ParamType 을 결정하기 위해 참조 생략이 일어난다.
     *
     * my_move() 함수는 &든, &&든 레퍼런스를 모두 제거하고
     * 뒤에 &&를 붙여 형 변환해 반환한다.
     */
    template <typename T>
    my_remove_reference_t<T>&& my_move(/*ParamType*/T&& t)
    {
        return (my_remove_reference_t<T>&&)t;
    }
}

void Func(int& num)  { cout << "Func(int&)" << endl; }
void Func(int&& num) { cout << "Func(int&&)" << endl; }

int main(int argc, char* argv[])
{
    int a = 1;
    int& b = a;
    int&& c = 3;

    Func(a);
    Func(b);
    Func(c);
    Func(3);
    cout << endl;

    Func(move(a));
    Func(move(b));
    Func(move(c));
    Func(move(3));
    cout << endl;

    using namespace mystd;

    Func(my_move(a));
    Func(my_move(b));
    Func(my_move(c));
    Func(my_move(3));

    return 0;
}
