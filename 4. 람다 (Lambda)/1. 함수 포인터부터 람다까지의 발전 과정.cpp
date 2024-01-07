#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/*
 * 함수 포인터부터 람다까지의 발전 과정
 */

bool Pred1(int lhs)
{
    return lhs >= 3;
}

class Pred2
{
    int num;

public:
    Pred2(int num) : num(num) { }
    bool operator() (int lhs) { return lhs >= num; }
};

class Pred3
{
public:
    // bind() 를 사용하기 위해서는
    // 다음을 필수적으로 선언해 주어야 한다.
    using result_type = bool;
    using first_argument_type = int;
    using second_argument_type = int;

    // T operator() (Y, U) const
    // 형식을 갖춰줘야 한다.
    result_type operator() (first_argument_type lhs, second_argument_type rhs) const { return lhs <= rhs; }
};

class Pred4
{
public:
    // bind() 를 위한 선언
    using result_type = bool;
    using first_argument_type = int;
    using second_argument_type = int;

    // T operator() (Y, U) const
    result_type operator() (first_argument_type lhs, second_argument_type rhs) const { return lhs >= rhs; }
};

int main(int argc, char* argv[])
{
    vector<int> v{1, 2, 3, 4, 5, 6};

    // 함수 포인터를 이용한 C 스타일의 전통적인 방식 
    int result = count_if(v.begin(), v.end(), Pred1);

    // 펑터(함수 객체) 를 이용한 C++ 스타일의 방식 
    result = count_if(v.begin(), v.end(), Pred2(3));

    // 펑터(함수 객체) 와 bind1st 를 이용한 C++ 스타일의 방식
    // 3 이 lhs 에 바인딩된다.
    // 
    // binder1st 라는 펑터를 반환한다.
    result = count_if(v.begin(), v.end(), bind1st(Pred3(), 3));

    // 펑터(함수 객체) 와 bind2nd 를 이용한 C++ 스타일의 방식
    // 3 이 rhs 에 바인딩된다.
    // 
    // binder2nd 라는 펑터를 반환한다.
    result = count_if(v.begin(), v.end(), bind2nd(Pred4(), 3));

    using namespace std::placeholders;
    // 인자를 _1 위치에 바인딩한다.
    result = count_if(v.begin(), v.end(), bind(Pred4(), _1, 3));
    result = count_if(v.begin(), v.end(), bind(Pred4(), 3, _1));
    // 5 보다 작고 2 보다 큰 개수
    result = count_if(v.begin(), v.end(), bind(
        logical_and<bool>(),
        bind(less<int>(), _1, 6),
        bind(greater<int>(), _1, 2)
    ));

    // 람다를 이용한 모던 C++ 스타일의 방식 
    result = count_if(v.begin(), v.end(), [](int lhs) { return lhs >= 3; });

    cout << result << endl;

    return 0;
}
