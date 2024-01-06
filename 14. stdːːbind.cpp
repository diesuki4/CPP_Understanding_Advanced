#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

/*
 * std::bind
 */

int print(int i) { cout << i << endl; return i; }

class Widget
{
public:
    int print(int i)         { cout << i << endl; return i; }
    int print2(int i, int j) { cout << i << " " << j << endl; return i + j; }
};

int main(int argc, char* argv[])
{
    int (*fp)(int) = print;

    fp(5);

    Widget w;
    using WIDGET_PRINT = int (Widget::*)(int);
    WIDGET_PRINT mfp = &Widget::print;

    w.print(5);
    // 멤버 함수 접근 연산자
    (w.*mfp)(5);

    bind(&Widget::print, w, 5)();

    // 1번째 인자 5 를 가져온다.
    auto wPrint = bind(&Widget::print, w, _1);
    wPrint(5);

    // [1, 5] 에서 2번째 인자 5 를 가져온다.
    auto wPrint2 = bind(&Widget::print, w, _2);
    wPrint2(1, 5);

    // w 를 _1 에, 5 를 _2 에 바인딩한다.
    auto wPrint3 = bind(&Widget::print, _1, _2);
    wPrint3(w, 5);

    // w 를 _1 에, 5 를 _2 에, 10 을 _3 에 바인딩한다.
    auto wPrint4 = bind(&Widget::print2, _1, _2, _3);
    wPrint4(w, 5, 10);

    return 0;
}
