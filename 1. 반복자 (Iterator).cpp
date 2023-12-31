#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

/*
 * 반복자 (Iterator)
 */

template <typename T>
void Print(T&& t)
{
    /*
     * 컨테이너에 상관 없이,
     * 일관된 방식으로 순회할 수 있다.
     */
    for (auto it = t.begin(); it != t.end(); ++it)
        cout << *it << " ";

    cout << endl;
}

namespace mystd
{
    template <typename T>
    class myvector
    {
    public:
        // 반복자는 실제로는 구조체다.
        using iterator = T*;

        myvector() : ibegin(data), iend(data) { }

        void push_back(const T& data)
        {
            *(iend++) = data;
        }

        T& operator[] (int i)
        {
            return data[i];
        }

        size_t size() const
        {
            return iend - ibegin;
        }

        iterator begin() const
        {
            return ibegin;
        }

        iterator end() const
        {
            return iend;
        }

    private:
        T data[100];
        iterator ibegin;
        iterator iend;
    };
};

int main(int argc, char* argv[])
{
    vector<int> v{6, 2, 4, 3, 1, 5};
    list<int> l{6, 2, 4, 3, 1, 5};
    set<int> s{6, 2, 4, 3, 1, 5};

    Print(v);
    Print(l);
    Print(s);

    using namespace mystd;

    myvector<int> mv;

    mv.push_back(6);
    mv.push_back(2);
    mv.push_back(4);
    mv.push_back(3);
    mv.push_back(1);
    mv.push_back(5);

    Print(mv);

    return 0;
}
