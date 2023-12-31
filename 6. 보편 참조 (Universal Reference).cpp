/*
 * https://openmynotepad.tistory.com/20
 */
#include <iostream>
#include <vector>

using namespace std;

/*
 * 보편 참조 (Universal Reference)
 *
 * <타입 추론> 이 필요한 상황에서
 * l-value 레퍼런스 인자도, r-value 레퍼런스 인자도 전달할 수 있게 되면,
 * 
 * 보편 참조가 된다.
 *
 * 템플릿에서 매개변수 타입이 정확히 <T&&> 로 선언되어 있거나,
 * 변수가 auto&& 로 선언되어 있는 경우
 */

class Widget { };

// l-value 도, r-value 도 전달받을 수 있는 보편 참조
template <typename T>
void Func(T&& t)
{
    return;
}

// T&& 형식이 아니므로, 보편 참조가 아니다.
template <typename T>
void Gunc(vector<T>&& v)
{
    return;
}

// const 를 붙여도, 보편 참조가 아니다.
template <typename T>
void Gunc(const T&& v)
{
    return;
}

// T&& 형식이어도, 보편 참조가 아니다.
template <typename T>
class Class
{
public:
    // Class<T> 의 T 를 추론하는 과정에서
    // 이미 T 가 무슨 타입인지 알기 때문에 추론이 더 이상 필요 없다.
    void Func(T&& x);
};

int main(int argc, char* argv[])
{
    // 이건 보편 참조가 아니다.
    Widget&& w1 = Widget();

    // 보편 참조 (w1 은 l-value)
    auto&& w2 = w1;
    // 보편 참조 (Widget() 은 r-value)
    auto&& w3 = Widget();

    Func(w1);        // w1       ==> l-value
    Func(Widget());  // Widget() ==> r-value

    return 0;
}
