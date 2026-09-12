#include <iostream>
#include "sem1.h"


int main()
{
    int num1, num2;
    std::cout << "Put number one: ";
    std::cin >> num1;
    std::cout << "Put number two: ";
    std::cin >> num2;
    int res = summ(num1, num2);
    std::cout << num1 << " + " << num2 << " = " << res << std::endl;
}