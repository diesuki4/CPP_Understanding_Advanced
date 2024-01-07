#include <iostream>

using namespace std;

/*
 * r-value 참조자도 이름을 가지면 l-value가 된다
 */

class Button
{
public:
    Button()                  { }
    Button(const Button& rhs) { cout << "Button::복사 생성자" << endl; }
    Button(Button&& rhs)      { cout << "Button::이동 생성자" << endl; }
};

class Widget
{
    Button button;

public:
    /*
     * r-value 레퍼런스로 전달되긴 했지만 여기서는 이름을 가지므로
     * l-value 로 처리된다.
     */
    Widget(Button&& b) : button(b) { }
};

class Canvas
{
    Button button;

public:
    /*
     * 그러므로 move() 함수를 이용해 l-value 인 b 를
     * 다시 r-value 레퍼런스로 변환해줘야 한다.
     */
    Canvas(Button&& b) : button(move(b)) { }
};

int main(int argc, char* argv[])
{
    Button b;

    Widget w(move(b));
    Canvas c(move(b));

    return 0;
}
