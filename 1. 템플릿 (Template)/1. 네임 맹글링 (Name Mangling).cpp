#include <iostream>

using namespace std;

/*
 * 네임 맹글링 (Name Mangling)
 */

/* Decorated Name
 * 
 * C      ==>  _GetMax
 * 
 * int    ==>  ??$GetMax@N@@YANNN@Z
 * double ==>  ??$GetMax@H@@YAHHH@Z
 *
 * 이것이 C와 C++ 함수가 호환되지 않는 이유이고
 * 그래서 C 함수를 가져와 쓸 때는 extern "C" 가 필요하다. */

/* <네임 맹글링>
 *
 * 컴파일러가 구분을 위해
 * 원래 함수의 이름을 변형해 바꾸는 것을 뜻한다.
 *
 * 이것이 오버로딩의 원리다. */

template <typename T>
T GetMax(T a, T b)
{
    cout << __FUNCTION__  << endl;   // Name
    cout << __FUNCDNAME__ << endl;   // Decorated Name
    cout << __FUNCSIG__   << endl;   // Signature

    return (a < b) ? b : a;
}

int main(int argc, char* argv[])
{
    GetMax(2, 3);
    GetMax(2.0, 3.0);

    return 0;
}
