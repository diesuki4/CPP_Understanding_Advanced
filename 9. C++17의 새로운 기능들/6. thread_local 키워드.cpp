#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

/*
 * thread_local 키워드
 */

/* 스레드는 원래 다른 스레드와
 * 코드, 데이터, 힙을 공유하고
 * 
 * 스택만 따로 할당 받는다.
 *
 * 따라서, 데이터 영역에 존재하는
 * 전역, static 변수들은 원래 공유되는데
 *
 * thread_local 키워드를 이용하면
 * 
 * 스레드별로 관리되는 Thread Local Storage 에 변수가 할당돼
 * 각 스레드별로 독립적으로 전역, static 변수를 사용할 수 있게 된다. */

mutex mtx;

int g = 10;
// 각 스레드 진입점마다 1번씩 초기화된다.
thread_local int tlg = 10;

void Func(int n)
{
    /* Race Condition 발생 */
    static int num = 0;

    for (int i = 0; i < n; ++i)
        ++num, ++g;

    {
        lock_guard lg(mtx);
        cout << "num: " << num << endl;
    }
}

void tlFunc(int n)
{
    /* Thread Local Storage 에서 스레드별로 관리되기 때문에
     * Race Condition 문제가 발생하지 않는다. */
    thread_local static int tlnum = 0;

    for (int i = 0; i < n; ++i)
        ++tlnum, ++tlg;

    {
        lock_guard lg(mtx);
        cout << "tlnum " << tlnum << endl;
    }
}

int main(int argc, char* argv[])
{
    thread func[50];
    thread tlfunc[50];

    for (int i = 0; i < 50; ++i)
        func[i] = thread(Func, 100000),
        tlfunc[i] = thread(tlFunc, 100000);

    for (int i = 0; i < 50; ++i)
        func[i].join(),
        tlfunc[i].join();

    /* Race Condition 으로 인한 잘못된 값 */
    cout << "g: " << g << endl;

    /* 각 스레드는 자신의 tlg 를 증가시켰을 뿐
     * main 스레드의 tlg 는 건드리지 않았다. */
    cout << "tlg: " << tlg << endl;

    return 0;
}
