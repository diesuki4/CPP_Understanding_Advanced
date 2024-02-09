/*
 * https://m.blog.naver.com/oidoman/90145719426
 */
#include <iostream>

using namespace std;

/*
 * 오브젝트 카운터
 */

template <typename T>
class Counter
{
private:
    static int createdCount;
    static int destroyedCount;

protected:
    Counter()  { ++createdCount; }
    ~Counter() { ++destroyedCount; }

public:
    static int get_created()   { return createdCount; }
    static int get_destroyed() { return destroyedCount; }
    static int get_alive()     { return createdCount - destroyedCount; }
};
template <typename T> int Counter<T>::createdCount   = 0;
template <typename T> int Counter<T>::destroyedCount = 0;

// Counter 가 클래스의 인스턴스 개수를 알아서 관리해준다.
class Widget : public Counter<Widget>
{
};

void print()
{
    cout << "Created: "   << Counter<Widget>::get_created()   << endl;
    cout << "Destroyed: " << Counter<Widget>::get_destroyed() << endl;
    cout << "Alive: "     << Counter<Widget>::get_alive()     << endl;
    cout << "-----------------" << endl;
}

int main(int argc, char* argv[])
{
    Widget w;
    print();

    unique_ptr<Widget> uptr(make_unique<Widget>());
    print();

    uptr.reset();
    print();

    return 0;
}
