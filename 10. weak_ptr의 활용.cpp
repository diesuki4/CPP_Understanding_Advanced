#include <iostream>

using namespace std;

/*
 * weak_ptr의 활용
 */

// Weak Reference Count 를 증가시킨다.
void GameLoop(weak_ptr<int> wk)
{
    // weak_ptr 은 shared_ptr 로 변환해서만 사용할 수 있다.
    shared_ptr<int> sh = wk.lock();

    // 사용 전에 유효성을 검증해야 한다.
    if (sh != nullptr)
        cout << *sh << endl;
}

int main(int argc, char* argv[])
{
    /* 게임 매니저 측 */
    shared_ptr<int> sh(new int(5));

    /* 캐릭터 측 */
    /* 매니저에서 파괴되었다면, 다른 곳에서도 안 쓰고 싶다. */
    GameLoop(sh);

    /* 게임 매니저 측 */
    /* sh 가 관리하는 자원 해제 */
    sh.reset();

    /* 캐릭터 측 */
    /* 매니저에서 파괴되었다면, 다른 곳에서도 안 쓰고 싶다. */
    GameLoop(sh);

    return 0;
}
