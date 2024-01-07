#include <iostream>

using namespace std;

/*
 * auto, decltype
 */

// Trailing Return Type
auto Add(int a, int b) -> int
{
    return a + b;
}

/* 과거에는 <int, int> 는 int, <int, float> 은 float 로
 * 알아서 반환할 수 있는 방법이 없었다.
 *
 * auto 시점에서는 아직 t, u 의 타입을 알 수 없다. */
template <typename T, typename U>
auto Add2(T t, U u) /* -> decltype(t + u) */
{
    return t + u;
}

int main(int argc, char* argv[])
{
    // int
    auto a = 3, b = 6;

    cout << Add(3, 6) << endl;        // int

    cout << Add2(3, 6) << endl;       // int
    cout << Add2(10, 20.4F) << endl;  // float

    return 0;
}
