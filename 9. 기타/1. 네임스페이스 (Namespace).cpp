#include <iostream>

using namespace std;

/*
 * 네임스페이스 (Namespace)
 */

int i = 10;

namespace myspace
{
    int i = 20;
}
// 네임스페이스는 분할이 가능하다.
namespace myspace
{
    int j = 30;
}

int main(int argc, char* argv[])
{
    // 전역 네임스페이스
    cout << ::i << endl;

    cout << myspace::i << endl;
    cout << myspace::j << endl;

    return 0;
}
