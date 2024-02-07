/*
 * https://gsbang.tistory.com/entry/Cpp-클래스-관계-연관association-aggregation-composition
 * https://gsbang.tistory.com/entry/Cpp-클래스-관계-상속
 * https://kyoun.tistory.com/100
 * https://bootcamp.uxdesign.cc/association-composition-and-aggregation-in-c-3ca70336e992
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

// 추상 인터페이스 클래스
class IChargeable
{
public:
    virtual void charge() = 0;
    virtual ~IChargeable() {}
};

/* 인터페이스 클래스 상속 (Realization)
 * A 는 B 의 인터페이스를 구현해야 한다.
 *
 * 상속 받은 클래스는 인터페이스 클래스의 구현체가 된다. */
class Car : public IChargeable
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
     * 운전자는 자동차에 소유되지 않고, 여러 자동차를 가질 수 있다.
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

    virtual void charge() override { cout << "급속 충전" << endl; }

    ~Car()
    {
        /* Composition 은 객체의 생성과 소멸을 관리한다.
         * 
         * Tire[4]
         * Engine */
    }
};

class RearWing {};

/* Is-A (Inheritance 혹은 Generalization)
 * 스포츠카는 자동차의 일종이다.
 *
 * 무조건 public 으로 상속해야 한다.
 *
 * 자식은 부모의 일종으로서 인터페이스와 구현을
 * 모두 물려받아야 하기 때문. */
class SportsCar : public Car
{
    shared_ptr<RearWing> pRearWing;

public:
    /* Has-A (Aggregation)
     * Association 과 유사하지만 소유의 개념이다.
     * 리어윙은 자동차에 소유되고, 여러 자동차에 장착될 수 없다.
     *
     * 보통 포인터로 참조한다. */
    void attachRearWing(shared_ptr<RearWing> pNewRearWing)
    {
        pRearWing = pNewRearWing;
    }

    shared_ptr<RearWing> detachRearWing()
    {
        shared_ptr<RearWing> pTemp(pRearWing);
	    // 소유의 개념이 있기 때문에, 여러 자동차에 동시에 장착 불가
        pRearWing.reset();

        return pTemp;
    }
};

int main(int argc, char* argv[])
{


    return 0;
}
