#include <iostream>

using namespace std;

/*
 * storage, helper
 */

struct Base { };
struct Derived : Base { };

namespace mystd
{
    template <int...>
    struct seq
    {
    };

    template <int x, typename Arg>
    struct storage
    {
        Arg data;
    };

    template <typename Seq, typename... Args>
    struct helper
    {
    };

    // helper<seq<0, 1, 2>, char, int, double>
    // helper<seq<0, 1, 2>, char, int, double> : storage<0, char>, helper<seq<1, 2>, int, double>
    // helper<seq<0, 1, 2>, char, int, double> : storage<0, char>, storage<1, int>, helper<seq<2>, double>
    // helper<seq<0, 1, 2>, char, int, double> : storage<0, char>, storage<1, int>, storage<2, double>
    template <int s0, int... s, typename A0, typename... Args>
    struct helper<seq<s0, s...>, A0, Args...>
        : storage<s0, A0>, helper<seq<s...>, Args...>
    {
    };
};

int main(int argc, char* argv[])
{
    Derived::Base bs;

    using namespace mystd;

    helper<seq<0, 1, 2>, char, int, double>::storage<0, char>    t;
    helper<seq<0, 1, 2>, char, int, double>::storage<0, char>    t0;
    helper<seq<0, 1, 2>, char, int, double>::storage<1, int>     t1;
    helper<seq<0, 1, 2>, char, int, double>::storage<2, double>  t2;

    t0.data = 'A';
    t1.data = 10;
    t2.data = 4.5;

    return 0;
}
