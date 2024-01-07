#include <iostream>

using namespace std;

/*
 * DUMMY 매크로
 */

// 실제 연결을 진행하는 매크로
#define _STRING_CAT(a, b)   a ## b
// __LINE__ 등이 정상적으로 변환되도록 하기 위한 레퍼 매크로
#define STRING_CAT(a, b)    _STRING_CAT(a, b)
// 특정 지점에 Break Point 를 걸고 싶을 때 사용
#define DUMMY               int STRING_CAT(_dummy, __LINE__) = 0;

int main(int argc, char* argv[])
{
    int ij = 10;

    cout << STRING_CAT(i, j) << endl;

    DUMMY;      // 중단점 설정 가능
    int a = 0;
    DUMMY;      // 중단점 설정 가능

    // if 문 내의 표현식에서는 변수를 정의할 수 있다.
    if (int i = 0)
        cout << i << endl;
    // else if, else 블록에서도 참조할 수 있다.
    else
        cout << i << endl;

    return 0;
}
