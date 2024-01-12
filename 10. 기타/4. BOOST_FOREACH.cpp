#include <iostream>
#include <vector>

using namespace std;

/*
 * BOOST_FOREACH
 */

// bBreakChecker 는 본문의 break 판별을 위해 사용
#define BOOST_FOREACH(expr, container) \
if (bool bBreakChecker = true) \
    for (decltype(container)::iterator it = container.begin(); bBreakChecker && it != container.end(); ++it) \
        if (!(bBreakChecker = false)) \
            for (expr = *it; !bBreakChecker; bBreakChecker = true)

class Class
{
    size_t n;
    int* arr;

public:
    Class(vector<int> v) : n(v.size()), arr(new int[n])
    {
        for (int i = 0; i < n; ++i)
            arr[i] = v[i];
    }

    int* begin() const { return arr; }
    int* end() const   { return arr + n; }

    ~Class() { delete[] arr; }
};

int main(int argc, char* argv[])
{
    vector<int> container{0, 1, 2, 3, 4, 5};

    BOOST_FOREACH(int& e, container)
    {
        if (e == 4)
            break;
        else
            cout << e << " ";
    }

    Class c({0, 1, 2, 3, 4, 5});

    /* 포인터나 반복자를 반환하는 begin(), end() 함수가 구현되어 있으면
     * Range-based for 를 쓸 수 있다. */
    for (int& e : c)
    {
        if (e == 4)
            break;
        else
            cout << e << " ";
    }

    return 0;
}
