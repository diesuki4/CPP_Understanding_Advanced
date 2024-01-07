#include <iostream>

using namespace std;

/*
 * 타입 표현식을 통한 타입 유추 구현
 */

namespace mystd
{
    template <typename T>
    struct Type2Value
    {
        static const T value;
    };
    template <typename T>
    const T Type2Value<T>::value = 0;

    template <typename T, typename U>
    struct TypeResolver
    {
        using type = decltype(Type2Value<T>::value + Type2Value<U>::value);
    };
};

#define typeof(x) select_type<sizeof(*select_array(x))>::type

int main(int argc, char* argv[])
{
    using namespace mystd;

    TypeResolver<int, float>::type f = 3.5F;    // float
    TypeResolver<char, double>::type d = 4.7;   // double

    return 0;
}
