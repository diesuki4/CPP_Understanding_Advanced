#include <iostream>

using namespace std;

/*
 * 값 표현식을 통한 타입 유추 구현
 */

// 포인터는 크기를 알 수 있으므로, 전방 선언이 가능
struct Widget;
Widget* p;

struct Widget { };

namespace mystd
{
    typedef char A1[1];
    using A2 = char[2];
    using A3 = char[3];

    /* 반환 형이 포인터면, 함수의 몸체를 정의하지 않을 수 있다. */
    A1* select_array(short);    // 크기가 1 인 A1 를 short 에 매핑
    A2* select_array(int);      // 크기가 2 인 A2 를  int  에 매핑
    A3* select_array(float);    // 크기가 3 인 A3 를 float 에 매핑

    template <int T>
    struct select_type    { };
    template <>
    struct select_type<1> { using type = short; };   // A1 의 크기가 1 이므로
    template <>
    struct select_type<2> { using type = int; };     // A2 의 크기가 2 이므로
    template <>
    struct select_type<3> { using type = float; };   // A3 의 크기가 3 이므로
};

#define typeof(x) select_type<sizeof(*select_array(x))>::type

int main(int argc, char* argv[])
{
    // int
    decltype(1 + 2) i = 10;

    cout << sizeof(i) << endl;
    cout << sizeof(1 + 2) << endl;

    using namespace mystd;

    cout << sizeof(A1) << endl;
    cout << sizeof(A2) << endl;
    cout << sizeof(A3) << endl;

    typeof(short(1)) s;  // short
    typeof(1 + 2) n;     // int
    typeof(3.5F) f;      // float

    return 0;
}
