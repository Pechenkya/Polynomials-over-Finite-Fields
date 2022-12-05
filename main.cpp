#include <iostream>
#include ".\\Tests\\tests.hpp"

int main()
{
    PB_Tests::set_tests();
    int x = 1;
    while(true)
    {
        std::cout << "Input any number to run test (0 to exit): ";
        std::cin >> x;
        if(!x)
            break;
        
        PB_Tests::run_test();
    }
    return 0;
}