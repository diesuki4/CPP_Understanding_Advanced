#include <iostream>

using namespace std;

/*
 * new, delete 연산자 오버로딩
 */

char buffer[1024] = {0};

class Class
{
    int data;

public:
    Class(int data) : data(data) { cout << "생성자 (" << data << ")" << endl; }

    void* operator new (size_t size)
    {
        cout << "operator new (" << size << ")" << endl;

        /* Boost 라이브러리의 메모리 풀에서는
         * 동적 할당 오버헤드를 줄이기 위해
         *
         * 미리 만들어둔 풀을 할당한다. */

        // return new char[size];
        return buffer;
    }

    /* new 연산자 오버로딩 시에는 매개변수를 추가할 수 있다. */
    void* operator new[] (size_t size, const char* msg, int iValue)
    {
        cout << "operator new[] (" << size << ") " << msg << " " << iValue << endl;

        // return new char[size];
        return buffer;
    }

    void operator delete (void* p)
    {
        cout << "operator delete ()" << endl;

        // delete p;
        // 메모리 풀에 반환
    }

    /* delete 오버로딩에는 매개변수를 추가할 수 없다. */
    void operator delete[] (void* p)
    {
        cout << "operator delete[] ()";

        // delete[] p;
        // 메모리 풀에 반환
    }

    ~Class() { cout << "소멸자" << endl; }
};

void printBuffer()
{
    for (int* p = reinterpret_cast<int*>(buffer); *p; ++p)
        cout << *p << " ";

    cout << endl;
}

int main(int argc, char* argv[])
{
    // Class* p = static_cast<Class*>( operator new(sizeof(Class)) );
    // p->Class::Class();
    Class* p = new Class(6);
    printBuffer();

    // p->Class::~Class();
    // operator delete(p);
    delete p;

    /* 객체 배열의 첫 번째 블록(dword) 에는
     * 배열의 크기가 저장된다. */
    p = new ("객체 배열 할당", 3) Class[3]{7, 8, 9};
    printBuffer();

    delete[] p;

    return 0;
}
