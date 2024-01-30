/*
 * https://gsbang.tistory.com/entry/Cpp-클래스-관계-상속
 * https://blog.naver.com/finderthing/10154813632
 * https://castle1262.tistory.com/31
 */
#include <iostream>

using namespace std;

/*
 * Is-A, Has-A, Uses-A
 */

class Tire {};
class Engine {};
class Driver {};
class CarWash
{
public:
    void use() {}
};

class Car
{
    /* Has-A (Composition)
     * 자동차는 4개의 타이어를 꼭 가져야 하며, 없이는 존재할 수 없다. */
    Tire tire[4];
    /* Has-A (Composition)
     * 자동차는 1개의 엔진을 꼭 가져야 하며, 없이는 존재할 수 없다.
     *
     * Composition 은 꼭 값 타입이 아니라, 포인터 타입일 수도 있다. */
    unique_ptr<Engine> pEngine;
    /* Has-A (Association)
     * 자동차는 운전자를 가질 수도 있고 안 가질 수도 있으나, 생명 주기는 관리하지 않는다.
     *
     * 보통 포인터로 참조한다. */
    shared_ptr<Driver> pDriver;

public:
    Car() : pEngine{make_unique<Engine>()} {}

    void setDriver(shared_ptr<Driver> pNewDriver)
    {
        pDriver = pNewDriver;
    }

    /* Uses-A (Dependency)
     * 자동차는 세차장을 이용하며, 잠깐 쓸 뿐 참조는 유지하지 않는다. */
    void wash(shared_ptr<CarWash> pCarWash)
    {
        pCarWash->use();
    }

    virtual void drive() {}
    virtual ~Car() {}
};

class RearWing {};

/* Is-A (Inheritance 혹은 Generalization)
 * 스포츠카는 자동차의 일종이다.
 *
 * 무조건 public 으로 상속해야 한다.

 * 자식은 부모의 일종으로서 인터페이스와 구현을
 * 모두 물려받아야 하기 때문. */
class SportsCar : public Car
{
    /* Has-A (Aggregation)
     * 스포츠카는 리어윙을 가질 수도 있고 안 가질 수도 있으나, 가질 경우 생명 주기를 관리해 줘야 한다.
     *
     * 보통 포인터로 참조한다. */
    unique_ptr<RearWing> pRearWing;

public:
    void addRearWing()
    {
        pRearWing = make_unique<RearWing>();
    }

    void drive() override {}
};

int main(int argc, char* argv[])
{


    return 0;
}
