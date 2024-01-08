#include <iostream>

using namespace std;

/*
 * RAII (자원 획득은 초기화다, Resource Acquisition Is Initialization)
 *
 * 생성자, 소멸자 자동 호출을 이용해
 * 생성자에서 획득한 자원을 소멸자를 통해 자동으로 해제하는 개념
 * 
 * DUMMY 매크로: 특정 지점에 Break Point 를 걸고 싶을 때
 * SCOPE_EXIT 매크로: 블록 탈출 시 특정 처리를 하고 싶을 때
 * PRE_BLOCK 매크로: if 문 탈출 시 특정 처리를 하고 싶을 때
 */

// 실제 연결을 진행하는 매크로
#define _STRING_CAT(a, b)   a ## b
// __LINE__ 등이 정상적으로 변환되도록 하기 위한 레퍼 매크로
#define STRING_CAT(a, b)    _STRING_CAT(a, b)
// 특정 지점에 Break Point 를 걸고 싶을 때 사용
#define DUMMY               int STRING_CAT(_dummy, __LINE__) = 0

// RAII 객체
template <typename Func>
class ScopeExit
{
    // 생성자에서 함수를 받고, 소멸자에서 호출한다.
    Func f;

public:
    ScopeExit(Func f_) : f(f_)  { }
    ~ScopeExit()                { f(); }
    // if 블록에서 사용하기 위한 형 변환
    operator bool()             { return false; }
};

template <typename Func>
auto MakeScopeExit(Func f)
{
    return ScopeExit<Func>(f);
}

// auto scope_exit134 = MakeScopeExit(lambda);
#define SCOPE_EXIT(expr)    auto STRING_CAT(scope_exit, __LINE__) = MakeScopeExit([&]() { expr })

void SomeFunc1()
{
    SCOPE_EXIT( cout << "Scope Exit Work 1" << endl; );
    SCOPE_EXIT( cout << "Scope Exit Work 2" << endl; );

    cout << "Func Work" << endl;
}

int gVal = 100;
/* 함수 종료 후 전역 변수의 값을
 * 복구하고 싶을 때 활용 */
void SomeFunc2()
{
    auto old_gVal = gVal;
    SCOPE_EXIT( cout << (gVal = old_gVal) << endl; );

    gVal = 1;
    cout << gVal << endl;
}

unsigned gValueStamp = 0;
/* 옵저버 패턴에서 gVal 이 바뀔 때
 * gValueStamp 도 바꿔주고 싶을 때 활용 */
#define PRE_BLOCK(expr)     if ( SCOPE_EXIT(expr) ); else

void SomeFunc3()
{
    PRE_BLOCK( gValueStamp = gVal; cout << " 3rd" << endl; )
    PRE_BLOCK( cout << " 2nd"; )
    {
        ++gVal;
        cout << "1st";
    }

    cout << gVal << " == " << gValueStamp << endl;
}

int main(int argc, char* argv[])
{
    int ij = 10;

    cout << STRING_CAT(i, j) << endl;

    DUMMY;      // 중단점 설정 가능
    int a = 0;
    DUMMY;      // 중단점 설정 가능

    // if 문 내의 표현식에서도 변수를 정의할 수 있다.
    if (int i = 0)
        cout << i << endl;
    // else if, else 블록에서도 참조할 수 있다.
    else
        cout << i << endl;

    SomeFunc1();
    SomeFunc2();
    SomeFunc3();

    return 0;
}
