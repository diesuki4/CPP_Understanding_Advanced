#include <iostream>

using namespace std;

/*
 * 폴드 표현식 (Fold Expression)
 */

template <int N>
struct Sum1
{
    enum { value = N + Sum1<N - 1>::value };
};

template <>
struct Sum1<0>
{
    enum { value = 0 };
};

auto Sum2()
{
    return 0;
}

template <typename N0, typename... Ns>
auto Sum2(N0 n0, Ns... ns)
{
    return n0 + Sum2(ns...);
}

/* <폴드 표현식>
 *
 * 종료 조건을 작성할 필요가 없다.
 *
 * 단, 괄호와 가장 마지막에 붙을 인자를 명시해줘야 한다. */
template <typename... Ns>
auto Sum3(Ns... ns)
{
    // Sum3<int>(1) + Sum3<float>(2.4F) + Sum3<double>(3.8) + Sum3<int>(0)
    return (ns + ... + 0);
}

int main(int argc, char* argv[])
{
    cout << Sum1<10>::value << endl;
    cout << Sum2(1, 2.4F, 3.8) << endl;
    cout << Sum3(1, 2.4F, 3.8) << endl;

    return 0;
}
