#include <iostream>

using namespace std;

/*
 * tuple 구현
 */

namespace mystd
{
    template <int...>
    struct seq
    {
    };

    template <int max, int... s>
    struct make_seq : make_seq<max - 1, max - 1, s...>
    {
    };

    template <int... s>
    struct make_seq<0, s...>
    {
        using type = seq<s...>;
    };

    template <int max>
    using MakeSeq = typename make_seq<max>::type;

    template <int x, typename Arg>
    struct storage
    {
        Arg data;
    };

    template <typename Seq, typename... Args>
    struct helper
    {
    };

    template <int s0, int... s, typename A0, typename... Args>
    struct helper<seq<s0, s...>, A0, Args...>
        : storage<s0, A0>, helper<seq<s...>, Args...>
    {
    };

    // mytuple<char, int, double>
    // mytuple<char, int, double> : helper<MakeSeq<3>, char, int, double>
    // mytuple<char, int, double> : helper<seq<0, 1, 2>, char, int, double>
    template <typename... Args>
    struct mytuple : helper<MakeSeq<sizeof...(Args)>, Args...>
    {
        // sizeof...(Args) 연산자는 파라미터 팩의 템플릿 매개변수 개수를 구한다.
    };

    template <int N, typename T>
    T& myget(storage<N, T>& f)
    {
        return f.data;
    }
};

int main(int argc, char* argv[])
{
    using namespace mystd;

    mytuple<char, int, double> mtp;

    myget<0>(mtp) = 'A';
    myget<1>(mtp) = 10;
    myget<2>(mtp) = 4.5;

    return 0;
}
