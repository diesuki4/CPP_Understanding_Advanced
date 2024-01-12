#include <iostream>

using namespace std;

/*
 * 일반화된 Range-based for
 */

struct Mystring
{
    string s;

    // 공백을 만나면 false 를 반환하는 펑터
    struct EndOfString
    {
        bool operator() (string::iterator it)
        {
            return *it != ' ';
        }
    };

    string::iterator begin() { return s.begin(); }
    EndOfString end()        { return EndOfString(); }
};
// string::iterator it = Mystring::begin();
// it != Mystring::end()
bool operator != (string::iterator it, Mystring::EndOfString p)
{
    return p(it);
}

int main(int argc, char* argv[])
{
    /* end() 에서 펑터를 반환하고, 펑터에서 () 연산자 오버로딩을 통해
     * 종료 조건을 명시할 수 있다. */
    for (char c : Mystring{"Hello World !!"})
        cout << c;

    return 0;
}
