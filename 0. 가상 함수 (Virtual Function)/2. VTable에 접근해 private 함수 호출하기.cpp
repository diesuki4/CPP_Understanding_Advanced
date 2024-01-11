#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * VTable에 접근해 private 함수 호출하기
 */

class Base
{
private:
    virtual void print()  { cout << "Base::print" << endl; }
};

class Derived : public Base
{
private:
    void print() override { cout << "Derived::print" << endl; }
};

void doPrint(Base* This)
{
    // 첫 번쨰 멤버 VPtr 의 주소 void* *[]
    void*** po = (void***)This;
    // 첫 번째 멤버의 값(VTable 의 주소) void* []
    void** vptr = (void**)(*po);
    // VTable 에서 첫 번째 함수(의 주소) void*
    void* fn = (void*)vptr[0];

    /* 멤버 함수의 포인터는
     * 간단하게 형 변환, copy를 통한 복사가 불가 */
    void (Base:: * fp)();
    memcpy(&fp, &fn, sizeof(void*));

    (This->*fp)();
}

int main(int argc, char* argv[])
{
    Base base;
    Derived derived;

    /* 멤버 함수의 포인터는 일반 포인터보다 크기가 클 수 있다. */
    cout << sizeof(void (*)()) << endl;
    cout << sizeof(void (Base::*)()) << endl;
    cout << sizeof(void (Derived::*)()) << endl;

    doPrint(&base);
    doPrint(&derived);

    return 0;
}
