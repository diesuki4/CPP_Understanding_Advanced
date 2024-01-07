#include <iostream>

using namespace std;

/*
 * 순환 참조 (Cyclic Reference)
 */

class BBB;

class AAA
{
    int data;
    shared_ptr<BBB> sh;

public:
    AAA(int data) : data(data) { }
    void setPtr(shared_ptr<BBB> sh) { this->sh = sh; }
    shared_ptr<BBB> getPtr() const { return sh; }
    int getData() const { return data; }
    ~AAA() { cout << "AAA::소멸자" << endl; }
};

class BBB
{
    int data;
    // 하나를 weak_ptr 로 정의해 순환 참조를 해결
    // shared_ptr<AAA> sh;
    weak_ptr<AAA> wk;

public:
    BBB(int data) : data(data) { }
    void setPtr(shared_ptr<AAA> sh) { /*this->sh*/ wk = sh; }
    weak_ptr<AAA> getPtr() const { return wk; }
    int getData() const { return data; }
    ~BBB() { cout << "BBB::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    shared_ptr<AAA> shA = make_shared<AAA>(5);
    shared_ptr<BBB> shB = make_shared<BBB>(10);

    shA->setPtr(shB);
    shB->setPtr(shA);

    cout << shA.use_count() << endl;
    cout << shB.use_count() << endl;

    shared_ptr<BBB> shAB = shA->getPtr();
    cout << shAB->getData() << endl;

    // 대신 사용 전에 유효성 검증이 필요하다.
    shared_ptr<AAA> shBA = shB->getPtr().lock();
    if (shBA != nullptr)
        cout << shBA->getData() << endl;

    return 0;
}
