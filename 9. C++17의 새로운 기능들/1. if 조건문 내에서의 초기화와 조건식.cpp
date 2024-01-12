#include <iostream>

using namespace std;

/*
 * if 조건문 내에서의 초기화와 조건식
 */

int main(int argc, char* argv[])
{
    /* if 조건문 안에 초기화와 조건식을 같이 넣을 수 있다. */
    if (bool b = true; b)
        cout << boolalpha << b << endl;
    else
        cout << boolalpha << b << endl;

    return 0;
}
