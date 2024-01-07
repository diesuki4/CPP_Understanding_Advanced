#include <iostream>
#include <tuple>

using namespace std;

/*
 * make_seq
 */

namespace mystd
{
    template <int...>
    struct seq
    {
    };

    // make_seq<3>
    // make_seq<2, 2>
    // make_seq<1, 1, 2>
    // make_seq<0, 0, 1, 2>
    template <int max, int... s>
    struct make_seq : make_seq<max - 1, max - 1, s...>
    {
    };

    // make_seq<0, 0, 1, 2>
    template <int... s>
    struct make_seq<0, s...>
    {
        // seq<0, 1, 2>
        using type = seq<s...>;
    };

    template <int max>
    using MakeSeq = typename make_seq<max>::type;
};

int main(int argc, char* argv[])
{
    tuple<float, int> t = {3.3F, 10};

    cout << get<0>(t) << endl;  // 3.3F
    cout << get<1>(t) << endl;  // 10

    using namespace mystd;

    // make_seq<2>::type ==> seq<0, 1>
    MakeSeq<2> msq2;
    // make_seq<3>::type ==> seq<0, 1, 2>
    MakeSeq<3> msq3;

    return 0;
}
