#include <iostream>

using namespace std;

/*
 * 가변 인자 템플릿 (Variadic Template) - 함수
 */

// 종료 조건
void Func()
{
    cout << endl;
}

/* 템플릿 파라미터 팩은 타입 앞에 ... 이 오고,
 * 함수 파라미터 팩은 타입 뒤에 ... 이 온다.
 *
 * typename Args... 이 아닌, typename... Args
 * Args...& 가 아닌, Args&...
 *
 * Func<double> 이 전달되면
 * Args 에는 아무것도 지정되지 않는다. */
template <typename Arg0, typename... Args>    // typename... Args  ==>  템플릿 파라미터 팩
void Func(Arg0& arg0, Args&... args)          // Args&... args     ==>  함수 파라미터 팩
{
    cout << arg0 << " ";
    Func(args...);
}

int main(int argc, char* argv[])
{
    const char* p = "Hello World";
    char c        = '!';
    int i         = 1;
    float f       = 2.F;
    double d      = 3.0;

    // arg0 ==> const char*&
    // args ==> char&, int&, float&, double&
    Func(p, c, i, f, d);

    return 0;
}
