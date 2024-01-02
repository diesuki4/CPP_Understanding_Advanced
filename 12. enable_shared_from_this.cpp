/*
 * https://stackoverflow.com/questions/50557861/weak-from-this-within-constructor#answer-50574777
 */
#include <iostream>

using namespace std;

/*
 * enable_shared_from_this
 */

class Widget
{
public:
    shared_ptr<Widget> getShared()
    {
        // 다른 Control Block 을 가진 shared_ptr 을
        // 계속 반환하게 된다.
        return shared_ptr<Widget>(this);
    }
};

class Slider
{
    // 자기 자신에 대한 weak_ptr 을 유지
    weak_ptr<Slider> weakSelf;

public:
    shared_ptr<Slider> getShared()
    {
        // 그것을 반환하면 된다.
        return weakSelf.lock();
    }
};

// 위 동작을 수행하는 클래스 템플릿을 만들면
template <class T>
class my_enable_shared_from_this
{
    // 실제 enable_shared_from_this 도
    // weak_ptr 로 구현되어 있다.
    weak_ptr<T> weakSelf;

public:
    /*
     * shared_ptr<T> sh(new T);
     * 
     * weak_ptr 의 설정은 이 클래스의 생성자에서는 진행될 수 없다.
     * 
     * 객체의 생성자 호출 시점은
     * 아직 shared_ptr 이 생성되기 전이기 때문.
     * 
     * 1. 객체 생성 (weakSelf 설정 없이)
     * 2. shared_ptr 생성 (여기서 weakSelf 가 설정됨)
     */
    void setWeakSelf(shared_ptr<T> sh)
    {
        weakSelf = sh;
    }

    // 저장되어 있던 weak_ptr 을 반환한다.
    shared_ptr<T> my_shared_from_this()
    {
        return weakSelf.lock();
    }
};

class Button : public my_enable_shared_from_this<Button>
{
public:
    shared_ptr<Button> getShared()
    {
        return my_shared_from_this();
    }
};

int main(int argc, char* argv[])
{
    shared_ptr<Widget> shWgt = make_shared<Widget>();
    shared_ptr<Widget> shW1  = shWgt->getShared();
    shared_ptr<Widget> shW2  = shWgt->getShared();
    shared_ptr<Widget> shW3  = shWgt->getShared();

    // Strong Reference Count 가 모두 1 이므로
    // 해제 시에 문제가 발생한다.
    cout << shWgt.use_count() << endl;
    cout << shW1.use_count() << endl;
    cout << shW2.use_count() << endl;
    cout << shW3.use_count() << endl;

    shared_ptr<Button> shBtn = make_shared<Button>();
    // weak_ptr 설정은 실제로는 shared_ptr 생성자에서 처리된다.
    shBtn->setWeakSelf(shBtn);

    shared_ptr<Button> shB1 = shBtn->my_shared_from_this();
    shared_ptr<Button> shB2 = shBtn->my_shared_from_this();
    shared_ptr<Button> shB3 = shBtn->my_shared_from_this();

    // 정상적으로 Strong Reference Count 가 처리된다.
    cout << shBtn.use_count() << endl;
    cout << shB1.use_count() << endl;
    cout << shB2.use_count() << endl;
    cout << shB3.use_count() << endl;

    return 0;
}
