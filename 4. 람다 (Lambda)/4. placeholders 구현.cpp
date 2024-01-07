#include <iostream>

using namespace std;

/*
 * placeholders 구현
 */

namespace mystd
{
    template <int value>
    struct _Ph { };

    using _M1 = _Ph<1>;
    using _M2 = _Ph<2>;
    using _M3 = _Ph<3>;
    /* ... */

    struct void_;
    // 실제로는 가변 인자 템플릿으로 구현되어 있다.
    template <typename Selector, typename A = void_, typename B = void_>
    struct MyTypeSelector
    {
        using type = void_;
    };

    template <typename A, typename B>
    struct MyTypeSelector<_M1, A, B>
    {
        using type = A;
    };

    template <typename A, typename B>
    struct MyTypeSelector<_M2, A, B>
    {
        using type = B;
    };

    template <typename Selector>
    struct MyValueSelector
    {
        void operator() ()
        {
        }
    };

    template <>
    struct MyValueSelector<_M1>
    {
        template <typename C>
        C& operator() (C& first)
        {
            return first;
        }

        template <typename C, typename D>
        C& operator() (C& first, D& second)
        {
            return first;
        }
    };

    template <>
    struct MyValueSelector<_M2>
    {
        template <typename C, typename D>
        D& operator() (C& first, D& second)
        {
            return second;
        }
    };
};

int main(int argc, char* argv[])
{
    using namespace mystd;

    // 1번째인 int 를 type 으로 가져온다.
    MyTypeSelector<_M1, int, float>::type i = 10;

    // 2번째인 float 를 type 으로 가져온다.
    MyTypeSelector<_M2, int, float>::type f = 3.5F;

    int a;
    float b, c;

    MyValueSelector<_M1>()(a, b) = 3;     // a = 3;
    MyValueSelector<_M2>()(a, b) = 4.5F;  // b = 4.5F;
    MyValueSelector<_M1>()(c) = 6.7F;     // c = 6.7F;

    return 0;
}
