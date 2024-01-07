#include <iostream>
#include <functional>

using namespace std;

/*
 * 람다 (Lambda)
 *
 * 클래스 = 람다 표현식, 객체 = 클로저
 */

function<void(void)> f;

void Func()
{
    int num = 10;

    /* 캡처하는 변수가 호출 시점에서 유효하지 않을 수 있기 때문에
     * 지역 변수를 캡처할 때는 주의해야 한다. */
    auto Print = [&]()
    {
        cout << num << endl;
    };

    Print();
    f = Print;
}

int main(int argc, char* argv[])
{
    // 람다는 auto 를 매개변수로 지정할 수 있다.
    auto lambda = [](auto a, auto b) { return a + b; };

    // decltype(f) Add3 = f;
    auto Add = lambda;
    cout << Add(10, 20.4F) << endl;

    int i = 3, j = 6;

    auto Add2 = [i, j]()
    {
        // 값 캡처는 const 로 처리된다.
        // ++i, ++j;
        return i + j;
    };

    auto Add3 = [i, j]() mutable
    {
        // mutable 을 붙이면 조작 가능
        ++i, ++j;
        return i + j;
    };

    Func();
    // num 이 더 이상 유효하지 않은 시점에서의 호출
    f();

    return 0;
}
